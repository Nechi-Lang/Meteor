#include "parser.hpp"
#include "ast.hpp"

#include <memory>
#include <stdexcept>
#include <utility>

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    if (current <= 0)
        return tokens[0];

    return tokens[current - 1];
}

Token Parser::advance() {
    Token t = peek();
    current++;
    return t;
}

bool Parser::check(TokenKind kind) {
    return peek().kind == kind;
}

bool Parser::match(TokenKind kind) {
    if (check(kind)) {
        advance();
        return true;
    }

    return false;
}

void Parser::consume(TokenKind kind, std::string msg) {
    if (match(kind))
        return;

    throw std::runtime_error(std::move(msg));
}

std::unique_ptr<Expr> Parser::primary() {

    if (match(TokenKind::StringL)) {
        return std::make_unique<StringExpr>(
            std::move(previous().lexeme)
        );
    }

    if (match(TokenKind::True)) {
        return std::make_unique<BoolExpr>(true);
    }

    if (match(TokenKind::False)) {
        return std::make_unique<BoolExpr>(false);
    }

    throw std::runtime_error(
        "\033[31m[Parser err]: unknown primary token\033[0m"
    );
}

std::unique_ptr<Stmt> Parser::writeStmt() {
    advance();

    consume(
        TokenKind::LParen,
        "\033[31m[Parser err]: expected '(' after 'write'\033[0m"
    );

    auto value = primary();

    std::unique_ptr<Expr> isNewLine =
        std::make_unique<BoolExpr>(true);

    if (match(TokenKind::Comma)) {
        isNewLine = primary();
    }

    consume(
        TokenKind::RParen,
        "\033[31m[Parser err]: expected ')' after write value\033[0m"
    );

    consume(
        TokenKind::Semicolon,
        "\033[31m[Parser err]: expected ';' after write ')'\033[0m"
    );

    return std::make_unique<WriteStatement>(
        std::move(value),
        std::move(isNewLine)
    );
}

std::unique_ptr<Stmt> Parser::execStmt() {
    advance();

    consume(
        TokenKind::LParen,
        "\033[31m[Parser err]: expected '(' after 'exec'\033[0m"
    );

    auto value = primary();

    consume(
        TokenKind::RParen,
        "\033[31m[Parser err]: expected ')' after exec value\033[0m"
    );

    consume(
        TokenKind::Semicolon,
        "\033[31m[Parser err]: expected ';' after exec ')'\033[0m"
    );

    return std::make_unique<ExecStatement>(
        std::move(value)
    );
}

std::unique_ptr<Stmt> Parser::parse_token() {

    Token t = peek();

    if (t.kind == TokenKind::Write) {
        return writeStmt();
    }

    if (t.kind == TokenKind::Exec) {
        return execStmt();
    }

    throw std::runtime_error(
        "\033[31m[Parser err]: unknown token or parser can't parse it\033[0m"
    );
}

std::unique_ptr<Program> Parser::parse() {

    auto program = std::make_unique<Program>();

    while (!check(TokenKind::Eof)) {
        program->statements.push_back(parse_token());
    }

    return program;
}
