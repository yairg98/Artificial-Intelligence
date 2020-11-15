othello.exe: othello.o board.o player.o testPlayer.o
	g++ -o othello.exe othello.o board.o player.o testPlayer.o
	
othello.o: othello.cpp player.h board.h
	g++ -c othello.cpp
    
board.o: board.cpp board.h
	g++ -c board.cpp
	
player.o: player.cpp player.h
	g++ -c player.cpp
	
testPlayer.o: testPlayer.cpp player.h
	g++ -c testPlayer.cpp

debug:
	g++ -g -o othello.exe othello.cpp board.cpp player.cpp

clean:
	rm -f *.exe *.o *.stackdump *~