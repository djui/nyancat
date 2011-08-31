#include <stdio.h>
#include <termios.h>  // kbhit
#include <sys/time.h> //
#include <string.h>   //
#include <unistd.h>   //
#include <mikmod.h>   // MikMod
#include "song.h"

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

// From mmio/mmio.c
static long _iobase = 0;

static BOOL _mr_eof(MREADER* reader) {
  return feof(((MFILEREADER *)reader)->file); // TODO
}

static BOOL _mr_read(MREADER *reader, void *ptr, size_t size) {
  return fread(ptr, size, 1, ((MFILEREADER *)reader)->file); // TODO
}

static int _mr_get(MREADER *reader) {
  return fgetc(((MFILEREADER *)reader)->file); // TODO
}

static BOOL _mr_seek(MREADER *reader, long offset, int whence) {
  return fseek(((MFILEREADER *)reader)->file, (whence==SEEK_SET) ? offset+_iobase : offset, whence); // TODO
}

static long _mr_tell(MREADER *reader) {
  return ftell(((MFILEREADER *)reader)->file)->_iobase; // TODO
}

int main() {
  int i=0, x, y, t;
  const int COLOURS_LEN = sizeof(COLOURS) / sizeof(int);
  const int FLAG_LEN    = sizeof(FLAG)    / sizeof(char) - 1;
  
  MODULE *module;
  MREADER *mreader;
  MikMod_RegisterAllDrivers();
  MikMod_RegisterAllLoaders();
  md_mode |= DMODE_SOFT_MUSIC;
  MikMod_Init("");

  mreader = (MREADER *)calloc(1, sizeof(MREADER));
  mreader->Eof  = &_mr_eof;
  mreader->Read = &_mr_read;
  mreader->Get  = &_mr_get;
  mreader->Seek = &_mr_seek;
  mreader->Tell = &_mr_tell;

  module = Player_LoadGeneric(mreader, 64, 0);
  // module.loop = true; // module.wrap = true;
  Player_Start(module);
  
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
  
  puts("\x1b[0m"); // reset colours
  Player_Stop();
  Player_Free(module);
  MikMod_Exit();
  return 0;
}
