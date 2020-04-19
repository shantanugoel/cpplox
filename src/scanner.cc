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

    default:
      // Log error but keep scanning to get as many errors as possible in one
      // go.
      Lox::Error(line_, "Unexpected character.");
      break;
  }
}

}  // namespace lox