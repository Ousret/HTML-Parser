CC  = gcc -Wall
BIN = htmlparser
CFLAGS = -lcurl -g
INC = includes/

$(BIN): main.o parser.o commands.o
	$(CC) main.o parser.o commands.o -o $(BIN) -lm $(CFLAGS)

main.o: main.c $(INC)main.h $(INC)commands.h
	$(CC) -c main.c
	
parser.o: parser.c $(INC)parser.h
	$(CC) -c parser.c 

commands.o: commands.c $(INC)commands.h
	$(CC) -c commands.c

clean:
	@rm -f *.o
	@rm $(BIN)

install:
	@cp $(BIN) /usr/bin/$(BIN)	
