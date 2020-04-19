#include <iostream>

#include "lox.h"

// Initialize error state.
bool lox::Lox::had_error_ = false;

int main(int argc, char** argv) {
  lox::Lox interpreter;

  if (argc > 2) {
    std::cout << "Usage: " << argv[0] << " [script]";
  } else if (argc == 2) {
    interpreter.RunFile(argv[1]);
  } else {
    interpreter.RunPrompt();
  }
}