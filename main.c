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
#include <microhttpd.h>

#include "microhttp_handler.h"
#include "terminal_manager.h"

int main(int argc, char ** argv)
{
  struct MHD_Daemon * d;
  if (argc != 2)
  {
    printf("%s PORT\n", argv[0]);
    return 1;
  }

  /*terminal list initialization*/
  TerminalList_Init();

  /*start server*/
  d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, atoi(argv[1]),
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

