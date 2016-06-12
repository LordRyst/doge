#ifndef _UID_H_
#define _UID_H_

#include <stdint.h>
//int8_t
//int16_t
//int32_t
//int64_t
#include <list>

using namespace std;

typedef int32_t UID;
typedef int16_t Index;

UID GetNextUID();
void ReturnUID(UID giveBack);

#endif