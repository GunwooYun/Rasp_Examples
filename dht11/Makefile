server : server.o
	gcc -o server server.o -lwiringPi

server.o : server.c
	gcc -c -o server.o server.c

clean :
	rm *.o server
