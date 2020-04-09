#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <string>
#include <vector>

#include "token.h"
#include "token_type.h"

namespace lox {

class Scanner {
 public:
  Scanner() = delete;
  Scanner(std::string source) : source_(source) {}
  std::vector<Token> ScanTokens() {}

 private:
  std::string source_;
  std::vector<Token> tokens_;

  void scanToken();
};

}  // namespace lox

#endif  // __SCANNER_H__
