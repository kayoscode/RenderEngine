#include "defs.h"
#include <iostream>
#include "Vector3.h"

int main(void){
	Vector3 value;
	initscr();
	raw();
	noecho();

	printw("this is a test of ncurses\n");
	getch();

	endwin();

	return 0;
}
