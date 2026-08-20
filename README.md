# Meteor (0.1.0)
## Interpreter of Meteor programming language

### Try

```c++
g++ main.cpp lexer/lexer.cpp parser/parser.cpp interpreter/interpreter.cpp -o bin/meteor
```

### OR (after compiling)

```c++
./bin/meteor build.mt
```

### EASY PROGRAM

```c++

// Comment
write("Hello, World!");
write("no line", false);
write("with auto line");
write("with line", true);

exec("ls -la");
exec("mkdir newmm");
```

### NEW_CFG

```c++
./bin/meteor new_cfg
```

## Create new config.mt with "Hello, World!" program

### Version 0.1.0 (0.1.x)
