build: connect4.c menu.c
	gcc -o connect4 connect4.c menu.c -lncurses
clean:
	rm connect4 connect4.o menu.o
