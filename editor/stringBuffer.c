#include "stringBuffer.c"

void initSB(char* fileName) {
  ifstream file;
  file.open(fileName);
  if(file.is_open()) {
    int fileSize = file.fileSize();
    if (fileSize < 512) {
      fileSize = 512;
    }
    fileSize << 1;
    _charHeap = malloc(fileSize);
    _charHeapSize = fileSize;
    while(!file.eof()) {
      //TODO read file into _charHeap
    }
    _stringHeap = malloc(sizeof(_string) * 16);
    _stringHeapSize = 16;
    _stringHeap* myStr = _stringHeap[0];
    myStr->string = _charHeap;
    myStr->nextString = 0;
    myStr->prevString = 0;
    myStr->nextMemory = 0;
    myStr->prevMemory = 0;
    myStr->nextSize = 0;
    myStr->prevSize = 0;
    _firstString = myStr;
    _lastString = myStr;
    _smallString = myStr;
    _largeString = myStr;
    _currentString = myStr;
    _currentOffset = 0;
    _lineIndex = 1;
    _lineOffset = 0;
  } else {
    printf("Could not read or create file.\n");
    exit(1);
  }
}

inline bool moveCursorLeft() {
  if (_currentOffset > 0) {
    _currentOffset--;
  } else if (_currentString->prevString) {
    _currentString = _currentString->prevString;
    char* ptrBegin = _currentString->string;
    char* ptrEnd;
    if(_currentString->nextMemory) {
      ptrEnd = _currentString->nextMemory.string;
    } else {
      ptrEnd = _charHeap + _charHeapSize;
    }
    _currentOffset = ptrEnd - ptrBegin -1;//ptr is the next string in memory or off the end.
  } else {//Begining of file
    return false;
  }
  return true;
}

inline bool moveCursorRight() {
  char* ptrBegin = _currentString->string;
  char* ptrEnd;
  if (_currentString->nextMemory) {
    ptrEnd = _currentString->nextMemory.string;
  } else {
    ptrEnd = _charHeap + _charHeapSize;
  }
  int length = ptrEnd - ptrBegin;
  if (_currentOffset + 1 < length) {
    _currentOffset++;
  } else if (_currentString->nextString) {
    _currentString = _currentString->nextString;
    _currentOffset = 0;
  } else {//end of file
    return false;
  }
  //Check if we moved to next line.
  return true;
}

void moveCursorUp() {
  int backspaces = 0;
  int offset = 0;
  char returns = 2;
  while (returns > 0 && moveCursorLeft()) {//check for beginning of file.
    backspaces++;
    if (_currentString->string[_currentOffset] == '\n'){
      returns--;
      if (returns == 1) {
	offset = backspaces - 1;
	backspaces = 0;
      }
    }
  }
  if (backspaces < offset) {
    offset = backspaces;
  }
  if (_currentString->string == _firstString && _currentOffset == 0) {
    offset --;
  }
  for (offset; offset > 0 && moveCursorRight(); offset--);
}

void moveCursorDown() {
  int forwards = 0;
  int offset = 0;
  while (moveCursorLeft() && _currentString->string[_currentOffset] != '\n') {
    offset++;
  }
  if (_currentString->string[_currentOffset] == '\n') {
    offset++;
  }
  while (moveCursorRight() && _currentString->string[_currentOffset] != '\n') {
  }
  for (offset; offset > 0 && moveCursorRight() && _currentString->string[_currentOffset] != '\n'; offset--);
}

char** printScreen(int xSize, int ySize,
		   int lineNum, int lineOffset,
		   char cursor, char wiki) {
  char** screen = malloc(xSize * ySize);
  int index = 0;
  int goBackLines = lineNum - _lineIndex;
  _string* firstPrintLine = _currentString;
  int firstPrintCharacter = _currentOffset - 1;
  while (goBackLines < 0) {
    for (int thisStringPos = firstPrintCharacter; thisStringPos >= 0 && firstPrintLine->string[thisStringPos] != '\n'; thisStringPos--};
    if (firstPrintLine->string[thisStringPos] == '\n') {
      goBackLines--;
    } else if (thisStringPos < 0) {
      char* ptrLast = firstPrintLine->string;
      if (firstPrintLine->prevString) {
	firstPrintLine = firstPrintLine->prevString;
	char* beginLine = firstPrintLine->string;
	int length = ptrLast - beginLine;
	thisStringPos = length - 2;//Null terminator at length - 1
      } else {
	goBackLines = 0;
	thisStringPos = 0;
	break;
      }
    }
  }
  if (goBackLines < 0) {

  } else if (goBackLines > 0) {
  
  } else {

  }
}

char atEndOfString() {
  int length = lengthOfString(_currentString);
  return _currentOffset == length - 1;
}

inline int lengthOfString(_string theString) {
  return _theString->nextMemory.string - _currentString->string;
}

char isStringFree(_string check) {
  if (_smallString) {
    _string point = _smallString;
    while (point && point != check) {
      point = point->nextSize();
    }
    if (point && point == check) {
      return true;
    }
  }
  return false;
}

void swapSize(_string first, _string second) {
  _string prev = first->prevSize;
  _string next = second->nextSize;
  if (prev) {
    prev->nextSize = second;
  }
  if (next) {
    next->prevSize = first;
  }
  first->prevSize = second;
  first->nextSize = next;
  second->prevSize = prev;
  second->nextSize = first;
}

void deleteString(_string begone) {
  for (int i = 0; i < _stringHeapTop; i++) {
    if (_stringHeap[i] == begone) {
      _string top = _stringHeap[--_stringHeapTop];
      if (begone->nextSize) {
	begone->nextSize->prevSize = begone->prevSize;
      }
      if (begone->prevSize) {
	begone->prevSize->nextSize = begone->nextSize;
      }
      
    }
  }
}

void extendStringForward(_string toExtend) {
  _string nextMemory = toExtend->nextMemory;
  if (nextMemory && isStringFree(nextMemory)) {
    if (lengthOfString(nextMemory) > 1) { //shorted, and make sure memory is sorted.
      nextMemory->string++;
      int length = lengthOfString(nextMemory);
      _string larger = nextMemory->prevSize;
      while (larger && lengthOfString(larger) > length) {
	//swap places in size;
	swapSize(larger, nextMemory);
	larger = larger->prevSize;
      }
    } else { //String Size 1
      nextMemory->string++;
      
    }
  }
}

void extendStringBackward(_string toExtend) {
  
}

void insertChar(char ch) {//most likely at beginning of string
  if (_currentOffset == 0) {
    _string memPrev = _currentString->prevMemory;
    if (isStringFree(memPrev)) {
      if (lengthOfString(memPrev) > 1) {
	_currentString->string--;
	_currentString->string[0] = ch;
	//check if prevMem needs moved to be a smaller size;
      } else {//string size one, delete.
	if (memPrev->prevMemory) {
	  memPrev->prevMemory->nextMemory = _currentString;
	}
	
      }
    }
  }
}

void deleteChar();
void backspace();
int getLineIndex();
int getLineOffset();
bool saveAndJump();//return jump success
void exportHTML();
char* getWord();
