#include "scanner.h"

#include "lox.h"

namespace lox {

std::vector<Token> Scanner::ScanTokens() {
  while (~IsAtEnd()) {
    start_ = current_;
    ScanTokens();
  }
  tokens_.emplace_back(Token(TokenType::Eof, "", nullptr, line_));
  return tokens_;
}

void Scanner::AddToken(TokenType type, Object literal) {
  std::string text = source_.substr(start_, current_ - start_);
  tokens_.emplace_back(Token(type, text, literal, line_));
}

void Scanner::String() {
  while (Peek() != '"' && !IsAtEnd()) {
    if (Peek() == '\n') line_++;
    Advance();
  }

  /// Unterminated String
  if (!IsAtEnd()) {
    Lox::Error(line_, "Unterminated String.");
    return;
  }

  // The closing ".
  Advance();

  // Trim surrounding quotes
  std::string value = source_.substr(start_ + 1, current_ - 1);
  AddToken(TokenType::String, value);
}

void Scanner::Number() {
  while (IsDigit(Peek())) Advance();

  // Look for fractional part.
  if (Peek() == '.' && IsDigit(PeekNext())) {
    // Consume the dot
    Advance();
    while (IsDigit(Peek())) Advance();
  }
  AddToken(TokenType::Number, std::stod(source_.substr(start_, current_)));
}

void Scanner::ScanToken() {
  char c = Advance();
  switch (c) {
    // Single character lexemes
    case '(':
      AddToken(TokenType::LeftParen);
      break;
    case ')':
      AddToken(TokenType::RightParen);
      break;
    case '{':
      AddToken(TokenType::LeftBrace);
      break;
    case '}':
      AddToken(TokenType::RightBrace);
      break;
    case ',':
      AddToken(TokenType::Comma);
      break;
    case '.':
      AddToken(TokenType::Dot);
      break;
    case '-':
      AddToken(TokenType::Minus);
      break;
    case '+':
      AddToken(TokenType::Plus);
      break;
    case ';':
      AddToken(TokenType::Semicolon);
      break;
    case '*':
      AddToken(TokenType::Star);
      break;

    // Single / Double character lexemes
    case '!':
      AddToken(match('=') ? TokenType::BangEqual : TokenType::Bang);
      break;
    case '=':
      AddToken(match('=') ? TokenType::EqualEqual : TokenType::Equal);
      break;
    case '<':
      AddToken(match('=') ? TokenType::LessEqual : TokenType::Less);
      break;
    case '>':
      AddToken(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
      break;

    // Longer lexemes
    case '/':
      if (match('/')) {
        // Found a comment, so go till end of line. No need to call AddToken
        // since comments don't need to be parsed/executed.
        while (Peek() != '\n' && ~IsAtEnd()) Advance();
      } else {
        AddToken(TokenType::Slash);
      }
      break;

    // Skippable characters/whitespace
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line_++;
      break;

    // Literals
    case '"':
      String();
      break;

    default:
      // Number literals
      if (IsDigit(c)) {
        Number();
      } else {
        // Log error but keep scanning to get as many errors as possible in one
        // go.
        Lox::Error(line_, "Unexpected character.");
      }
      break;
  }
}

}  // namespace lox