#include "uid.h"

UID _NextUID = 1;
list <UID> _Returned;

UID GetNextUID() {
	if (_Returned.size()) {
		UID id = _Returned.front();
		_Returned.pop_front();
		return id;
	} else {
	    return _NextUID++;
	}
}

void ReturnUID(UID giveBack) {
	_Returned.push_back(giveBack);
}