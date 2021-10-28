#include <stdio.h>

#define N 5

const int move_x[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int move_y[] = {1, 2, 2, 1, -1, -2, -2, -1};
int board[N][N];

void setup(void) {
  for (int i=0; i < N; i++) {
    for (int j=0; j < N; j++) {
      board[i][j] = -1;
    }
  }
}

int solve(int curX, int curY, int curMove) {
  if (curMove == N*N) {
    return 1;
  }
  for (int move=0; move < 8; move++) {
    int newX = curX + move_x[move];
    int newY = curY + move_y[move];
    if ((newX >= 0) && (newX < N) && (newY >= 0) && (newY < N) &&
        (board[newX][newY] == -1)) {
      board[newX][newY] = curMove;
      if (solve(newX, newY, curMove+1)) {
        return 1;
      }
      board[newX][newY] = -1;
    }
  }
  return 0;
}

void printBoard(void) {
  for (int i=0; i < N; i++) {
    for (int j=0; j < N; j++) {
      printf("%4d", board[i][j]);
    }
    printf("\n");
  }
}

int main(void) {
  setup();
  board[0][0] = 0;
  if (solve(0, 0, 1)) {
    printf("Success\n");
  } else {
    printf("Failure\n");
  }
  printBoard();
  return 0;
}
