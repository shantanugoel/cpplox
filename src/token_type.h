#ifndef __TOKEN_TYPE_H__
#define __TOKEN_TYPE_H__

namespace lox {
namespace token_type_internal {
#define TOKEN_TYPE_STRING(type) #type
#define TOKEN_TYPES \
  X(LeftParen)      \
  X(RightParen)     \
  X(LeftBrace)      \
  X(RightBrace)     \
  X(Comma)          \
  X(Dot)            \
  X(Minus)          \
  X(Plus)           \
  X(Semicolon)      \
  X(Slash)          \
  X(Star)           \
  X(Bang)           \
  X(BangEqual)      \
  X(Equal)          \
  X(EqualEqual)     \
  X(Greater)        \
  X(GreaterEqual)   \
  X(Less)           \
  X(LessEqual)      \
  X(Identifier)     \
  X(String)         \
  X(Number)         \
  X(And)            \
  X(Class)          \
  X(Else)           \
  X(False)          \
  X(Fun)            \
  X(For)            \
  X(If)             \
  X(Nil)            \
  X(Or)             \
  X(Print)          \
  X(Return)         \
  X(Super)          \
  X(This)           \
  X(True)           \
  X(Var)            \
  X(While)          \
  X(Eof)
};  // namespace token_type_internal

enum class TokenType {
#define X(enumval) enumval,
  TOKEN_TYPES
#undef X
};

static std::string TokenTypeName[] = {
#define X(enumval) TOKEN_TYPE_STRING(enumval),
    TOKEN_TYPES
#undef X
};

}  // namespace lox

#endif  // __TOKEN_TYPE_H__