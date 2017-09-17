/*
 * microhttp_config.c
 *
 *  Created on: 16/09/2017
 *      Author: Milorad
 */

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
    -------------------------<br>\n\
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
     -------------------------<br>\n\
     %s\n\
     </body></html>";

const char * oneTerminal =
    "ID:%s<br>\n\
     Cards Supported: %s %s %s<br>\n\
     Transactions Supported: %s %s %s<br>\n\
     ----<br>";

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

const char* askIdPage =
    "<html><head><title>libmicrohttpd server</title></head>\n\
     <body>\n\
     <p>Current number of terminals : %s </p>\n\
     <p>Enter Terminal ID</p>\
     <form action=\"/idpost\" method=\"post\">\
       <input name=\"id\" type=\"text\"\
       <input type=\"submit\" value=\" id no. \"></form>\
     </body></html>";

const char* answerIdOkPage =
    "<html><head><title>libmicrohttpd server</title></head>\n\
     <body>\n\
     <p>Current number of terminals : %s </p>\n\
     <p>Terminal Info</p>\
     ID:%s<br>\n\
     Cards Supported: %s %s %s<br>\n\
     Transactions Supported: %s %s %s<br>\n\
     </body></html>";

const char* answerIdNokPage =
    "<html><head><title>libmicrohttpd server</title></head>\n\
     <body>\n\
     <p>Current number of terminals : %s </p>\n\
     <p>Terminal Not Found!</p>\
     </body></html>";

