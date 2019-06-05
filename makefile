all: 
	g++ -o game main.cpp Player.cpp Invador.cpp Ball.cpp -lncurses -pthread

clean :
	 rm game