all: 
	g++ -o game main.cpp -lncurses -pthread

clean :
	 rm game