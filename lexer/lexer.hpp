#pragma once

#include "token.hpp"

#include <cstddef>
#include <vector>
#include <utility>

class Lexer {
private:
    std::string source;
    size_t current = 0;

    std::vector<Token> tokens;

public:
    explicit Lexer(std::string source)
        : source(std::move(source)) {}

    std::vector<Token> tokenize();

private:
    void scan_token();

    bool isEnd();

    char peek();
    char peekNext();
    char advance();

    void skipWhitespace();

    void stringm();
    void identifier();
    void skipComment();
};
