SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++

game: gameboard
	$(CC) -c main.cpp
	$(CC) main.o GameBoard.o -o sfmal-app $(SFMLFLAGS)

gameboard:
	$(CC) -c GameBoard.cpp


clean:
	rm sfmal-app
	rm *.o
