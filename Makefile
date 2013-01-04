build: connect4

connect4: connect4.o menu.o
	gcc -o connect4 connect4.o menu.o -lncurses
connect4.o: connect4.c menu.h
	gcc -o connect4.o -c connect4.c -lncurses
menu.o: menu.c menu.h
	gcc -o menu.o -c menu.c -lncurses
clean:
	rm connect4 connect4.o menu.o
