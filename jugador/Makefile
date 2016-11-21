OPENCV_LIBS = `pkg-config --cflags --libs opencv`
THREADS_LIBS = -lpthread

all: jugador

jugador: conexiones.o JUGADOR.o 
		gcc JUGADOR.o conexiones.o   -o jugador $(OPENCV_LIBS) $(THREADS_LIBS) -Wall

JUGADOR.o: JUGADOR.c conexiones.h
			gcc -c JUGADOR.c -o JUGADOR.o $(OPENCV_LIBS) $(THREADS_LIBS) -Wall

conexiones.o: conexiones.c conexiones.h 
				gcc -c conexiones.c -o conexiones.o $(OPENCV_LIBS) $(THREADS_LIBS) -Wall



clean: 
	rm -f *.o
	rm -f jugador

run:	jugador
	./jugador retador.jpg	127.0.0.1
