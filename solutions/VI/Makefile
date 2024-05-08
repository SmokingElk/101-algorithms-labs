CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS =

all: applicants_dump medalist_below_score

applicants_dump: applicants_dump.cpp person.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

medalist_below_score: medalist_below_score.cpp person.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f applicants_dump medalist_below_score

run: all
	./applicants_dump applicants.bin 20
	./medalist_below_score applicants.bin 50