const WIDTH=10
const HEIGHT=6

const variants = [
  {id: 0, points: [[0, 0], [0, 1], [0, 2], [0, 3], [0, 4]]},
  {id: 0, points: [[0, 0], [1, 0], [2, 0], [3, 0], [4, 0]]},
  {id: 1, points: [[0, 0], [1, 0], [-1, 1], [0, 1], [0, 2]]},
  {id: 1, points: [[0, 1], [0, 0], [1, 2], [1, 1], [2, 1]]},
  {id: 1, points: [[0, 2], [-1, 2], [1, 1], [0, 1], [0, 0]]},
  {id: 1, points: [[1, 1], [1, 2], [0, 0], [0, 1], [-1, 1]]},
  {id: 1, points: [[1, 0], [0, 0], [2, 1], [1, 1], [1, 2]]},
  {id: 1, points: [[-1, 1], [-1, 2], [0, 0], [0, 1], [1, 1]]},
  {id: 1, points: [[0, 2], [1, 2], [-1, 1], [0, 1], [0, 0]]},
  {id: 1, points: [[0, 1], [0, 0], [-1, 2], [-1, 1], [-2, 1]]},
  {id: 2, points: [[0, 0], [0, 1], [0, 2], [0, 3], [1, 3]]},
  {id: 2, points: [[-3, 1], [-2, 1], [-1, 1], [0, 1], [0, 0]]},
  {id: 2, points: [[1, 3], [1, 2], [1, 1], [1, 0], [0, 0]]},
  {id: 2, points: [[3, 0], [2, 0], [1, 0], [0, 0], [0, 1]]},
  {id: 2, points: [[0, 0], [0, 1], [0, 2], [0, 3], [-1, 3]]},
  {id: 2, points: [[0, 0], [1, 0], [2, 0], [3, 0], [3, 1]]},
  {id: 2, points: [[0, 3], [0, 2], [0, 1], [0, 0], [1, 0]]},
  {id: 2, points: [[3, 1], [2, 1], [1, 1], [0, 1], [0, 0]]},
  {id: 3, points: [[0, 0], [0, 1], [-1, 2], [0, 2], [-1, 3]]},
  {id: 3, points: [[0, 0], [1, 0], [2, 1], [2, 0], [3, 1]]},
  {id: 3, points: [[-1, 3], [-1, 2], [0, 1], [-1, 1], [0, 0]]},
  {id: 3, points: [[3, 1], [2, 1], [1, 0], [1, 1], [0, 0]]},
  {id: 3, points: [[0, 0], [0, 1], [1, 2], [0, 2], [1, 3]]},
  {id: 3, points: [[-2, 1], [-1, 1], [0, 0], [0, 1], [1, 0]]},
  {id: 3, points: [[1, 3], [1, 2], [0, 1], [1, 1], [0, 0]]},
  {id: 3, points: [[2, 0], [1, 0], [0, 1], [0, 0], [-1, 1]]},
  {id: 4, points: [[0, 0], [1, 0], [0, 1], [1, 1], [0, 2]]},
  {id: 4, points: [[0, 1], [0, 0], [1, 1], [1, 0], [2, 1]]},
  {id: 4, points: [[0, 2], [-1, 2], [0, 1], [-1, 1], [0, 0]]},
  {id: 4, points: [[2, 0], [2, 1], [1, 0], [1, 1], [0, 0]]},
  {id: 4, points: [[1, 0], [0, 0], [1, 1], [0, 1], [1, 2]]},
  {id: 4, points: [[0, 0], [0, 1], [1, 0], [1, 1], [2, 0]]},
  {id: 4, points: [[0, 2], [1, 2], [0, 1], [1, 1], [0, 0]]},
  {id: 4, points: [[1, 1], [1, 0], [0, 1], [0, 0], [-1, 1]]},
  {id: 5, points: [[0, 0], [1, 0], [2, 0], [1, 1], [1, 2]]},
  {id: 5, points: [[0, 2], [0, 1], [0, 0], [1, 1], [2, 1]]},
  {id: 5, points: [[1, 2], [0, 2], [-1, 2], [0, 1], [0, 0]]},
  {id: 5, points: [[0, 0], [0, 1], [0, 2], [-1, 1], [-2, 1]]},
  {id: 6, points: [[0, 0], [2, 0], [0, 1], [1, 1], [2, 1]]},
  {id: 6, points: [[0, 2], [0, 0], [1, 2], [1, 1], [1, 0]]},
  {id: 6, points: [[2, 1], [0, 1], [2, 0], [1, 0], [0, 0]]},
  {id: 6, points: [[1, 0], [1, 2], [0, 0], [0, 1], [0, 2]]},
  {id: 7, points: [[0, 0], [0, 1], [-2, 2], [-1, 2], [0, 2]]},
  {id: 7, points: [[0, 0], [1, 0], [2, 2], [2, 1], [2, 0]]},
  {id: 7, points: [[0, 2], [0, 1], [2, 0], [1, 0], [0, 0]]},
  {id: 7, points: [[2, 2], [1, 2], [0, 0], [0, 1], [0, 2]]},
  {id: 8, points: [[0, 0], [-1, 1], [0, 1], [-2, 2], [-1, 2]]},
  {id: 8, points: [[0, 0], [1, 1], [1, 0], [2, 2], [2, 1]]},
  {id: 8, points: [[-1, 2], [0, 1], [-1, 1], [1, 0], [0, 0]]},
  {id: 8, points: [[2, 2], [1, 1], [1, 2], [0, 0], [0, 1]]},
  {id: 9, points: [[0, 0], [-1, 1], [0, 1], [1, 1], [0, 2]]},
  {id: 10, points: [[0, 0], [-1, 1], [0, 1], [0, 2], [0, 3]]},
  {id: 10, points: [[0, 0], [1, 1], [1, 0], [2, 0], [3, 0]]},
  {id: 10, points: [[0, 3], [1, 2], [0, 2], [0, 1], [0, 0]]},
  {id: 10, points: [[1, 1], [0, 0], [0, 1], [-1, 1], [-2, 1]]},
  {id: 10, points: [[0, 0], [1, 1], [0, 1], [0, 2], [0, 3]]},
  {id: 10, points: [[-1, 1], [0, 0], [0, 1], [1, 1], [2, 1]]},
  {id: 10, points: [[0, 3], [-1, 2], [0, 2], [0, 1], [0, 0]]},
  {id: 10, points: [[3, 0], [2, 1], [2, 0], [1, 0], [0, 0]]},
  {id: 11, points: [[0, 0], [1, 0], [1, 1], [1, 2], [2, 2]]},
  {id: 11, points: [[-2, 2], [-2, 1], [-1, 1], [0, 1], [0, 0]]},
  {id: 11, points: [[1, 0], [0, 0], [0, 1], [0, 2], [-1, 2]]},
  {id: 11, points: [[0, 0], [0, 1], [1, 1], [2, 1], [2, 2]]},
];

