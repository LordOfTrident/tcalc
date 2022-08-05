#ifndef LOC_HH__HEADER_GUARD__
#define LOC_HH__HEADER_GUARD__

#include <cstdlib>   // std::size_t
#include <string>    // std::string
#include <ostream>   // std::ostream
#include <algorithm> // std::count

#include "colors.hh"

struct Location {
	Location();

	std::size_t row, col, strLen;
	std::string line, file;

	friend std::ostream &operator <<(std::ostream &p_stream, const Location &p_loc); // debug
};

#endif
