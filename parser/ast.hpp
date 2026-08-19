#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct Stmt : ASTNode {};
struct Expr : ASTNode {};

/*
 * EXPRESSIONS
 */

struct StringExpr : Expr {
    std::string value;

    explicit StringExpr(std::string value)
        : value(std::move(value)) {}
};

struct BoolExpr : Expr {
    bool value;

    explicit BoolExpr(bool value)
        : value(value) {}
};

/*
 * STATEMENTS
 */

struct ExecStatement : Stmt {
    std::unique_ptr<Expr> expr;

    explicit ExecStatement(std::unique_ptr<Expr> expr)
        : expr(std::move(expr)) {}
};

struct WriteStatement : Stmt {
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Expr> isNewLine;

    explicit WriteStatement(
        std::unique_ptr<Expr> expr,
        std::unique_ptr<Expr> isnl = nullptr
    )
        : expr(std::move(expr)),
          isNewLine(std::move(isnl)) {}
};

struct Program : ASTNode {
    std::vector<std::unique_ptr<Stmt>> statements;
};
