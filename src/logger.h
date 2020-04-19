#ifndef __LOGGER_H_
#define __LOGGER_H_
#include <iostream>

namespace lox {

class Logger {
 public:
  static void Error(int line, const std::string& message) {
    Report(line, "", message);
  }
  static bool had_error_;

 private:
  static void Report(int line, const std::string& where,
                     const std::string& message) {
    std::cerr << "[Line " << line << "] Error " << where << ": " << message
              << "\n";
    had_error_ = true;
  }
};  // namespace lox

}  // namespace lox

#endif  // __LOGGER_H_