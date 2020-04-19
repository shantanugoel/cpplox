#ifndef __LOX_H__
#define __LOX_H__

#include <iostream>
#include <string>

#include "logger.h"

namespace lox {

class Lox {
 public:
  Lox() = default;
  ~Lox() = default;
  void RunPrompt(void);
  void RunFile(const std::string& path);
  void SetError(bool status) { Logger::had_error_ = status; }
  bool GetError() { return Logger::had_error_; }

 private:
  void Run(const std::string& source);
};

}  // namespace lox

#endif  // __LOX_H__