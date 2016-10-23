OPEN= $(pkg-config --cflags --libs opencv) -Wall
CC=gcc

juego: TATETI.o conexiones.o
		$(CC) TATETI.o conexiones.o $(pkg-config --cflags --libs opencv) -Wall -o juego


TATETI.o:TATETI.c  conexiones.h
			$(CC) -c  TATETI.c $(pkg-config --cflags --libs opencv) -Wall



conexiones.o: conexiones.c conexiones.h
			$(CC) -c   conexiones.c






clean:
		rm ­f ./*.o
		rm ­f juego
