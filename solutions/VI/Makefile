dbFilename=./db

all: database dumpC processC clear
	./dump.exe $(dbFilename)
	./process.exe $(dbFilename) -f

dump: database dumpC clear
	./dump.exe $(dbFilename)

process: database processC clear
	./process.exe $(dbFilename) -f

dumpC: 
	gcc -c ./dump.c -o ./dump.o
	gcc ./database.o ./dump.o -o ./dump.exe

processC:
	gcc -c ./process.c -o ./process.o
	gcc ./database.o ./process.o -o ./process.exe

database:
	gcc -c ./database.c -o ./database.o

clear:
	DEL *.o