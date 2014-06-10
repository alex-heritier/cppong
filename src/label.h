
#ifndef LABEL_H
#define LABEL_H

#include <iostream>

#include "drawable.h"

class Label : public Drawable {
public:
	Label(int x, int y, std::string text);
	void draw();
	std::string text(std::string text);
private:
	int x, y;
	std::string msg;
};

#endif