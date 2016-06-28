#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#include <vector>

using namespace std;

struct message {
  void* mg_conn;
  char* data;
};

void MessagesAdd(void* mg_conn, char* data, int size);

#endif
