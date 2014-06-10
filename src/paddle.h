
#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>

#include "graphics.h"
#include "drawable.h"

class Paddle : public Drawable {
public:
	int x, y, dy;
	Paddle(int x, int y, std::string sprite);
	void move(Direction dir);
	void draw();
	int size();
private:
	std::string sprite;
};

#endif