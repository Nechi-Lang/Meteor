CXX = g++

all:
	mkdir -p bin
	$(CXX) ../lexer.cpp check.cpp -o bin/check

run: all
	./bin/check

clean:
	rm -rf bin
