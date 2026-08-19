#include "interpreter.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

void Interpreter::interpret() {

    while (current < program->statements.size()) {

        execute(
            program->statements[current].get()
        );

        current++;
    }
}

void Interpreter::execute(Stmt* stmt) {

    if (auto* write =
        dynamic_cast<WriteStatement*>(stmt)) {

        auto* string =
            dynamic_cast<StringExpr*>(
                write->expr.get()
            );

        auto* isNewLine =
            dynamic_cast<BoolExpr*>(
                write->isNewLine.get()
            );

        if (!string) {
            throw std::runtime_error(
                "\033[31m[Interpreter err]: "
                "write() expects a string\033[0m"
            );
        }

        std::cout << string->value;

        if (isNewLine && isNewLine->value) {
            std::cout << '\n';
        }

        return;
    }

    if (auto* exec =
        dynamic_cast<ExecStatement*>(stmt)) {

        auto* string =
            dynamic_cast<StringExpr*>(
                exec->expr.get()
            );

        if (!string) {
            throw std::runtime_error(
                "\033[31m[Interpreter err]: "
                "exec() expects a string\033[0m"
            );
        }

        std::system(string->value.c_str());

        return;
    }

    throw std::runtime_error(
        "\033[31m[Interpreter err]: "
        "unknown statement\033[0m"
    );
}
