#include "defs.h"
#include <iostream>
#include "Vector2.h"

int main(void){
	initscr();
	raw();
	noecho();

	printw("this is a test of ncurses\n");
	getch();

	endwin();

	return 0;
}
