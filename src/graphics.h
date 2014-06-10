
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

#include "drawable.h"

enum class Direction {
	LEFT,
	UP,
	RIGHT,
	DOWN
};

namespace Graphics {
	extern int WIDTH, HEIGHT;
	extern std::vector<Drawable *> entities;
	
	void init();
	void draw(int x, int y, std::string sprite, bool vertical);
	void registerEntity(Drawable *d);
	void update();
	void end();
}

#endif