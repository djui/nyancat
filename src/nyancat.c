#include <stdio.h>

static const int   WIDTH=60;
static const int   ANGLE=4;
static const int   DELAY=50000;
static const int   COLOURS[] = {31, 33, 32, 34, 35}; // r,(o,)y,g,b,p
static const char  FLAG[] = "`*.,*'^";
static const char* CAT[] = {
  "         ",
  "         ",
  " ,---/V\\ ",
  "~|__(o.o)",
  " U U U U ",
  "         ",
  "         ",
  " ,---/V\\ ",
  "~|__(o.o)",
  "  UU  UU "
};

int main(void) {
  int i=0, x, y, t, loop=1;
  const int COLOURS_LEN = sizeof(COLOURS) / sizeof(int);
  const int FLAG_LEN    = sizeof(FLAG)    / sizeof(char) - 1;
  printf("%d\n", FLAG_LEN);
  
  while (loop) {
    for (y = 0; y < COLOURS_LEN; y++) { // line loop
      printf("\x1b[1;%dm", COLOURS[y]); // set rainbow line colour
      for (x = 0; x < WIDTH - ANGLE*(COLOURS_LEN-y); x++) // rainbow line
        putchar(FLAG[(x + (FLAG_LEN-y)+i) % FLAG_LEN]); // print rainbow character
      printf("\x1b[0m"); // clear colour
      for (t = ANGLE; t < ANGLE * (COLOURS_LEN-y); t++) // print distance holder
        putchar(' ');
      printf("\x1b[1;37m"); // set bright color for cat
      puts(CAT[y%COLOURS_LEN + (i%10<COLOURS_LEN ? 0 : COLOURS_LEN)]); // cat
    }
    
    i++;
    usleep(DELAY); // wait x ms
    printf("\x1b[%dA", COLOURS_LEN); // move up before loop
  }

  puts("\x1b[0m"); // reset colors
  return 0;
}
