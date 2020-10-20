othello.exe: othello.o board.o
	g++ -o othello.exe othello.o board.o
	
othello.o: othello.cpp player.h board.h
	g++ -c othello.cpp

board.exe: board.o
	g++ -o board.exe board.o
    
board.o: board.cpp board.h
	g++ -c board.cpp

debug:
	g++ -g -o othello.exe othello.cpp board.cpp

clean:
	rm -f *.exe *.o *.stackdump *~