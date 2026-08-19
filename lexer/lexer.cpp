#include "lexer.hpp"
#include "token.hpp"

#include <cctype>
#include <cstddef>
#include <stdexcept>
#include <vector>

bool Lexer::isEnd() {
    return current >= source.size();
}

char Lexer::peek() {
    if (isEnd()) return '\0';

    return source[current];
}

char Lexer::peekNext() {
    if (current + 1 >= source.size()) return '\0';

    return source[current + 1];
}

char Lexer::advance() {
    char c = peek();
    current++;
    return c;
}

void Lexer::skipWhitespace() {
    while (peek() == ' ' || peek() == '\n' || peek() == '\t' || peek() == '\r') {
        advance();
    }
}

void Lexer::stringm() {
    advance();

    size_t start = current;

    while (peek() != '"' && !isEnd()) advance();

    if (isEnd()) {
        throw std::runtime_error("\033[31m[Lexer err]: Unterminated string\033[0m");
    }

    std::string textS = source.substr(start, current - start);

    advance();

    tokens.push_back(Token(TokenKind::StringL, textS));
}

void Lexer::identifier() {
    size_t start = current;

    while (!isEnd() && (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_')) advance();

    std::string textId = source.substr(start, current - start);

    if (textId == "write") tokens.push_back(Token(TokenKind::Write, textId));
    else if (textId == "exec") tokens.push_back(Token(TokenKind::Exec, textId));
    else if (textId == "true") tokens.push_back(Token(TokenKind::True, textId));
    else if (textId == "false") tokens.push_back(Token(TokenKind::False, textId));
    else if (textId == "module") tokens.push_back(Token(TokenKind::Module, textId));
    else if (textId == "import") tokens.push_back(Token(TokenKind::Import, textId));
    else if (textId == "func") tokens.push_back(Token(TokenKind::Func, textId));
    else tokens.push_back(Token(TokenKind::Identifier, textId));
}

void Lexer::skipComment() {
    while (peek() != '\n' && !isEnd()) advance();
}

void Lexer::scan_token() {
    char c = peek();

    if (std::isalpha(c) || c == '_') identifier();
    else if (c == '"') stringm();
    else if (c == '/') {
        if (peekNext() == '/') {
            advance(); // /
            advance(); // /
            skipComment();
        }
        else {
            throw std::runtime_error("\033[31m[Lexer err]: Comment with two '/' -> \"//\"\033[0m");
        }
    }
    else if (c == '(') {
        advance();
        tokens.push_back(Token(TokenKind::LParen, "("));
    }
    else if (c == ')') {
        advance();
        tokens.push_back(Token(TokenKind::RParen, ")"));
    }
    else if (c == '{') {
        advance();
        tokens.push_back(Token(TokenKind::LBrace, "{"));
    }
    else if (c == '}') {
        advance();
        tokens.push_back(Token(TokenKind::RBrace, "}"));
    }
    else if (c == ';') {
        advance();
        tokens.push_back(Token(TokenKind::Semicolon, ";"));
    }
    else if (c == ',') {
        advance();
        tokens.push_back(Token(TokenKind::Comma, ","));
    }
    else if (c == '.') {
        advance();
        tokens.push_back(Token(TokenKind::Dot, "."));
    }
    else {
        throw std::runtime_error("\033[31m[Lexer err]: Unknown symbol or token\033[0m");
    }
}

std::vector<Token> Lexer::tokenize() {
    while (!isEnd()) {
        skipWhitespace();

        if (isEnd()) break;

        scan_token();
    }

    tokens.push_back(Token(TokenKind::Eof, ""));

    return tokens;
}
