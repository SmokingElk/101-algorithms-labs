all:
	gcc -c ./stack.c -o ./stack.o
	gcc -c ./main.c -o ./main.o
	gcc ./stack.o ./main.o -o ./app.exe
	DEL *.o
	./app.exe

run:
	./app.exe