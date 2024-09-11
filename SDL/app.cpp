#include "sim.h"
#include <SDL2/SDL.h>

#define ALIVE 0xFF00FF00
#define DEAD 0xFF000000

static int world[SIM_Y_SIZE][SIM_X_SIZE];
static int new_world[SIM_Y_SIZE][SIM_X_SIZE];

void init_game() {
  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      world[y][x] = simRand() % 2;
    }
  }
}

void draw() {
  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      int color = world[y][x] ? ALIVE : DEAD;
      simPutPixel(x, y, color);
    }
  }

  simFlush();
}

int get_state(int x, int y) {
  if (x > 0 && y > 0 && x < SIM_X_SIZE && y < SIM_Y_SIZE) {
    return world[x][y];
  }

  return 0;
}

int get_count_neib(int x, int y) {
  return get_state(x, y - 1) + get_state(x - 1, y) + get_state(x, y + 1) +
         get_state(x + 1, y);
}

void update() {
  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      int count = get_count_neib(x, y);
      if (world[y][x] == 1) {
        if (count == 2 || count == 3) {
          new_world[y][x] = 1;
        } else {
          new_world[y][x] = 0;
        }
      } else {
        if (count == 3) {
          new_world[y][x] = 1;
        } else {
          new_world[y][x] = 0;
        }
      }
    }
  }

  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      world[y][x] = new_world[y][x];
    }
  }
}

void app() {
  init_game();
  while (true) {
    draw();
    update();
    SDL_Delay(100);
  }
}
