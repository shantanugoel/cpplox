#include <string>

#include "expr.h"

namespace lox {
class AstPrinter : ExprVisitor<std::string> {
 public:
  std::string visit(Binary expr) override {
    (void)expr;
    return "a";
  }
  std::string visit(Grouping expr) override {
    (void)expr;
    return "a";
  }
  std::string visit(Literal expr) override {
    (void)expr;
    return "a";
  }
  std::string visit(Unary expr) override {
    (void)expr;
    return "a";
  }
};
}  // namespace lox

int main() {
  lox::AstPrinter ast_printer;
  (void)ast_printer;
  return 0;
}