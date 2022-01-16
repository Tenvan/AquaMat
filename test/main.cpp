#include <iostream>
#include <cstdarg>
#include <string>

void myPrintf(const char* text, ...) {
  char buffer[256];
  va_list(args);
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);
  printf(buffer);
}

int main() {
  std::cout << "Hello, World!\n" << std::endl;
  printf("Hello, World 2\n!");
  myPrintf("Hello, World %d %d!\n", 3, 4);
  myPrintf("%s!\n", "Hello, World 5");
  return 0;
}

