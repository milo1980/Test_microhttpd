/*
 * main.c
 *
 *  Created on: 14/09/2017
 *      Author: Milorad
 */

#include <sys/types.h>
//#include <sys/select.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <microhttpd.h>

#define POSTBUFFERSIZE  512
#define MAXCLIENTS      2

#define GET             0
#define POST            1

const char *busypage =
    "<html><head><title>libmicrohttpd server</title></head>\
     <body>This server is busy, please try again later.</body></html>";
const char *completepage =
    "<html><head><title>libmicrohttpd server</title></head>\
     <body>The upload has been completed.</body></html>";
const char *servererrorpage =
    "<html><head><title>libmicrohttpd server</title></head>\
     <body>An internal server error has occured.</body></html>";

const char *createTerminalPostPage =
    "<html><head><title>libmicrohttpd server</title></head>\n\
    <body>\n\
    <p>Current number of terminals : %s </p>\n\
    <p></p>\n\
    <p>   Create terminal</p>\n\
    <p>-------------------------</p>\n\
    <form action=\"/terminalpost\" method=\"post\" enctype=\"multipart/form-data\">\n\
      <input type=\"checkbox\" name=\"cardType\" value=\"Visa\" checked> Visa Card<br>\n\
      <input type=\"checkbox\" name=\"cardType\" value=\"Master\" checked> Master Card<br>\n\
      <input type=\"checkbox\" name=\"cardType\" value=\"EFTPOS\" checked> EFTPOS<br>\n\
      <p></p>\n\
      <input type=\"checkbox\" name=\"TransactionType\" value=\"Cheque\" checked> Cheque<br>\n\
      <input type=\"checkbox\" name=\"TransactionType\" value=\"Savings\" checked> Savings<br>\n\
      <input type=\"checkbox\" name=\"TransactionType\" value=\"Credit\" checked> Credit<br>\n\
      <input type=\"submit\" value=\"Submit\">\n\
    </form></body></html>";

const char *createTerminalJsonPage =
    "<html><head><title>libmicrohttpd server</title></head>\n\
    <body>\n\
    <p>Current number of terminals : %s </p>\n\
    <p></p>\n\
    <p>   Create terminal</p>\n\
    <p>-------------------------</p>\n\
    <form action=\"/terminalpost\" enctype=\"application/json\">\n\
      <input type=\"checkbox\" name=\"cardType\" value=\"Visa\" checked> Visa Card<br>\n\
      <input type=\"checkbox\" name=\"cardType\" value=\"Master\" checked> Master Card<br>\n\
      <input type=\"checkbox\" name=\"cardType\" value=\"EFTPOS\" checked> EFTPOS<br>\n\
      <p></p>\n\
      <input type=\"checkbox\" name=\"TransactionType\" value=\"Cheque\" checked> Cheque<br>\n\
      <input type=\"checkbox\" name=\"TransactionType\" value=\"Savings\" checked> Savings<br>\n\
      <input type=\"checkbox\" name=\"TransactionType\" value=\"Credit\" checked> Credit<br>\n\
      <input type=\"submit\" value=\"Submit\">\n\
    </form></body></html>";

const char * listTerminalPage =
    "<html><head><title>libmicrohttpd server</title></head>\n\
     <body>\n\
     <p>Current number of terminals : %s </p>\n\
     <p>List of Terminals</p>\n\
     <p>-------------------------</p>\n\
     %s\n\
     </body></html>";

const char * oneTerminal =
    "<p>id:%s</p>\n\
     <p>Cards Supported: %s %s %s</p>\n\
     <p>Transactions Supported: %s %s %s</p>\n\
     <p>----</p>";

const char * basePage =
    "<html><head><title>libmicrohttpd server</title>\n\
     </head><body>libmicrohttpd demo</body></html>";

const char * badPage =
    "<html><head><title>libmicrohttpd server</title>\n\
     </head><body>Bad page!</body></html>";

const char * submitPage =
    "<html><head><title>libmicrohttpd server</title>\n\
     </head><body>Submit Ok.</body></html>";

const char * errorPage =
    "<html><head><title>libmicrohttpd server</title>\n\
     </head><body>Error!</body></html>";

