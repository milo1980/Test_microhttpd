/*
 * test_unit.c
 *
 *  Created on: 16/09/2017
 *      Author: Milorad
 */
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "terminal_manager.h"

static terminalinfo_t terminalTest1;
static terminalinfo_t terminalTest2;
static terminalinfo_t * pTerminal;

static void TestUnit_Test1Stub()
{
  printf("\nTest1..");
}
static void TestUnit_Test1Check()
{
  if (0 != TerminalList_GetNumber())
  {
    printf("FAILED");
  }
  printf("PASSED");
}
static void TestUnit_Test1()
{
  TestUnit_Test1Stub(); /*call test stub*/

  TerminalList_Init(); /*call function to test*/

  TestUnit_Test1Check(); /*call function checker*/
}

static void TestUnit_Test2Stub()
{
  printf("\nTest2..");
  TerminalList_Init();
  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1234;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "b");
  strcpy(terminalTest1.cardsSupported[2], "c");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
}
static void TestUnit_Test2Check()
{
  if (1 != TerminalList_GetNumber())
  {
    printf("FAILED");
    return;
  }
  printf("PASSED");
}
static void TestUnit_Test2()
{
  TestUnit_Test2Stub(); /*call test stub*/

  TerminalList_Add(&terminalTest1); /*call function to test*/

  TestUnit_Test2Check(); /*call function checker*/
}

static void TestUnit_Test3Stub()
{
  printf("\nTest3..");
  TerminalList_Init();
}
static void TestUnit_Test3Check()
{
  if (0 != TerminalList_GetNumber())
  {
    printf("FAILED");
    return;
  }
  printf("PASSED");
}
static void TestUnit_Test3()
{
  TestUnit_Test3Stub(); /*call test stub*/

  TerminalList_Add(NULL); /*call function to test*/

  TestUnit_Test3Check(); /*call function checker*/
}

static void TestUnit_Test4Stub()
{
  printf("\nTest4..");
  TerminalList_Init();

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1234;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "b");
  strcpy(terminalTest1.cardsSupported[2], "c");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1001;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "");
  strcpy(terminalTest1.cardsSupported[2], "");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest2, 0, sizeof(terminalinfo_t));
}
static void TestUnit_Test4Check()
{
  if (2 != TerminalList_GetNumber())
  {
    printf("FAILED");
    return;
  }
  if (0 != memcmp(&terminalTest1, &terminalTest2, sizeof(terminalinfo_t)))
  {
    printf("FAILED");
    return;
  }
  printf("PASSED");
}
static void TestUnit_Test4()
{
  TestUnit_Test4Stub(); /*call test stub*/

  TerminalList_Get(&terminalTest2, 1); /*call function to test*/

  TestUnit_Test4Check(); /*call function checker*/
}

static void TestUnit_Test5Stub()
{
  printf("\nTest5..");
  TerminalList_Init();

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1234;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "b");
  strcpy(terminalTest1.cardsSupported[2], "c");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1001;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "");
  strcpy(terminalTest1.cardsSupported[2], "");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest2, 0, sizeof(terminalinfo_t));
}
static void TestUnit_Test5Check()
{
  if (2 != TerminalList_GetNumber())
  {
    printf("FAILED");
    return;
  }
  if (0 == memcmp(&terminalTest1, &terminalTest2, sizeof(terminalinfo_t)))
  {
    printf("FAILED");
    return;
  }
  printf("PASSED");
}
static void TestUnit_Test5()
{
  TestUnit_Test5Stub(); /*call test stub*/

  TerminalList_Get(&terminalTest2, 100); /*call function to test*/

  TestUnit_Test5Check(); /*call function checker*/
}

static void TestUnit_Test6Stub()
{
  printf("\nTest6..");
  TerminalList_Init();
}
static void TestUnit_Test6Check()
{
  if (0 != TerminalList_GetNumber())
  {
    printf("FAILED");
    return;
  }
  printf("PASSED");
}
static void TestUnit_Test6()
{
  TestUnit_Test6Stub(); /*call test stub*/

  TerminalList_Get(NULL, 0); /*call function to test*/

  TestUnit_Test6Check(); /*call function checker*/
}

static void TestUnit_Test7Stub()
{
  printf("\nTest7..");
  TerminalList_Init();

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1234;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "b");
  strcpy(terminalTest1.cardsSupported[2], "c");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1001;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "");
  strcpy(terminalTest1.cardsSupported[2], "");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest2, 0, sizeof(terminalinfo_t));
}
static void TestUnit_Test7Check()
{
  if (2 != TerminalList_GetNumber())
  {
    printf("FAILED");
    return;
  }
  if (NULL == pTerminal)
  {
    printf("FAILED");
    return;
  }
  printf("PASSED");
}
void static TestUnit_Test7()
{
  TestUnit_Test7Stub(); /*call test stub*/

  pTerminal = TerminalList_GetFromID(1001); /*call function to test*/

  TestUnit_Test7Check(); /*call function checker*/
}

static void TestUnit_Test8Stub()
{
  printf("\nTest8..");
  TerminalList_Init();

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1234;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "b");
  strcpy(terminalTest1.cardsSupported[2], "c");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest1, 0, sizeof(terminalinfo_t));
  terminalTest1.id = 1001;
  strcpy(terminalTest1.cardsSupported[0], "a");
  strcpy(terminalTest1.cardsSupported[1], "");
  strcpy(terminalTest1.cardsSupported[2], "");
  strcpy(terminalTest1.transactionsSupported[0], "x");
  strcpy(terminalTest1.transactionsSupported[1], "y");
  strcpy(terminalTest1.transactionsSupported[2], "z");
  TerminalList_Add(&terminalTest1);

  memset(&terminalTest2, 0, sizeof(terminalinfo_t));
  pTerminal = NULL;
}
static void TestUnit_Test8Check()
{
  if (2 != TerminalList_GetNumber())
  {
    printf("FAILED");
    return;
  }
  if (NULL != pTerminal)
  {
    printf("FAILED");
    return;
  }
  printf("PASSED");
}
static void TestUnit_Test8()
{
  TestUnit_Test8Stub(); /*call test stub*/

  pTerminal = TerminalList_GetFromID(1000); /*call function to test*/

  TestUnit_Test8Check(); /*call function checker*/
}

void TestUnit_Main()
{
  TestUnit_Test1();
  TestUnit_Test2();
  TestUnit_Test3();
  TestUnit_Test4();
  TestUnit_Test5();
  TestUnit_Test6();
  TestUnit_Test7();
  TestUnit_Test8();
  printf("\n");
}

