#pragma once

#include "ast.hpp"
#include "../lexer/token.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Parser {
private:
    std::vector<Token> tokens;
    size_t current = 0;

public:
    explicit Parser(std::vector<Token> tokens)
        : tokens(std::move(tokens)) {}

    std::unique_ptr<Program> parse();

private:
    Token peek();
    Token previous();
    Token advance();

    bool check(TokenKind kind);
    bool match(TokenKind kind);

    void consume(TokenKind kind, std::string msg);

    std::unique_ptr<Stmt> writeStmt();
    std::unique_ptr<Stmt> execStmt();

    std::unique_ptr<Expr> primary();

    std::unique_ptr<Stmt> parse_token();
};
