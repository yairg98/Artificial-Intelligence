gameplay.exe: gameplay.o Othello.o
	g++ -o gameplay.exe gameplay.o Othello.o
	
gameplay.o: gameplay.cpp Player.h Othello.h
	g++ -c gameplay.cpp

Othello.exe: Othello.o
	g++ -o Othello.exe Othello.o
    
Othello.o: Othello.cpp Othello.h
	g++ -c Othello.cpp

debug:
	g++ -g -o gameplay.exe gameplay.cpp Othello.cpp

clean:
	rm -f *.exe *.o *.stackdump *~