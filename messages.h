#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include "mongoose.h"
#include "uid.h"

using namespace std;

struct Message {
	mg_connection* player;
	char* data;
	int size;
};

void MessagesAdd(mg_connection* mg_conn, char* data, int size);

#endif
