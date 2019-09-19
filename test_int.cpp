#include "iostream"

int main() {
  int mat = 0x11245;

  std::cout << mat << std::endl;

  int shifeted = (mat >> 4) + 1;
  std::cout << shifeted << std::endl;

  int shifeted_2 = (shifeted >> 4) + 1;
  std::cout << shifeted_2 << std::endl;
}
