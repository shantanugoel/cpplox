#ifndef __LOX_H__
#define __LOX_H__

#include <iostream>
#include <string>

namespace lox {

class Lox {
 public:
  void RunPrompt(void);
  void RunFile(const std::string& path);
  void Error(int line, const std::string& message) {
    Report(line, "", message);
  }

  bool had_error_ = false;

 private:
  void Run(const std::string& source);
  void Report(int line, const std::string& where, const std::string& message) {
    std::cerr << "[Line " << line << "] Error " << where << ": " << message;
    had_error_ = true;
  }
};

}  // namespace lox

#endif  // __LOX_H__