#include <defs.h>
#include <iostream>

int main(void){
	initscr();
	raw();
	noecho();

	printw("this is a test of ncurses\n");
	getch();

	endwin();

	return 0;
}
