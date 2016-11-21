OPENCV_LIBS = `pkg-config --cflags --libs opencv`
THREADS_LIBS = -lpthread

all: juego

juego: conexiones.o TATETI.o 
		gcc TATETI.o conexiones.o  -o juego $(OPENCV_LIBS) $(THREADS_LIBS) -Wall

TATETI.o: TATETI.c conexiones.h 
			gcc -c TATETI.c -o TATETI.o $(OPENCV_LIBS) $(THREADS_LIBS) -Wall

conexiones.o: conexiones.c conexiones.h 
				gcc -c conexiones.c -o conexiones.o $(OPENCV_LIBS) $(THREADS_LIBS) -Wall


clean: 
	rm -f *.o
	rm -f juego
#valgrind --leak-check=full
run:	juego
	 ./juego servidor.jpg