typedef struct
{
  char cardsSupported[3][64];
  char transactionsSupported[3][64];
  unsigned int id;
} terminalinfo_t;

struct connection_info_struct
{
  int connectiontype;
  struct MHD_PostProcessor *postprocessor;
  terminalinfo_t terminal;
  int cardIndex;
  int transactionIndex;
  const char *answerstring;
  int answercode;
};

static unsigned int nr_of_uploading_clients = 0;
static unsigned int nr_of_terminals = 0;
static terminalinfo_t terminalList[100];
static char url_args[100][64];

static int send_page(struct MHD_Connection *connection, const char *page,
    int status_code)
{
  int ret;
  struct MHD_Response *response;

  response = MHD_create_response_from_buffer(strlen(page), (void *) page,
      MHD_RESPMEM_MUST_COPY);
  if (!response) return MHD_NO;
  MHD_add_response_header(response, MHD_HTTP_HEADER_CONTENT_TYPE, "text/html");
  ret = MHD_queue_response(connection, status_code, response);
  MHD_destroy_response(response);

  return ret;
}

static int iterate_post(void *coninfo_cls, enum MHD_ValueKind kind,
    const char *key, const char *filename, const char *content_type,
    const char *transfer_encoding, const char *data, uint64_t off, size_t size)
{
  struct connection_info_struct *con_info = coninfo_cls;

  con_info->answerstring = servererrorpage;
  con_info->answercode = MHD_HTTP_INTERNAL_SERVER_ERROR;

  printf("\tkey: %s\tname: %s\n", key, data);
  if (0 == strcmp(key, "cardType"))
  {
    strncpy(con_info->terminal.cardsSupported[con_info->cardIndex++], data, 64);
  }
  else if (0 == strcmp(key, "TransactionType"))
  {
    strncpy(
        con_info->terminal.transactionsSupported[con_info->transactionIndex++],
        data, 64);
  }
  else
  {
  }

  con_info->answerstring = completepage;
  con_info->answercode = MHD_HTTP_OK;

  return MHD_YES;
}

static void request_completed(void *cls, struct MHD_Connection *connection,
    void **con_cls, enum MHD_RequestTerminationCode toe)
{
  struct connection_info_struct *con_info = *con_cls;

  if (NULL == con_info) return;

  if (con_info->connectiontype == POST)
  {
    if (NULL != con_info->postprocessor)
    {
      MHD_destroy_post_processor(con_info->postprocessor);
      nr_of_uploading_clients--;
    }

    con_info->terminal.id = (unsigned int) rand();
    memcpy(&terminalList[nr_of_terminals], &con_info->terminal,
        sizeof(terminalinfo_t));
    printf("POST\t%s\tid: %d\n", "DONE", terminalList[nr_of_terminals].id);
    nr_of_terminals++;
  }

  free(con_info);
  *con_cls = NULL;
}

static int get_url_args(void *cls, enum MHD_ValueKind kind, const char *key,
    const char* value)
{
  return 0;
}

