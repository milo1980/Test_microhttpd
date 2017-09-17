/*
 * main.c
 *
 *  Created on: 14/09/2017
 *      Author: Milorad
 */
#include <sys/types.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <microhttpd.h>

#include "microhttp_handler.h"
#include "terminal_manager.h"

extern void TestUnit_Main();

int main(int argc, char ** argv)
{
  struct MHD_Daemon * d;
  uint16_t PORT;
  bool unitTest = false;

  if (argc == 3)
  {
    PORT = atoi(argv[1]);
    if (0 == strcmp(argv[2], "true"))
    {
      unitTest = true;
    }
  }
  else if (argc == 2)
  {
    PORT = atoi(argv[1]);
  }
  else
  {
    /*default port*/
    PORT = 8080;
  }

  if (unitTest == true)
  {
    TestUnit_Main();
  }

  /*terminal list initialization*/
  TerminalList_Init();

  /*start server*/
  d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT,
  NULL,
  NULL, &microhttp_answerToConnection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
      microhttp_requestCompleted, NULL, MHD_OPTION_END);
  if (d == NULL) return 1;

  /*for ENTER terminate server*/
  (void) getc(stdin);
  /*stop service*/
  MHD_stop_daemon(d);
  return 0;
}

