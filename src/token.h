#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>

#include "token_type.h"

namespace lox {

class Token {
 public:
  // TODO: Add literal object as well.
  Token(const TokenType type, const std::string& lexeme, const int line)
      : type_(type), lexeme_(lexeme), line_(line) {}

  std::string ToString() {
    // TODO: convert type and literal as well as part of this.
    return lexeme_;
  }

 private:
  const TokenType type_;
  const std::string lexeme_;
  const int line_;
};

}  // namespace lox

#endif  // __TOKEN_H__
