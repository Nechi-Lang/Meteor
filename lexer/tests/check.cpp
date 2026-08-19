#include <iostream>
#include <string>

#include "../lexer.hpp"
#include "../token.hpp"
#include "toktypename.hpp"

int main() {
    std::string source = R"(
// Meteor test

write("Hello World", true);

exec("echo Meteor");

write("Automation");
)";

    Lexer lexer(source);

    try {
        std::vector<Token> tokens = lexer.tokenize();

        for (const auto& token : tokens) {
            std::cout
                << tokenKindToString(token.kind)
                << " -> "
                << token.lexeme
                << '\n';
        }
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
