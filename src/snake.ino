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

// 0 = right
// 1 = down
// 2 = left
// 3 = up
int direction = 0;

void loop() {
  if (!(arduboy.nextFrame())) return;

  arduboy.clear();

  for (int i = 0; i < sizeOfSnake - 1; i++) {
    arduboy.fillRect(snake[i][0] * 2, snake[i][1] * 2, 2, 2, 1);
  };

  if (arduboy.everyXFrames(15)) {
    int newCell[2];

    if (direction == 0) {
      newCell[0] = snake[sizeOfSnake - 1][0] + 1;
      newCell[1] = snake[sizeOfSnake - 1][1];
    } else if (direction == 1){
      newCell[0] = snake[sizeOfSnake - 1][0];
      newCell[1] = snake[sizeOfSnake - 1][1] + 1;
    } else if (direction == 3){
      newCell[0] = snake[sizeOfSnake - 1][0];
      newCell[1] = snake[sizeOfSnake - 1][1] - 1;
    } else if (direction == 2){
      newCell[0] = snake[sizeOfSnake - 1][0] - 1;
      newCell[1] = snake[sizeOfSnake - 1][1];
    }

    for (int i = 0; i < sizeOfSnake; ++i) {
      memcpy(snake[i], snake[i + 1], sizeof(snake[i]));
    };

    memcpy(snake[sizeOfSnake - 1], newCell, sizeof(newCell));
  }

  if (arduboy.pressed(DOWN_BUTTON)) {
    direction = 1;
  } else if (arduboy.pressed(UP_BUTTON)) {
    direction = 3;
  } else if (arduboy.pressed(LEFT_BUTTON)) {
    direction = 2;
  } else if (arduboy.pressed(RIGHT_BUTTON)) {
    direction = 0;
  }

  arduboy.display();
}
