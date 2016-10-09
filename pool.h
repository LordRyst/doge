#ifndef _POOL_H_
#define _POOL_H_

#ifndef NDEBUG
#include <stdio.h>
#endif

struct pool {
  void* poolBegin;
  char bytes;
  int cap;
  int top;
  int nextAvailable[];
  int nextCap;
  int nextTop;
};

void* newFromPool() {
  if (nextTop >= 0) {
    int index = nextAvailable[nextTop--];
    return poolBegin + bytes * index;
  } else {
    return 0;
  }
}

void deleteFromPool(int index) {
  if (index != top) {
    if (nextTop != nextCap) {

    } else {//resize nextAvailable
      nextAvailable = realloc(nextAvailable, nextCap * 2 * typeof(nextAvailable));
    }
  } else {
    top--;
  }
}

char initPool(int capacity, char objSize) {
  poolBegin = malloc(capacity, objSize);
  if (poolBegin) {
    bytes = objSize;
    cap = capacity;
    top = 0;
  } else {
    top = 0;
    cap = 0;
    bytes = 0;
    return 0;
  }
}



#endif
