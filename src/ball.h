
#ifndef BALL_H
#define BALL_H

#include <iostream>

#include "drawable.h"
#include "paddle.h"

class Ball : public Drawable {
public:
	double x, y;
	double dx, dy;
	Ball(int x, int y, std::string sprite);
	void move();
	void draw();
	void collide(Direction direction);
	void collide(Direction direction, Paddle *paddle);
private:
	std::string sprite;
};

#endif