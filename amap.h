#ifndef _AMAP_H_
#define _AMAP_H_

#include <map>
#include "uid.h"

using namespace std;

template <typename T>
struct StaticAMap {
	T* vector;
	Index size;
	UID* ids;
	map <UID, Index> indexes;
};

template <typename T>
class AMap {
	private:
		map < UID, Index > indexes;
		map <Index, UID> reverse;
		T* vector;
		Index size;
		Index capacity;
	public:
		AMap<T>();
		void add(UID id);
		void remove(UID id);
		StaticAMap<T> getStatic();	
};

#endif