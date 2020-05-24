#include <sstream>
#include <string>

#include "expr.h"

namespace lox {
class AstPrinter : ExprVisitor<std::string> {
 public:
  std::string Print(Expr expr) { return expr.accept(*this); }

  std::string visit(const Binary& expr) override {
    std::stringstream ss;
    ss << "(" << expr.op.ToString();
    Parenthesize(ss, expr.left, expr.right);
    ss << ")";
    return ss.str();
  }
  std::string visit(const Grouping& expr) override {
    std::stringstream ss;
    ss << "(group ";
    Parenthesize(ss, expr.expression);
    ss << ")";
    return ss.str();
  }
  std::string visit(const Literal& expr) override {
    (void)expr;
    // if (expr.value == 0) return "nil";
    return "a";
    // std::stringstream ss;
    // ss << "(" << expr.op.ToString();
    // ss << ")";
    // return ss.str();
  }
  std::string visit(const Unary& expr) override {
    std::stringstream ss;
    ss << "(" << expr.op.ToString();
    Parenthesize(ss, expr.right);
    ss << ")";
    return ss.str();
  }

 private:
  template <typename T>
  void Parenthesize(std::stringstream& ss, T t) {
    ss << " " << t.accept(*this);
  }

  template <typename T, typename... Args>
  void Parenthesize(std::stringstream& ss, T value, Args... args) {
    Parenthesize(ss, value);
    Parenthesize(ss, args...);
  }
};
}  // namespace lox

int main() {
  lox::AstPrinter ast_printer;
  (void)ast_printer;
  return 0;
}