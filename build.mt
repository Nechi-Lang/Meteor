write("BUILD...");
exec("g++ main.cpp lexer/lexer.cpp parser/parser.cpp interpreter/interpreter.cpp -o bin/meteor");
write("FINISHED");
