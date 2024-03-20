#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>

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

EXTERN EMSCRIPTEN_KEEPALIVE int process_file(char *filename) {
  printf("trying to open %s\n", filename);
  FILE *in_file = fopen(filename, "r"); // read only
  if (in_file == NULL) {
    printf("Error! Could not open file\n");
  }
  fseek(in_file, 0L, SEEK_END);
  int sz = ftell(in_file);
  fseek(in_file, 0L, SEEK_SET);
  char *buffer = malloc(sizeof(char) * sz);

  fread(buffer, sizeof(char), sz, in_file);

  // Example processing: count the number of bytes
  /*
  int count = 0;
  for (int i = 0; i < sz; i++) {
    count++;
    printf("%c", buffer[i]);
  }
  */

  printf("\n");
  return sz; // For this example, it just returns the size
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
