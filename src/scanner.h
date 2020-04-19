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

  // Variables to track state of scanning.
  int start_ = 0;
  int current_ = 0;
  int line_ = 1;

  void ScanToken();
  void AddToken(TokenType type) { AddToken(type, nullptr); }
  void AddToken(TokenType type, Object literal);
  void String();
  void Number();
  bool match(char expected) {
    if (IsAtEnd()) return false;
    if (source_[current_] != expected) return false;
    current_++;
    return true;
  }
  char Peek() {
    if (IsAtEnd()) return '\0';
    return source_[current_];
  }
  char PeekNext() {
    if (current_ + 1 >= source_.length()) return '\0';
    return source_[current_ + 1];
  }
  bool IsDigit(char c) { return c >= '0' && c <= '9'; }

  char Advance() {
    current_++;
    return source_[current_ - 1];
  }

  bool IsAtEnd() { return current_ >= source_.length; }
};

}  // namespace lox

#endif  // __SCANNER_H__
