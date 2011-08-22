#include <stdio.h>

static const int COLOURS[] = {33, 32, 34, 36, 31, 35}; // r,y,g,c,b,p
static const char FLAG[] = "`*.,*'^";
static const char* CAT[] = {
  "         ",
  "         ",
  "         ",
  " ,---/V\\ ",
  "~|__(o.o)",
  " U U U U ",
  "         ",
  "         ",
  "         ",
  " ,---/V\\ ",
  "~|__(o.o)",
  "  UU  UU "
};

int main(void) {
  int i=0, x, y, t, loop=1;

  while (loop) {
    for (y = 0; y < 6; y++) {
      printf("\x1b[1;%dm", COLOURS[y]);
      for (x = 0; x < 60-(6-y); x++)
        putchar(FLAG[(x+(7-y)+i)%7]);
      printf("\x1b[0m");
      for (t = 1; t < 6-y; t++)
        putchar(' ');
      printf("\x1b[1;37m");
      puts(CAT[y%6 + (i%10<5 ? 0 : 6)]);
    }
    
    i++;
    usleep(50000);
    puts("\x1b[7A");
  }

  puts("\x1b[0m"); // reset colors
  return 0;
}
