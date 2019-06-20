#include <stdio.h>
#include <emscripten.h>

int main () {
  printf("Initial Circles\n");
  emscripten_run_script("render()");
}

// Return circles to JS
int getCircles() {
  return 1;
}
