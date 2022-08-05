#include "colors.hh"

void SetFgColor(Color p_color) {
#ifdef PLATFORM_LINUX
	switch (p_color) {
	case Color::Default: std::cout << "\x1b[0m";    break;
	case Color::Black:   std::cout << "\x1b[0;30m"; break;
	case Color::Red:     std::cout << "\x1b[0;31m"; break;
	case Color::Green:   std::cout << "\x1b[0;32m"; break;
	case Color::Yellow:  std::cout << "\x1b[0;33m"; break;
	case Color::Blue:    std::cout << "\x1b[0;34m"; break;
	case Color::Magenta: std::cout << "\x1b[0;35m"; break;
	case Color::Cyan:    std::cout << "\x1b[0;36m"; break;
	case Color::White:   std::cout << "\x1b[0;37m"; break;

	case Color::Grey:          std::cout << "\x1b[1;90m"; break;
	case Color::BrightRed:     std::cout << "\x1b[1;91m"; break;
	case Color::BrightGreen:   std::cout << "\x1b[1;92m"; break;
	case Color::BrightYellow:  std::cout << "\x1b[1;93m"; break;
	case Color::BrightBlue:    std::cout << "\x1b[1;94m"; break;
	case Color::BrightMagenta: std::cout << "\x1b[1;95m"; break;
	case Color::BrightCyan:    std::cout << "\x1b[1;96m"; break;
	case Color::BrightWhite:   std::cout << "\x1b[1;97m"; break;

	default: assert(0 and "If this shows, it is an internal bug, please report it");
	}
#endif
}
