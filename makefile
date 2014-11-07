CC  = gcc -Wall
BIN = htmlparser
CFLAGS = -lcurl -g

$(BIN): main.o parser.o
	$(CC) main.o parser.o -o $(BIN) -lm $(CFLAGS)

main.o: main.c parser.h
	$(CC) -c main.c $(CFLAGS)
	
parser.o: parser.c parser.h
	$(CC) -c parser.c $(CFLAGS)
	
clean:
	@rm -f *.o
	@rm $(BIN)