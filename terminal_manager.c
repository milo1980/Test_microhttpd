/*
 * terminal_manager.c
 *
 *  Created on: 16/09/2017
 *      Author: Milorad
 */
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "terminal_manager.h"

/*private variable declaration*/
static terminalinfo_t terminalList[100];
static uint16_t nr_of_terminals = 0;

void TerminalList_Init()
{
  uint16_t i;

  for (i = 0; i < MAX_NO_OF_TERMINALS; i++)
  {
    terminalList[i].id = 0;
    strcpy(terminalList[i].cardsSupported[0], "");
    strcpy(terminalList[i].cardsSupported[1], "");
    strcpy(terminalList[i].cardsSupported[2], "");
    strcpy(terminalList[i].transactionsSupported[0], "");
    strcpy(terminalList[i].transactionsSupported[1], "");
    strcpy(terminalList[i].transactionsSupported[2], "");
  }
  nr_of_terminals = 0;
}

void TerminalList_Add(terminalinfo_t * const terminal)
{
  if (terminal != NULL)
  {
    /*copy information*/
    memcpy(&terminalList[nr_of_terminals], terminal, sizeof(terminalinfo_t));
    /*increment number of terminals*/
    nr_of_terminals++;
    /*circular buffers*/
    if (nr_of_terminals >= MAX_NO_OF_TERMINALS)
    {
      nr_of_terminals = 0;
    }
  }
}

void TerminalList_Get(terminalinfo_t * const terminal, unsigned int index)
{
  if ((terminal != NULL) && (index < MAX_NO_OF_TERMINALS))
  {
    /*copy information*/
    memcpy(terminal, &terminalList[index], sizeof(terminalinfo_t));
  }
}

unsigned int TerminalList_GetNumber()
{
  return nr_of_terminals;
}

void * TerminalList_GetFromID(unsigned int id)
{
  void * ret_value;
  uint16_t i;

  ret_value = NULL;
  if (nr_of_terminals == 0)
  {
    /*nothing to do*/
  }
  else
  {
    for (i = 0; i < nr_of_terminals; i++)
    {
      if (terminalList[i].id == id)
      {
        ret_value = &terminalList[i];
      }
    }
  }

  return ret_value;
}

