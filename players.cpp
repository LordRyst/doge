#include "players.h"

map < mg_connection*, Index > playerMgrIndexes;
map <Index, mg_connection*> playerMgrReverse;
Player* playerMgrVector = new Player[8];
Index playerMgrSize = 0;
Index playerMgrCapacity = 8;

void PlayersAdd(mg_connection* mg_conn){
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
	printf("Player added.\n");
}

void PlayersRemove(mg_connection* mg_conn){
	Index loc = playerMgrIndexes[mg_conn];
	Player* player = &playerMgrVector[loc];
	player->location[0] = 0;
	player->location[1] = 0;
	player->location[2] = 0;
	player->size = 0;
	if (loc < playerMgrSize - 1) {
		playerMgrVector[loc] = playerMgrVector[playerMgrSize - 1];
		mg_connection* swapped = playerMgrReverse[playerMgrSize - 1];
		playerMgrIndexes[swapped] = loc;
		playerMgrReverse[loc] = swapped;
	}
	
	playerMgrIndexes.erase(mg_conn);
	playerMgrReverse.erase(playerMgrSize - 1);
	playerMgrSize--;
}
