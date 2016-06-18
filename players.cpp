#include "players.h"
#ifndef NDEBUG
#include "stdio.h"
#endif


map <void*, Index > playerMgrIndexes;
map <Index, void*> playerMgrReverse;
Player* playerMgrVector = new Player[8];
Index playerMgrSize = 0;
Index playerMgrCapacity = 8;

void PlayersAdd(void* mg_conn){
	if (playerMgrCapacity == playerMgrSize) {
		Player* copy =  new Player[playerMgrCapacity << 1];
		memcpy(copy, playerMgrVector, playerMgrCapacity * sizeof(Player));
		playerMgrCapacity = playerMgrCapacity << 1;
		delete [] playerMgrVector;
		playerMgrVector = copy;
	}
	playerMgrIndexes[mg_conn] = playerMgrSize;
	playerMgrReverse[playerMgrSize] = mg_conn;
	Player* player = &playerMgrVector[playerMgrSize];
	player->player = 0;
	player->location[0] = 0;
	player->location[1] = 0;
	player->location[2] = 0;
	player->size = 0;
	playerMgrSize++;
#ifndef NDEBUG	
	printf("Player added.\n");
#endif
}

void PlayersRemove(void* mg_conn){
	Index loc = playerMgrIndexes[mg_conn];
	Player* player = &playerMgrVector[loc];
	player->location[0] = 0;
	player->location[1] = 0;
	player->location[2] = 0;
	player->size = 0;
	if (loc < playerMgrSize - 1) {
		playerMgrVector[loc] = playerMgrVector[playerMgrSize - 1];
		void* swapped = playerMgrReverse[playerMgrSize - 1];
		playerMgrIndexes[swapped] = loc;
		playerMgrReverse[loc] = swapped;
	}
	
	playerMgrIndexes.erase(mg_conn);
	playerMgrReverse.erase(playerMgrSize - 1);
	playerMgrSize--;
}
