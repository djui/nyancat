#include <stdio.h>
#include <termios.h>  // kbhit
#include <sys/time.h> //
#include <string.h>   //
#include <unistd.h>   //
#include <mikmod.h>   // MikMod
#include "music.h"

static const int   WIDTH=40;
static const int   ANGLE=0;
static const int   DELAY=20000;
static const int   COLOURS[] = {31, 33, 32, 36, 34, 35, 31, 33, 32, 36}; // r,y,g,lb,b,p
//static const int   COLOURS[] = {31, 31, 33, 33, 32, 32, 36, 36, 34, 34}; if you prefer this
static const char  FLAG[] = "`*.,*'^";
static const char* CAT[] = {
  "   __________________",
  "  /             __   \\   __",
  " |  *        * |  \\___|_/  |",
  " __    |       *     |           |",
  "|  \\___|    *   *   /   _      _  \\",
  " \\__   |  *        |   |_|    |_|  |",
  "    \\__|        *  |  ##     o   ##|",
  "       |   *        \\ ##|___|___|#/",
  " /\\____________\\___________/",
  " |___/\\___|     \\___|\\___|",
  "                                   ",
  "                                   ",
  "   __________________",
  "  /             __   \\   __",
  " |  *        * |  \\___|_/  |",
  "       |       *     |           |",
  "     __|    *   *   /   _      _  \\",
  "  __/  |  *        |   |_|    |_|  |",
  " /  ___|        *  |  ##     o   ##|",
  "|__/   |   *        \\ ##|___|___|#/",
  "/ \\____________\\___________/",
  "|___/\\___|     \\___|\\___| "
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

  // Extract module song payload
  char fname[] = "/tmp/file-XXXXXX";
  int fd = mkstemp(fname);
  if (write(fd, src_music_xm, src_music_xm_len) < 0)
    return -1;
  lseek(fd, 0, SEEK_SET);
  FILE *pFile = fdopen(fd, "rb");

  // Load and play the module song
  MODULE *module;
  MikMod_RegisterAllDrivers();
  MikMod_RegisterAllLoaders();
  md_mode |= DMODE_SOFT_MUSIC;
  MikMod_Init("");
  module = Player_LoadFP(pFile, 64, 0);
  module->wrap = 1;
  Player_Start(module);

  // Animation
  while (1) {
    MikMod_Update();
    for (y = 0; y < COLOURS_LEN; y++) { // line loop
      printf("\x1b[1;%dm", COLOURS[y]); // set rainbow line colour
      if (y<3 | y>7){
        for (x = -6; x < WIDTH - ANGLE*(COLOURS_LEN-y); x++) // rainbow line
          putchar(FLAG[(x + (FLAG_LEN-y)+i) % FLAG_LEN]); // print rainbow character
      } else {
        for (x = 0; x < WIDTH - ANGLE*(COLOURS_LEN-y); x++) // rainbow line
          putchar(FLAG[(x + (FLAG_LEN-y)+i) % FLAG_LEN]); // print rainbow character
      }
      printf("\x1b[0m"); // clear colour
      printf("\x1b[1m"); // set bright color for cat
      puts(CAT[y%COLOURS_LEN + (i%20<COLOURS_LEN ? 0 : COLOURS_LEN+2)]); // cat
    }

    if (_kbhit()) // key pressed?
      break;

    i++;
    usleep(DELAY); // wait x ms
    printf("\x1b[%dA", COLOURS_LEN); // move up before loop
  }

  puts("\x1b[0m"); // reset colours
  Player_Stop();
  Player_Free(module);
  MikMod_Exit();
  return 0;
}
