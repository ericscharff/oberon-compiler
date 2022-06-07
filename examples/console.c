#include <termios.h>
#include <unistd.h>

static struct termios orig_io;

void Console_StartScreen(void) {
  struct termios io;

  if (tcgetattr(1, &io) != 0) {
    return;
  }
  orig_io = io;
  // Polling read
  io.c_cc[VMIN] = 0;
  io.c_cc[VTIME] = 0;

  // Disable canonical and echo mode
  io.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(1, TCSANOW, &io);
}

void Console_EndScreen(void) {
  tcsetattr(1, TCSANOW, &orig_io);
}

void Console_WriteChar(char c) {
  if (c == '\r') {
    c = '\n';
  }
  c = c & 0x7f;
  write(0, &c, 1);
}

void Console_ReadChar(int *c) {
  char buf;
  read(1, &buf, 1);
  *c = buf;
}
