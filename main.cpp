#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "interpreter/interpreter.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "\033[33mUsage: meteor <file.mt>\n\033[0m";
        std::cerr << "Flags:\n";
        std::cerr << "--help - print help information\n";
        return 1;
    }

    if (argc == 2 && std::string(argv[1]) == "new_cfg") {
        std::ofstream file("config.mt");

        if (!file.is_open()) {
            std::cerr << "Meteor: cannot create config.mt\n";
            return 1;
        }

        file << "write(\"Hello, World!\");\n";

        std::cout << "Meteor: created config.mt\n";

        return 0;
    }
    else if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "\n\n\033[32mHELP INFORMATION\n\033[0m";
        std::cout << "\033[33mFUNCTIONS:\033[0m\n";
        std::cout << "meteor new_cfg - create new config.mt with \"Hello, World!\" program\n\n";
        std::cout << "\033[33mFLAGS:\033[0m\n";
        std::cout << "--help - print help information about functions and flags of this interpreter\n\n\n";

        return 0;
    }

    std::string filename = argv[1];

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Meteor: cannot open file '" << filename << "'\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string source = buffer.str();

    try {
        Lexer lexer(source);
        auto tokens = lexer.tokenize();

        Parser parser(std::move(tokens));
        auto program = parser.parse();

        Interpreter interpreter(program.get());
        interpreter.interpret();

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
