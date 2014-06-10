
#include <iostream>

#include "paddle.h"
#include "graphics.h"

Paddle::Paddle(int x, int y, std::string sprite):
	x(x), y(y), dy(0), sprite(sprite)
{
}

void Paddle::move(Direction dir)
{
	switch (dir) {
		case Direction::UP:
			y++;
			dy = 1;
			break;
		case Direction::DOWN:
			y--;
			dy = -1;
			break;
	}
}

void Paddle::draw()
{
	Graphics::draw(x, y, sprite, true);
}

int Paddle::size()
{
	return sprite.size();
}