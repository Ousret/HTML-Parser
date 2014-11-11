CC  = gcc -Wall
BIN = htmlparser
CFLAGS = -lcurl -g

$(BIN): main.o parser.o commands.o
	$(CC) main.o parser.o commands.o -o $(BIN) -lm $(CFLAGS)

main.o: main.c parser.h
	$(CC) -c main.c
	
parser.o: parser.c parser.h
	$(CC) -c parser.c $(CFLAGS)

commands.o: commands.c commands.h
	$(CC) -c commands.c

clean:
	@rm -f *.o
	@rm $(BIN)