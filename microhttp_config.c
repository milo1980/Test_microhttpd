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

