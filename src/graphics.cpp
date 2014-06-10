
#include <iostream>
#include <ncurses.h>

#include "graphics.h"

namespace Graphics {
	
int WIDTH, HEIGHT;
std::vector<Drawable *> entities;

void init()
{
	initscr();					/* Start curses mode 		*/
	raw();						/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();					/* Don't echo() while we do getch */
	curs_set(0);
	getmaxyx(stdscr, HEIGHT, WIDTH);
}

void draw(int x, int y, std::string sprite, bool vertical)
{
	if (vertical) {
		for (int i = 0; i < sprite.size(); i++) {
			mvaddch(HEIGHT - y + i, x, sprite[i]);
		}
	} else {
		mvprintw(HEIGHT - y, x, sprite.c_str());
	}
}

void registerEntity(Drawable *entity)
{
	entities.push_back(entity);
}

void update()
{	
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->draw();
	}
	refresh();
	clear();
}

void end()
{
	endwin();
}

}