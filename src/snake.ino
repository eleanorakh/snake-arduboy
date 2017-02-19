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

void loop() {
  if (!(arduboy.nextFrame())) return;

  arduboy.clear();

  for (int i = 0; i < sizeOfSnake - 1; i++) {
    arduboy.fillRect(snake[i][0] * 2, snake[i][1] * 2, 2, 2, 1);
  };

  if (arduboy.everyXFrames(15)) {
    int newCell[2] = {snake[sizeOfSnake - 1][0] + 1, snake[sizeOfSnake - 1][1]};

    for (int i = 0; i < sizeOfSnake; ++i) {
      memcpy(snake[i], snake[i + 1], sizeof(snake[i]));
    };

    memcpy(snake[sizeOfSnake - 1], newCell, sizeof(newCell));
  }

  arduboy.display();
}
