#include <ncurses.h>

int main()
{
	initscr();
	addstr("Logbooks rule!");
	getch();
	endwin();
	return 0;
}
