#include <Arduboy.h>

#define FRAMERATE 60

Arduboy arduboy;

void setup() {
  arduboy.beginNoLogo();
  arduboy.audio.begin();
  arduboy.setFrameRate(FRAMERATE);
}

const int sizeOfSnake = 5;
int snake[sizeOfSnake][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};

enum Directions {
  NORTH = 1,
  EAST = 2,
  SOUTH = 4,
  WEST = 8
};

Directions direction = EAST;

void drawCell(int x, int y) {
  arduboy.fillRect(x * 2, y * 2, 2, 2, 1);
}

void drawSnake() {
  for (int i = 0; i < sizeOfSnake - 1; i++) {
    drawCell(snake[i][0], snake[i][1]);
  };
}

void moveSnake() {
  int newCell[2];

  if (direction == NORTH){
    newCell[0] = snake[sizeOfSnake - 1][0];
    newCell[1] = snake[sizeOfSnake - 1][1] - 1;
  } else if (direction == EAST) {
     newCell[0] = snake[sizeOfSnake - 1][0] + 1;
     newCell[1] = snake[sizeOfSnake - 1][1];
  } else if (direction == SOUTH){
    newCell[0] = snake[sizeOfSnake - 1][0];
    newCell[1] = snake[sizeOfSnake - 1][1] + 1;
  } else if (direction == WEST){
    newCell[0] = snake[sizeOfSnake - 1][0] - 1;
    newCell[1] = snake[sizeOfSnake - 1][1];
  }

  for (int i = 0; i < sizeOfSnake; ++i) {
    memcpy(snake[i], snake[i + 1], sizeof(snake[i]));
  };

  memcpy(snake[sizeOfSnake - 1], newCell, sizeof(newCell));
}

void handleInput() {
  if (arduboy.pressed(UP_BUTTON) && (direction & (EAST | WEST)) == direction) {
    direction = NORTH;
  } else if (arduboy.pressed(RIGHT_BUTTON) && (direction & (NORTH | SOUTH)) == direction) {
    direction = EAST;
  } else if (arduboy.pressed(DOWN_BUTTON) && (direction & (EAST | WEST)) == direction) {
    direction = SOUTH;
  } else if (arduboy.pressed(LEFT_BUTTON) && (direction & (NORTH | SOUTH)) == direction) {
    direction = WEST;
  }
}

void loop() {
  if (!(arduboy.nextFrame())) return;

  arduboy.clear();

  drawSnake();

  if (arduboy.everyXFrames(15)) {
    moveSnake();
  }

  handleInput();

  arduboy.display();
}
