
#include <ncurses.h>

#include "label.h"
#include "graphics.h"
#include "log.h"

Label::Label(int x, int y, std::string text): x(x), y(y), msg(text) {}

void Label::draw()
{
	Log::log("drawing the score \"" + msg +"\": ");
	Graphics::draw(x, y, msg.c_str(), false);
}

std::string Label::text(std::string txt)
{
	msg = txt;
	return msg;
}