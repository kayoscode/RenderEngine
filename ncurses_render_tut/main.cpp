#include <defs.h>

int main(){
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	printw("this is a test\n");

	getch();
	endwin();

	return 0;
}
