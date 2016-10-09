#include "messages.h"
#ifndef NDEBUG
  #include <stdio.h>
#endif

vector <message> forward;

void MessagesAdd(void* mg_conn, char* data, int size){
  int remains = size;
  while (remains > 0) {
    int shift = size - remains;
    char code = data[shift] >> 4;
    char type = data[shift] & 16;
    char* address = data + shift;
    switch (code) {
    case 0:
      switch (type) {
      case 0: // FORWARD
	forward.push_back(message());
	forward[forward.size() - 1].mg_conn = mg_conn;
	forward[forward.size() - 1].data = address;
	break;
#ifndef NDEBUG
      default:
	printf("MessagesAdd bad type.\n");
	break;
#endif
      }
      break;
    case 1:
      //messages2Bytes(mg_conn, address, 2);
      break;
#ifndef NDEBUG
    default:
      printf("MessagesAdd bad code.\n");
      break;
#endif      
    }
    remains -= 1 << code;
  };
}
