all:
	gcc -c ./table.c -o ./table.o
	gcc -c ./main.c -o ./main.o
	gcc ./table.o ./main.o -o ./app.exe
	DEL *.o
	./app.exe

run:
	./app.exe