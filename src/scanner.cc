#include "scanner.h"

#include <map>

#include "logger.h"

namespace lox {

namespace {
static const std::map<const std::string, TokenType> keywords = {
    {"and", TokenType::And},       {"class", TokenType::Class},
    {"else", TokenType::Else},     {"false", TokenType::False},
    {"for", TokenType::For},       {"fun", TokenType::Fun},
    {"if", TokenType::If},         {"nil", TokenType::Nil},
    {"or", TokenType::Or},         {"print", TokenType::Print},
    {"return", TokenType::Return}, {"super", TokenType::Super},
    {"this", TokenType::This},     {"true", TokenType::True},
    {"var", TokenType::Var},       {"while", TokenType::While},
};
}  // namespace

std::vector<Token> Scanner::ScanTokens() {
  while (!IsAtEnd()) {
    start_ = current_;
    ScanToken();
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
  if (IsAtEnd()) {
    Logger::Error(line_, "Unterminated String.");
    return;
  }

  // Trim surrounding quotes
  std::string value = source_.substr(start_ + 1, current_ - start_ - 1);
  // The closing ".
  Advance();

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
  AddToken(TokenType::Number,
           std::stod(source_.substr(start_, current_ - start_)));
}

void Scanner::Identifier() {
  while (IsAlphaNumeric(Peek())) Advance();

  // See if the identifier isa  reserved word.
  TokenType type = TokenType::Identifier;
  auto result = keywords.find(source_.substr(start_, current_ - start_));
  if (result != keywords.end()) {
    type = result->second;
  }
  AddToken(type);
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
      } else if (IsAlpha(c)) {
        Identifier();
      } else {
        // Log error but keep scanning to get as many errors as possible in one
        // go.
        std::cout << source_[current_] << "\n";
        Logger::Error(line_, "Unexpected character.");
      }
      break;
  }
}  // namespace lox

}  // namespace lox