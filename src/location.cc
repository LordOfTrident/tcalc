#include "location.hh"

Location::Location():
	row(1),
	col(1),
	strLen(0)
{}

std::ostream &operator <<(std::ostream &p_stream, const Location &p_loc) {
	std::string lineNumStr = std::to_string(p_loc.row), line = p_loc.line;

	std::size_t ptrOffset = std::count(line.begin(), line.begin() + p_loc.col - 1, '\t') * 3;

	std::size_t idx = 0;
	while (true) {
		idx = line.find("\t", idx);

		if (idx == std::string::npos)
			break;

		line.replace(idx, 1, "    ");
	}

	SetFgColor(Color::BrightWhite);
	p_stream << "    " << lineNumStr; // 10

	SetFgColor(Color::BrightWhite);
	p_stream << " | "; // 10 |

	SetFgColor(Color::Default);
	p_stream << line << "\n   " << std::string(lineNumStr.length() + 1, ' '); // 10 | 16 + asefsef

	SetFgColor(Color::BrightWhite);
	p_stream << " | "; //  10 | 16 + asefsef
	                   //     |

	SetFgColor(Color::Default);
	p_stream << std::string(ptrOffset + p_loc.col - 1, ' ');

	SetFgColor(Color::BrightMagenta);
	p_stream << '^' << std::string(p_loc.strLen == 0? 0 : p_loc.strLen - 1, '~');

	SetFgColor(Color::Default);

	/* example of how the output should look like:
		10 | 16 + asefsef
		   |      ^~~~~~~
	*/

	return p_stream;
}
