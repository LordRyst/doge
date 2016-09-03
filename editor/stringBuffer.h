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
int _stringHeapTop;
_string* _firstString;
_string* _lastString;
_string* _smallString;
_string* _largeString;
_string* _currentString;
int _currentOffset;

void _removeFromStrings(_string begone);
char atEndOfString();
int lengthOfString(_string theString);
void _scoochAndInsert(char ch);
char** printScreen(int xSize, int ySize, char cursor, char wiki);
void moveCursorUp();
void moveCursorDown();
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
