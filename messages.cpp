#include "messages.h"
#ifndef NDEBUG
  #include <stdio.h>
#endif

#define FORWARD 0
#define BACKWARD 0

void MessagesAdd(mg_connection* mg_conn, char* data, int size){
  int remains = size;
  while (remains > 0) {
    int shift = size - remains;
    char code = data[shift] >> 4;
    char* address = data + shift;
    switch (code) {
    case 0:
      messages1Byte(mg_conn, address, 1);
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

void messages1Byte(mg_connection* mg_conn, char* data, int size) {
  char type = data[0] & 255;
  switch (type) {
  case FORWARD:
    //MovementMgrAddForward(mg_conn);
    break;
  }
}
