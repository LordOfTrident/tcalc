#ifndef ERROR_HH__HEADER_GUARD__
#define ERROR_HH__HEADER_GUARD__

#include <iostream> // std::cerr, std::cout
#include <string>   // std::string
#include <cstdlib>  // std::size_t

#include "colors.hh"
#include "location.hh"

class CompilerError : std::exception {
public:
	const char *what() const noexcept;
};

namespace Error {
	void Template(const Location &p_loc, const std::string &p_msg,
	              const std::string &p_title, Color p_color);

	void Throw(const Location &p_loc, const std::string &p_msg);
	void Note(const Location &p_loc, const std::string &p_msg);
	void Warning(const Location &p_loc, const std::string &p_msg);
}

#endif
