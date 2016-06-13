#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include "mongoose.h"
#include "uid.h"

using namespace std;

void MessagesAdd(mg_connection* mg_conn, char* data, int size);
void messages1Byte(mg_connection* mg_conn, char* data, int size);

#endif
