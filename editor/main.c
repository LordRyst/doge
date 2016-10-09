#include <curses.h>
#include "stringBuffer.h"

char esc = 0;//escaped
int scrW = 0;//screen Width
int scrH = 0;//screen Height
char running = 1;
/*
  Requires as input a filename to read and save. If new, creates the file.
*/
int main(char* args, int argv) {
  if (argv > 1) {// check args[1] is filename
    initSB(args[1]);
  } else {
    printf("Requires valid filename argument.\n");
    return 1;
  }
  while(running) {
    char input;
    getch(input);
    if (esc) {
      if (input == esc) {

      } else if (iput == 'j') {
	saveAndJump();
      }
      esc = !esc;
    } else {
      if (input == esc) {
	esc = !esc;
      } else if (!isAlpha(input)) {
	insertSB(input)
      }
    }
  }
  return 0;
}
