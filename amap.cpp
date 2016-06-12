#include "amap.h"

using namespace std;

template <typename T>
AMap<T>::AMap() {
	size = 0;
	capacity = 8;
	vector = new T[8];
}

template <typename T>
void AMap<T>::add(UID id) {
	if (capacity == size) {
		T* copy =  new T[capacity << 1];
		memcpy(copy, vector, capacity * sizeof(T));
		capacity = capacity << 1;
		delete [] vector;
		vector = copy;
	}
	indexes[id] = size;
	reverse[size] = id;
	size++;
}
template <typename T>
void AMap<T>::remove(UID id) {
	Index loc = indexes[id];
	if (loc < size - 1) {
		vector[loc] = vector[size - 1];
		UID swapped = reverse[size - 1];
		indexes[swapped] = loc;
		reverse[loc] = swapped;
	}
	indexes.erase(id);
	reverse.erase(size - 1);
	size--;
}

template <typename T>
StaticAMap<T> AMap<T>::getStatic() {
	StaticAMap<T> data;
	data.size = size;
	data.vector = new T[size];
	memcpy(data.vector, vector, size * sizeof(T));
	data.ids = new UID[size];
	for (map<Index, UID>::iterator it = reverse.begin(); it != reverse.end(); it++) {
		data.ids[it->first] = it->second;
	}
	data.indexes = indexes;
	return data;
}