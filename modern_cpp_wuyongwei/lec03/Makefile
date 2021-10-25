CC = g++
CFLAGS = -g -Wall -DTEST

lifetime1: lifetime1.cpp
	$(CC) $(CFLAGS) -o lifetime1.out lifetime1.cpp

lifetime2: lifetime2.cpp
	$(CC) $(CFLAGS) -o lifetime2.out lifetime2.cpp

return_move: return_move.cpp
	$(CC) $(CFLAGS) -o return_move.out return_move.cpp

lref_rref: lref_rref.cpp
	$(CC) $(CFLAGS) -o lref_rref.out lref_rref.cpp

clean:
	rm *.out *.o 
