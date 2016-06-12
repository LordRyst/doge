#include "messages.h"

Message* messageMgrVector = new Message[8];
Index messageMgrSize = 0;
Index messageMgrCapacity = 8;

void MessagesAdd(mg_connection* mg_conn, char* data, int size){
	if (size) {
		char code = data[0] >> 4;
		switch (code) {
		case 0:// messages1Byte(mg_conn, data, size); break;
		case 1:// messages2Bytes(mg_conn, data, size); break;
		case 2:// messages4Bytes(mg_conn, data, size); break;
		case 3:// messages8Bytes(mg_conn, data, size);
		  break;
		}
	}
	
	/*if (messageMgrCapacity == messageMgrSize) {
		Message* copy =  new Message[messageMgrCapacity << 1];
		memcpy(copy, messageMgrVector, messageMgrCapacity * sizeof(Message));
		messageMgrCapacity = messageMgrCapacity << 1;
		delete [] messageMgrVector;
		messageMgrVector = copy;
	}
	Message* message = &messageMgrVector[messageMgrSize];
	message->data = data;
	message->size = size;
	message->player = mg_conn
	messageMgrSize++;*/
}
