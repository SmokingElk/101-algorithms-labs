all: compile run

compile:
	gcc -c ./lexeme.c -o ./lexeme.o
	gcc -c ./opClasses.c -o ./opClasses.o
	gcc -c ./exprTree.c -o ./exprTree.o
	gcc -c ./stack.c -o ./stack.o
	gcc -c ./stackPTN.c -o ./stackPTN.o
	gcc -c ./queue.c -o ./queue.o
	gcc -c ./lexer.c -o ./lexer.o
	gcc -c ./treeBuilder.c -o ./treeBuilder.o
	gcc -c ./multToSum.c -o ./multToSum.o
	gcc -c ./main.c -o ./main.o
	gcc ./lexeme.o ./opClasses.o ./stack.o ./stackPTN.o ./queue.o ./lexer.o ./exprTree.o ./treeBuilder.o ./multToSum.o ./main.o -o ./app.exe
	DEL *.o

run:
	./app.exe

run_i:
	./app.exe -i