#ifndef _PLAYERS_H_
#define _PLAYERS_H_

#include "uid.h"
#include <map>
#include <string.h>

using namespace std;

struct Player {
	UID player;
	float location[3];
	float size;
};

void PlayersAdd(void* mg_conn);

void PlayersRemove(void* mg_conn);

#endif
