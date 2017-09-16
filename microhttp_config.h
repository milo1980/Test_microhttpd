/*
 * microhttp_config.h
 *
 *  Created on: 16/09/2017
 *      Author: Milorad
 */

#ifndef MICROHTTP_CONFIG_H_
#define MICROHTTP_CONFIG_H_

#define POSTBUFFERSIZE  512
#define MAXCLIENTS      2

#define GET             0
#define POST            1

extern const char * busypage;
extern const char * completepage;
extern const char * servererrorpage;
extern const char * createTerminalPostPage;
extern const char * createTerminalJsonPage;
extern const char * listTerminalPage;
extern const char * oneTerminal;
extern const char * basePage;
extern const char * badPage;
extern const char * submitPage;
extern const char * errorPage;
extern const char * askIdPage;
extern const char* answerIdOkPage;
extern const char* answerIdNokPage;


#endif /* MICROHTTP_CONFIG_H_ */
