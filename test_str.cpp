#include <iostream>
#include <string>

void crete_string(std::string &oie) { oie = "azul"; }

std::string opa() {
  std::string oie;

  crete_string(oie);

  return oie;
}

int main() { std::cout << opa() << std::endl; }
