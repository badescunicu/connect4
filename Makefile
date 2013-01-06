build: connect4.c menu.c
	gcc -o connect4 connect4.c menu.c game.c -lncurses
clean:
	rm connect4
