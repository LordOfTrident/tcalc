#include "error.hh"

const char *CompilerError::what() const noexcept {
	return "Fatal error";
}

void Error::Template(const Location &p_loc, const std::string &p_msg,
                     const std::string &p_title, Color p_color) {
	SetFgColor(p_color);
	std::cerr << p_title << ": ";

	SetFgColor(Color::Default);
	std::cerr << p_msg << '\n';

	SetFgColor(Color::BrightWhite);
	std::cerr << "  -> At " << p_loc.file << (p_loc.file.empty()? "" : ":")
	          << p_loc.row << ":" << p_loc.col;

	SetFgColor(Color::Default);
	std::cerr << '\n' << p_loc << '\n' << std::endl;

}

void Error::Throw(const Location &p_loc, const std::string &p_msg) {
	Template(p_loc, p_msg, "Error", Color::BrightRed);

	throw CompilerError();
}

void Error::Note(const Location &p_loc, const std::string &p_msg) {
	Template(p_loc, p_msg, "Note", Color::BrightCyan);
}
