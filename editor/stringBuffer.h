#ifndef _STRING_BUFFER_H_
#define _STRING_BUFFER_H_

char _charHeap[];
int _charHeapSize;
struct _string{
  char* string;
  _string* nextMemory;
  _string* prevMemory;
  _string* nextString;
  _string* prevString;
  _string* nextSize;
  _string* prevSize;
};

_string _stringHeap[];
int _stringHeapSize;
_string* _firstString;
_string* _lastString;
_string* _smallString;
_string* _largeString;
_string* _currentString;
int _currentOffset;

char** printScreen(int xSize, int ySize, char cursor, char wiki);
char moveCursorUp();
char moveCursorDown();
char moveCursorLeft();
char moveCursorRight();
void insertChar(char ch);
void deleteChar();
void backspace();
int getLineIndex();
int getLineOffset();
bool saveAndJump();//return jump success
void exportHTML();
char* getWord();

#endif
