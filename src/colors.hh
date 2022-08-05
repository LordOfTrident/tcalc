#ifndef COLORS_HH__HEADER_GUARD__
#define COLORS_HH__HEADER_GUARD__

#include <iostream> // std::cout
#include <cassert>  // assert

#include "platform.hh"

enum class Color {
	Default = 0,

	Black,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White,

	Grey,
	BrightRed,
	BrightGreen,
	BrightYellow,
	BrightBlue,
	BrightMagenta,
	BrightCyan,
	BrightWhite
};

void SetFgColor(Color p_color);

#endif