const board = [];

function makeBoard() {
  for (let i = 0; i < WIDTH * HEIGHT; i++) {
    board.push(-1);
  }
}

function canPlace(points, x, y) {
  for (const [px, py] of points) {
    const boardX = px + x;
    const boardY = py + y;
    if (boardX < 0 || boardX >= WIDTH || boardY >= HEIGHT || board[boardY*WIDTH + boardX] != -1) {
      return false;
    }
  }
  return true;
}

function placePiece(id, points, x, y) {
  for (const [px, py] of points) {
    const boardX = px + x;
    const boardY = py + y;
    board[boardY * WIDTH + boardX] = id;
  }
}

function removePiece(points, x, y) {
  for (const [px, py] of points) {
    const boardX = px + x;
    const boardY = py + y;
    board[boardY * WIDTH + boardX] = -1;
  }
}

function solve(pieces) {
  if (pieces == 0) {
    return true;
  }
  const firstEmptySquare = board.indexOf(-1);
  const x = firstEmptySquare % WIDTH;
  const y = (firstEmptySquare / WIDTH) | 0;
  for (const variant of variants) {
    if ((1 << variant.id) & pieces) {
      // piece is unused
      if (canPlace(variant.points, x, y)) {
        placePiece(variant.id, variant.points, x, y);
        if (solve(pieces - (1 << variant.id))) {
          return true;
        }
        removePiece(variant.points, x, y);
      }
    }
  }
  return false;
}

function* solve2(pieces) {
  if (pieces == 0) {
    yield true;
  }
  const firstEmptySquare = board.indexOf(-1);
  const x = firstEmptySquare % WIDTH;
  const y = (firstEmptySquare / WIDTH) | 0;
  for (const variant of variants) {
    if ((1 << variant.id) & pieces) {
      // piece is unused
      if (canPlace(variant.points, x, y)) {
        placePiece(variant.id, variant.points, x, y);
        yield* solve2(pieces - (1 << variant.id));
        removePiece(variant.points, x, y);
      }
    }
  }
  yield false;
}

makeBoard();

class Pentominoes {
  constructor() {
    this.palette = [
      '#e6194B',
      '#f58231',
      '#ffe119',
      '#808000',
      '#bfef45',
      '#3cb44b',
      '#42d4f4',
      '#4363d8',
      '#000075',
      '#dcbeff',
      '#911eb4',
      '#f032e6',
    ];
  }

  setup() {
    this.ctx = document.getElementById('board').getContext('2d');
    this.gen = solve2(4095);
  }

  draw() {
    const ctx = this.ctx;
    const cellWidth = 25;
    const cellHeight = 25;

    let finished = false
    //for (let i=0; i < 1000; i++) {
    for (let i=0; i < 10; i++) {
      if (this.gen.next().value) {
        finished = true;
        break;
      }
    }
    for (let x=0; x < WIDTH; x++) {
      for (let y=0; y < HEIGHT; y++) {
        this.ctx.fillStyle = this.palette[board[y * WIDTH + x]] || '#bbb';
        this.ctx.fillRect(x * cellWidth, y * cellHeight, cellWidth, cellHeight);
      }
    }
    if (!finished) {
      requestAnimationFrame(() => this.draw());
    }
    //if (!this.gen.next().value) {
    //  requestAnimationFrame(() => this.draw());
    //}
  }
}

let p = new Pentominoes();
p.setup();
p.draw();
