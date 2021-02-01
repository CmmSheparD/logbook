#include <ncurses.h>

int main()
{
	initscr();
	addstr("Scrolls rule!");
	getch();
	endwin();
	return 0;
}
