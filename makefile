mrproper: main
	rm main.o

main: main.o
	gcc main.o -o main -lcurl -g
	
main.o: main.c
	gcc -c main.c -g