#include <ncurses.h>

void Console_StartScreen(void) {
  initscr();
  cbreak();
  nodelay(stdscr, 1);
  scrollok(stdscr, 1);
  noecho();
}

void Console_EndScreen(void) {
  endwin();
}

void Console_WriteChar(char c) {
  if ((c == '\r') || (c == '\n')) {
    printw("\n");
  } else if ((c >= 32) && (c < 127)) {
    printw("%c", c & 0x7f);
  }
}

void Console_ReadChar(int *c) {
  *c = getch();
}
