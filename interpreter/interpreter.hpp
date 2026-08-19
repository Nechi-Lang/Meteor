#pragma once

#include "../parser/ast.hpp"

#include <cstddef>

class Interpreter {
private:
    const Program* program;
    std::size_t current = 0;

public:
    explicit Interpreter(const Program* program)
        : program(program) {}

    void interpret();

private:
    void execute(Stmt* stmt);
};
