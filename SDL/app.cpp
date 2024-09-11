#include "sim.h"

#define ALIVE 0xFF00FF00
#define DEAD 0xFF000000

void init_game(int (*world)[SIM_X_SIZE], int (*new_world)[SIM_X_SIZE]) {
  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      world[y][x] = simRand() % 2;
    }
  }
}

void draw(int (*world)[SIM_X_SIZE], int (*new_world)[SIM_X_SIZE]) {
  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      int color = world[y][x] ? ALIVE : DEAD;
      simPutPixel(x, y, color);
    }
  }

  simFlush();
}

int get_state(int x, int y, int (*world)[SIM_X_SIZE],
              int (*new_world)[SIM_X_SIZE]) {
  if (x >= 0 && y >= 0 && x < SIM_X_SIZE && y < SIM_Y_SIZE) {
    return world[y][x];
  }

  return 0;
}

int get_count_neib(int x, int y, int (*world)[SIM_X_SIZE],
                   int (*new_world)[SIM_X_SIZE]) {
  return get_state(x, y - 1, world, new_world) +
         get_state(x - 1, y, world, new_world) +
         get_state(x, y + 1, world, new_world) +
         get_state(x + 1, y, world, new_world);
}

void update(int (*world)[SIM_X_SIZE], int (*new_world)[SIM_X_SIZE]) {
  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      int count = get_count_neib(x, y, world, new_world);
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
  int world[SIM_Y_SIZE][SIM_X_SIZE];
  int new_world[SIM_Y_SIZE][SIM_X_SIZE];
  for (int y = 0; y < SIM_Y_SIZE; ++y) {
    for (int x = 0; x < SIM_X_SIZE; ++x) {
      world[y][x] = 0;
      new_world[y][x] = 0;
    }
  }
  init_game(world, new_world);
  while (true) {
    draw(world, new_world);
    update(world, new_world);
  }
}
