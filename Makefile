othello.exe: othello.o
	g++ -o othello.exe othello.o
    
othello.o: othello.cpp othello.h
	g++ -c othello.cpp

debug:
	g++ -g -o othello.exe othello.cpp

clean:
	rm -f *.exe *.o *.stackdump *~