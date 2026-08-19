#pragma once

#include <string>

enum class TokenKind {
    Identifier,
    StringL,

    /*
     * Keywords
     */
    Write,
    Exec,

    Module,
    Import,
    Func,

    /*
     * Pre-keywords
     */
    True,
    False,

    /*
     * Symbols
     */
    LParen,
    RParen,
    LBrace,
    RBrace,

    /*
     * Symbols 2
     */
    Semicolon,
    Comma,
    Dot,

    Eof

};

struct Token {
    TokenKind kind;
    std::string lexeme;

    explicit Token(TokenKind kind, std::string lexeme)
        : kind(kind), lexeme(std::move(lexeme)) {}
};
