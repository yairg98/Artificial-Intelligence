gameplay.exe: gameplay.o othello.o
	g++ -o gameplay.exe gameplay.o othello.o
	
gameplay.o: gameplay.cpp othello.h
	g++ -c gameplay.cpp

othello.exe: othello.o
	g++ -o othello.exe othello.o
    
othello.o: othello.cpp othello.h
	g++ -c othello.cpp

debug:
	g++ -g -o gameplay.exe gameplay.cpp othello.cpp

clean:
	rm -f *.exe *.o *.stackdump *~