
#include <cmath>
#include <cstdlib>

#include "ball.h"
#include "graphics.h"
#include "paddle.h"
#include "log.h"

constexpr double PI = 3.14159265;

Ball::Ball(int x, int y, std::string sprite):
	x(x), y(y), dx(1 - 2*(rand() / (double)RAND_MAX)),
	dy(1 - 2*(rand() / (double)RAND_MAX)), sprite(sprite)
{
}

double dtor(double degrees)
{
	return degrees * (2 * PI) / 360;
}

double rtod(double radians)
{
	return radians * 360 / (2 * PI);
}

void Ball::move()
{
	x += dx;
	y += dy;
}

void Ball::draw()
{
	Graphics::draw((int)x, (int)y, sprite, false);
}

void Ball::collide(Direction direction)
{
	switch (direction) {
		case Direction::LEFT:
		case Direction::RIGHT:
			dx *= -1;
			break;
		case Direction::UP:
		case Direction::DOWN:
			dy *= -1;
			break;
	}
}

void Ball::collide(Direction direction, Paddle *paddle)
{
	collide(direction);
	dy += paddle->dy;
}
