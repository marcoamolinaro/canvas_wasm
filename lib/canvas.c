#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

// Number of Circles
#define NUM_CIRCLES 20

// Circle struct
struct Circle {
  int x; // x coordinate
  int y; // y coordinate
  int r; // circle radio
  int cr; // color RED
  int cg; // color GREEN
  int cb; // color BLUE
};

// Circles variable
struct Circle circles[NUM_CIRCLES];

// Random Number generator
int getRand(max) {
  return (rand() % max);
}

int main () {

  // Seed random number generator
  srand(time(NULL));

  // create circles
  for (int i = 0; i < NUM_CIRCLES; i++) {
    // Radius
    int radius = getRand(50);

    // Coordinates
    int x = getRand(1000) + radius;
    int y = getRand(1000) + radius;

    // Fill circles struct
    circles[i].x = x;
    circles[i].y = y;
    circles[i].r = radius;
    circles[i].cr = getRand(255);
    circles[i].cg = getRand(255);
    circles[i].cb = getRand(255);
  }

  // Start JS rendering
  EM_ASM({ render($0, $1); }, NUM_CIRCLES*6, 6 );
}

// Return circles to JS
struct Circle * getCircles() {
  return circles;
}
