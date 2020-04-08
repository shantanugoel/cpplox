#include "lox.h"

#include <fstream>
#include <iostream>
#include <string>

namespace lox {

void Lox::Run(const std::string& source) { (void)source; }

void Lox::RunFile(const std::string& path) {
  std::string source;
  std::ifstream script(path);
  if (script.is_open()) {
    script.seekg(0, std::ios::end);
    source.reserve(script.tellg());
    script.seekg(0, std::ios::beg);
    source.assign(std::istreambuf_iterator<char>(script),
                  std::istreambuf_iterator<char>());
  } else {
    std::cerr << "Error while opening script file: " << std::strerror(errno);
    return;
  }
  Run(source);
}

void Lox::RunPrompt() {
  std::string line;
  while (1) {
    std::cout << "> ";
    std::getline(std::cin, line);
    Run(line);
  }
}

}  // namespace lox