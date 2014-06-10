
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <ncurses.h>

#include "graphics.h"
#include "paddle.h"
#include "ball.h"
#include "label.h"
#include "log.h"

const int FRAMES = 60;	// 60 fps

int left_score = 0, right_score = 0;
Label *score;

// function for graphics update thread
void graphicsUpdate()
{
	while (true) {
		Graphics::update();
	    std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMES));
	}
}

void boundsCheck(Ball &entity);
void collisionCheck(Ball *ball, Paddle *left, Paddle *right);

// function for ball update thread
void ballUpdate(Ball *ball, Paddle *left, Paddle *right)
{
	while (true) {
		ball->move();
		boundsCheck(*ball);
		collisionCheck(ball, left, right);
	    std::this_thread::sleep_for(std::chrono::milliseconds(1000/50));
	}
}

// checks if the ball collides with a paddle
void collisionCheck(Ball *ball, Paddle *left, Paddle *right)
{
	int x = ball->x, y = ball->y;
	if (x == left->x + 1) {
		if (y > left->y - left->size() && y <= left->y) {
			ball->collide(Direction::LEFT, left);
		}
	} else if (x == right->x - 1) {
		if (y > right->y - right->size() && y <= right->y) {
			ball->collide(Direction::RIGHT, right);
		}
	}
}

// keeps paddles on screen
void boundsCheck(Paddle &entity)
{
	if (entity.y > Graphics::HEIGHT) {
		entity.y = Graphics::HEIGHT;
	} else if (entity.y - entity.size() < 0) {
		entity.y = entity.size();
	}
	Log::log("Paddle\t" + std::to_string(entity.x) + "\t" + std::to_string(entity.y));
}

// keeps ball on screen
void boundsCheck(Ball &entity)
{
	if (entity.y > Graphics::HEIGHT) {
		entity.y = Graphics::HEIGHT;
		entity.collide(Direction::UP);
	} else if (entity.y - 1 < 0) {
		entity.y = 1;
		entity.collide(Direction::DOWN);
	}
	
	if (entity.x <= 2) {
		right_score++;
		entity.x = Graphics::WIDTH/2;
		entity.dx *= -0.8;
		entity.dy *= -0.8;
		score->text(std::to_string(left_score) + "    " + std::to_string(right_score));
	} else if (entity.x + 2 >= Graphics::WIDTH) {
		left_score++;
		entity.x = Graphics::WIDTH/2;
		entity.dx *= -0.8;
		entity.dy *= -0.8;
		score->text(std::to_string(left_score) + "    " + std::to_string(right_score));
	}
	Log::log("Ball\t" + std::to_string(entity.x) + "\t" + std::to_string(entity.y));
}

int main(int argc, char **argv)
{	
	std::cout << "Pong++" << std::endl;
	// set up ncurses
	Graphics::init();
	Log::log("Pong++ starting!");
	Paddle paddle1(2, Graphics::HEIGHT - 10, "||||||||||");	// left paddle
	Paddle paddle2(Graphics::WIDTH - 2, Graphics::HEIGHT - 10, "||||||||||"); // right paddle
	Ball ball(Graphics::WIDTH/2, Graphics::HEIGHT/2, "O");
	std::string scoreLabel(std::to_string(left_score) + "    " + std::to_string(right_score));
	score = new Label((Graphics::WIDTH - 6) / 2, Graphics::HEIGHT - 1, scoreLabel);
	Graphics::registerEntity(&paddle1);
	Graphics::registerEntity(&paddle2);
	Graphics::registerEntity(&ball);
	Graphics::registerEntity(score);
	
	// graphics update thread
	std::thread graphicsTask(graphicsUpdate);
	graphicsTask.detach();
	
	// ball update thread
	std::thread ballTask(ballUpdate, &ball, &paddle1, &paddle2);
	ballTask.detach();
	
	// main loop
	int c = 0;
	while ((c = getch()) != 'q') {
		switch (c) {
			case 'z':
			case 'w':
				paddle1.move(Direction::UP);
				boundsCheck(paddle1);
				break;
			case 'x':
			case 's':
				paddle1.move(Direction::DOWN);
				boundsCheck(paddle1);
				break;
			case ',':
			case KEY_UP:
				paddle2.move(Direction::UP);
				boundsCheck(paddle2);
				break;
			case '.':
			case KEY_DOWN:
				paddle2.move(Direction::DOWN);
				boundsCheck(paddle2);
				break;
		}
	    std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMES));
	}
	Graphics::end();
	delete score;
}
