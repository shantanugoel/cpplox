#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <sstream>
#include <string>
#include <variant>

#include "token_type.h"

namespace lox {

// TODO: Update the possible variants here as we go.
using Object = std::variant<std::string, double, bool>;

class Token {
 public:
  // TODO: Add literal object as well.
  Token(const TokenType type, const std::string& lexeme, const Object& literal,
        const int line)
      : type_(type), lexeme_(lexeme), literal_(literal), line_(line) {}

  std::string ToString() {
    // TODO: convert type and literal as well as part of this.
    return lexeme_ + " " + std::visit(Visitor{}, literal_);
  }

 private:
  const TokenType type_;
  const std::string lexeme_;
  const Object literal_;
  const int line_;

  template <typename T>
  static std::string VisitorHelper(T x) {
    std::stringstream temp;
    temp << x;
    return temp.str();
  }

  struct Visitor {
    std::string operator()(double x) const { return VisitorHelper(x); }
    std::string operator()(bool x) const { return VisitorHelper(x); }
    std::string operator()(std::string x) const { return VisitorHelper(x); }
  };
};

}  // namespace lox

#endif  // __TOKEN_H__
