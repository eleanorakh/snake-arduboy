#include <Arduboy.h>

#define FRAMERATE 60

Arduboy arduboy;

void setup() {
  arduboy.beginNoLogo();
  arduboy.audio.begin();
  arduboy.setFrameRate(FRAMERATE);
}

void loop() {
  if (!(arduboy.nextFrame())) return;

  arduboy.clear();

  int snake[][2] = {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {3, 1}, {4, 1}};
  for (int i = 0; i < sizeof(snake); i++) {
    arduboy.fillRect(snake[i][0] * 2, snake[i][1] * 2, 2, 2, 1);
  };

  arduboy.display();
}
