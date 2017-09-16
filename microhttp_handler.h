/*
 * microhttp_handler.h
 *
 *  Created on: 16/09/2017
 *      Author: Milorad
 */

#ifndef MICROHTTP_HANDLER_H_
#define MICROHTTP_HANDLER_H_

extern int microhttp_answerToConnection(void * cls, struct MHD_Connection * connection,
    const char * url, const char * method, const char * version,
    const char * upload_data, size_t * upload_data_size, void ** con_cls);

extern void microhttp_requestCompleted(void *cls, struct MHD_Connection *connection,
    void **con_cls, enum MHD_RequestTerminationCode toe);



#endif /* MICROHTTP_HANDLER_H_ */
