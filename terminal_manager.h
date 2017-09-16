/*
 * terminal_manager.h
 *
 *  Created on: 16/09/2017
 *      Author: Milorad
 */

#ifndef TERMINAL_MANAGER_H_
#define TERMINAL_MANAGER_H_

#define MAX_NO_OF_TERMINALS 20

typedef struct
{
  char cardsSupported[3][64];
  char transactionsSupported[3][64];
  unsigned int id;
} terminalinfo_t;

extern void TerminalList_Init();
extern void TerminalList_Add(terminalinfo_t * const terminal);
extern void TerminalList_Get(terminalinfo_t * const terminal, unsigned int index);
extern unsigned int TerminalList_GetNumber();


#endif /* TERMINAL_MANAGER_H_ */
