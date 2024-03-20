#include <emscripten/emscripten.h>
#include <stdio.h>

int main() {
  printf("Hello World\n");
  return 0;
}

int internal_sum(int a, int b) { return a + b; }

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

typedef struct {
  int x;
  int y;
} Point;

EXTERN EMSCRIPTEN_KEEPALIVE void myFunction(int argc, char **argv) {
  printf("like bro Called %d\n", internal_sum(50, 234));
}

EXTERN EMSCRIPTEN_KEEPALIVE int process_file(const char *data, int size) {
  // Example processing: count the number of bytes
  int count = 0;
  for (int i = 0; i < size; i++) {
    count++;
  }
  return count * 2; // For this example, it just returns the size
}

// Create a new Point and return a pointer to it
EXTERN EMSCRIPTEN_KEEPALIVE Point *create_point(int x, int y) {
  Point *p = (Point *)malloc(sizeof(Point));
  if (p != NULL) {
    p->x = x;
    p->y = y;
  }
  return p;
}

// Function to manipulate or use the Point
EXTERN EMSCRIPTEN_KEEPALIVE int get_point_x(Point *p) {
  if (p != NULL) {
    return p->x;
  }
  return -1; // Error code
}

// Clean up
EXTERN EMSCRIPTEN_KEEPALIVE void delete_point(Point *p) { free(p); }
