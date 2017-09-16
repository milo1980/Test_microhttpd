/*
 * microhttp_handler.c
 *
 *  Created on: 16/09/2017
 *      Author: Milorad
 */
#include <sys/types.h>
//#include <sys/select.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <microhttpd.h>

#include "microhttp_config.h"
#include "terminal_manager.h"




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
#if 0
static char url_args[1024] = "";
#endif

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

#if 0
static int get_url_args(void *cls, enum MHD_ValueKind kind, const char *key,
    const char* value)
{
  strcat(url_args,key);
  strcat(url_args,":");
  if (value != 0)
  {
    strcat(url_args,"\"\"");
  }
  else
  {
    strcat(url_args,value);
  }
  strcat(url_args,"\n");
  return MHD_YES;
}
#endif

void microhttp_requestCompleted(void *cls, struct MHD_Connection *connection,
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
    printf("POST\t%s\tid: %d\n", "DONE", con_info->terminal.id);
    TerminalList_Add(&con_info->terminal);
  }

  free(con_info);
  *con_cls = NULL;
}

int microhttp_answerToConnection(void * cls, struct MHD_Connection * connection,
    const char * url, const char * method, const char * version,
    const char * upload_data, size_t * upload_data_size, void ** con_cls)
{
  size_t i;
  static char pageBuffer[2048] = "";
  static char terminalListString[1024] = "";
  static char tempString[512] = "";
  static char tempString2[64] = "";
  static terminalinfo_t temptermin;
  unsigned int terminnum;

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
#if 1
          terminnum = TerminalList_GetNumber();
          snprintf(pageBuffer, sizeof(pageBuffer), createTerminalPostPage,
              itoa(terminnum, tempString, 10));
#else
          MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND,
              get_url_args, &url_args);
          printf("\n%s",url_args);
          snprintf(pageBuffer, sizeof(pageBuffer), createTerminalJsonPage,
              itoa(nr_of_terminals, tempString, 10));
#endif
        }
        else if (0 == strcmp(url, "list_terminals"))
        {
          /*build terminal list string*/
          strcpy(terminalListString, "");
          terminnum = TerminalList_GetNumber();
          for (i = 0; (i < terminnum); i++)
          {
            TerminalList_Get(&temptermin, i);
            snprintf(tempString, sizeof(tempString), oneTerminal,
                itoa(temptermin.id, tempString2, 10),
                temptermin.cardsSupported[0],
                temptermin.cardsSupported[1],
                temptermin.cardsSupported[2],
                temptermin.transactionsSupported[0],
                temptermin.transactionsSupported[1],
                temptermin.transactionsSupported[2]);
            strcat(terminalListString, tempString);
          }
          /*create and send responses*/
          snprintf(pageBuffer, sizeof(pageBuffer), listTerminalPage,
              itoa(terminnum, tempString, 10), terminalListString);
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


