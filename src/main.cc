#include <iostream>

#include "lox.h"

int main(int argc, char** argv) {
  lox::Lox interpreter;
  // Initialize error state.
  interpreter.SetError(false);

  if (argc > 2) {
    std::cout << "Usage: " << argv[0] << " [script]";
  } else if (argc == 2) {
    interpreter.RunFile(argv[1]);
  } else {
    interpreter.RunPrompt();
  }
}