#include <stdio.h>
#include <termios.h>  // kbhit
#include <sys/time.h> //
#include <string.h>   //
#include <unistd.h>   //

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

int _kbhit() {
  int r;
  fd_set read_fd;
  struct timeval tv = {0};
  struct termios term, oterm;

  tcgetattr(STDIN_FILENO, &oterm);
  memcpy(&term, &oterm, sizeof(term));
  cfmakeraw(&term);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  FD_ZERO(&read_fd);
  FD_SET(STDIN_FILENO, &read_fd);
  r = select(1, &read_fd, NULL, NULL, &tv);
  tcsetattr(STDIN_FILENO, TCSANOW, &oterm);

  return r;
}

int main() {
  int i=0, x, y, t;
  const int COLOURS_LEN = sizeof(COLOURS) / sizeof(int);
  const int FLAG_LEN    = sizeof(FLAG)    / sizeof(char) - 1;
  printf("%d\n", FLAG_LEN);
  
  while (1) {
    for (y = 0; y < COLOURS_LEN; y++) { // line loop
      printf("\x1b[1;%dm", COLOURS[y]); // set rainbow line colour
      for (x = 0; x < WIDTH - ANGLE*(COLOURS_LEN-y); x++) // rainbow line
        putchar(FLAG[(x + (FLAG_LEN-y)+i) % FLAG_LEN]); // print rainbow character
      printf("\x1b[0m"); // clear colour
      for (t = ANGLE; t < ANGLE * (COLOURS_LEN-y); t++) // print distance holder
        putchar(' ');
      printf("\x1b[1m"); // set bright color for cat
      puts(CAT[y%COLOURS_LEN + (i%10<COLOURS_LEN ? 0 : COLOURS_LEN)]); // cat
    }
    
    if (_kbhit()) // key pressed?
      break;
    
    i++;
    usleep(DELAY); // wait x ms
    printf("\x1b[%dA", COLOURS_LEN); // move up before loop
  }

  puts("\x1b[0m"); // reset colors
  return 0;
}