static int answer_to_connection(void * cls, struct MHD_Connection * connection,
    const char * url, const char * method, const char * version,
    const char * upload_data, size_t * upload_data_size, void ** con_cls)
{
  size_t i;
  static char pageBuffer[2048] = "";
  static char terminalListString[1024] = "";
  static char tempString[512] = "";
  static char tempString2[64] = "";

  if (NULL == *con_cls)
  {
    struct connection_info_struct *con_info;

    if (nr_of_uploading_clients >= MAXCLIENTS)
      return send_page(connection, busypage, MHD_HTTP_SERVICE_UNAVAILABLE);

    con_info = malloc(sizeof(struct connection_info_struct));
    if (NULL == con_info) return MHD_NO;

    //init
    for (i = 0; i < 3; i++)
    {
      strcpy(con_info->terminal.cardsSupported[i], "");
      strcpy(con_info->terminal.transactionsSupported[i], "");
    }
    con_info->cardIndex = 0;
    con_info->transactionIndex = 0;
    con_info->terminal.id = 0;

    if (0 == strcmp(method, "POST"))
    {
      con_info->postprocessor = MHD_create_post_processor(connection,
      POSTBUFFERSIZE, iterate_post, (void *) con_info);

      if (NULL == con_info->postprocessor)
      {
        free(con_info);
        return MHD_NO;
      }

      nr_of_uploading_clients++;

      con_info->connectiontype = POST;
      con_info->answercode = MHD_HTTP_OK;
      con_info->answerstring = completepage;
    }
    else con_info->connectiontype = GET;

    *con_cls = (void *) con_info;

    return MHD_YES;
  }

  if (0 == strcmp(method, "GET"))
  {
    printf("GET");
    if (0 == url)
    {
      printf("\tNO URL\n");
      snprintf(pageBuffer, sizeof(pageBuffer), basePage);
    }
    else
    {
      if (0 == strcmp(url, "/"))
      {
        printf("\tNO URL");
        /*create and send responses*/
        snprintf(pageBuffer, sizeof(pageBuffer), basePage);
      }
      else
      {
        url++;
        printf("\t%s", url);
        if (0 == strcmp(url, "create_terminals"))
        {
          /*create and send responses*/
#if 0
          snprintf(pageBuffer, sizeof(pageBuffer), createTerminalPostPage,
              itoa(nr_of_terminals, tempString, 10));
#else
          MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND,
              get_url_args, url_args);
          printf("\t%s",url_args[0]);
          snprintf(pageBuffer, sizeof(pageBuffer), createTerminalJsonPage,
              itoa(nr_of_terminals, tempString, 10));
#endif
        }
        else if (0 == strcmp(url, "list_terminals"))
        {
          /*build terminal list string*/
          strcpy(terminalListString, "");
          for (i = 0; (i < nr_of_terminals); i++)
          {
            snprintf(tempString, sizeof(tempString), oneTerminal,
                itoa(terminalList[i].id, tempString2, 10),
                terminalList[i].cardsSupported[0],
                terminalList[i].cardsSupported[1],
                terminalList[i].cardsSupported[2],
                terminalList[i].transactionsSupported[0],
                terminalList[i].transactionsSupported[1],
                terminalList[i].transactionsSupported[2]);
            strcat(terminalListString, tempString);
          }
          /*create and send responses*/
          snprintf(pageBuffer, sizeof(pageBuffer), listTerminalPage,
              itoa(nr_of_terminals, tempString, 10), terminalListString);
        }
        else
        {
          /*create and send responses*/
          snprintf(pageBuffer, sizeof(pageBuffer), badPage);
        }
      }
    }
    printf("\n");
    return send_page(connection, pageBuffer, MHD_HTTP_OK);
  }
  else if (0 == strcmp(method, "POST"))
  {
    printf("POST");
    struct connection_info_struct *con_info = *con_cls;

    if (0 != *upload_data_size)
    {
      printf("\tUPLOAD size: %d\n", (unsigned int)*upload_data_size);
      MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
      *upload_data_size = 0;

      return MHD_YES;
    }
    else
    {
      printf("\tNO UPLOAD\n");
      /* Now it is safe to open and inspect the file before calling send_page with a response */
      return send_page(connection, con_info->answerstring, con_info->answercode);
    }
  }
  else
  {
    /* unexpected method */
    snprintf(pageBuffer, sizeof(pageBuffer), errorPage);
    return send_page(connection, pageBuffer, MHD_HTTP_OK);
  }
  return MHD_NO;
}

int main(int argc, char ** argv)
{
  size_t i;
  struct MHD_Daemon * d;
  if (argc != 2)
  {
    printf("%s PORT\n", argv[0]);
    return 1;
  }
  //init
  for (i = 0; i < 100; i++)
  {
    terminalList[i].id = 0;
    strcpy(terminalList[i].cardsSupported[0], "");
    strcpy(terminalList[i].cardsSupported[1], "");
    strcpy(terminalList[i].cardsSupported[2], "");
    strcpy(terminalList[i].transactionsSupported[0], "");
    strcpy(terminalList[i].transactionsSupported[1], "");
    strcpy(terminalList[i].transactionsSupported[2], "");
  }
  d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, atoi(argv[1]),
  NULL,
  NULL, &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
      request_completed, NULL, MHD_OPTION_END);
  if (d == NULL) return 1;
  (void) getc(stdin);
  MHD_stop_daemon(d);
  return 0;
}

