CC := gcc
CFLAGS := -ggdb -Wall -Werror -O -std=c99 -D_DEFAULT_SOURCE

all: csv

csv: csv.o program.o
	$(CC) $(CFLAGS) -o $@ $^

csv.o: csv.c program.h

program.o: program.c program.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f csv *.o

.PHONY: all clean
