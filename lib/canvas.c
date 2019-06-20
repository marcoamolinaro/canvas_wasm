#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

// Number of Circles
#define NUM_CIRCLES 500

// Circle struct
struct Circle {
  int x; // x coordinate
  int y; // y coordinate
  int r; // circle radio
  int cr; // color RED
  int cg; // color GREEN
  int cb; // color BLUE
};

// Circle Animation data struct
struct CircleAnimationData {
  int x; // x coordinate
  int y; // y coordinate
  int r; // circle radio
  int xv; // x - axis velocity
  int yv; // y - axis velocity
  int xd; // x - axis direction (1 = forward, 0 = backward)
  int yd; // y - axis direction (1 = forward, 0 = backward)
};

// Circles variable
struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

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

    // Fill animation data struct
    animationData[i].x = x;
    animationData[i].y = y;
    animationData[i].r = radius;
    animationData[i].xv = getRand(10);
    animationData[i].yv = getRand(10);
    animationData[i].xd = 1;
    animationData[i].yd = 1;

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
struct Circle * getCircles(int canvasWidth, int canvasHeight) {

  // Upadate circle data
  for (int i = 0; i < NUM_CIRCLES; i++) {

    // Colision RIGHT - set x direction backward 0
    if ((animationData[i].x + animationData[i].r) >= canvasWidth) {
      animationData[i].xd = 0;
    }

    // Colision LEFT - set x direction forward 1
    if ((animationData[i].x - animationData[i].r) <= 0) {
      animationData[i].xd = 1;
    }

    // Colision TOP - set y direction forward 1
    if ((animationData[i].y - animationData[i].r) <= 0) {
      animationData[i].yd = 1;
    }
    // Colision BOTTOM - set y direction backward 0
    if ((animationData[i].y + animationData[i].r) >= canvasHeight) {
      animationData[i].yd = 0;
    }

    // Move circle in specified direction
    if (animationData[i].xd == 1) {
      animationData[i].x += animationData[i].xv;
    } else {
      animationData[i].x -= animationData[i].xv;
    }

    if (animationData[i].yd == 1) {
      animationData[i].y += animationData[i].yv;
    } else {
      animationData[i].y -= animationData[i].yv;
    }

    // Upadate matching circles
    circles[i].x = animationData[i].x;
    circles[i].y = animationData[i].y;
  }

  return circles;
}
