#ifndef _PLAYERS_H_
#define _PLAYERS_H_

#include "uid.h"
#include <map>
#include "mongoose.h"

using namespace std;

struct Player {
	UID player;
	float location[3];
	float size;
};

void PlayersAdd(mg_connection* mg_conn);

void PlayersRemove(mg_connection* mg_conn);

#endif
