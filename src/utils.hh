#ifndef UTILS_HH__HEADER_GUARD__
#define UTILS_HH__HEADER_GUARD__

#include <string>    // std::string
#include <fstream>   // std::ifstream, std::ofstream
#include <stdexcept> // std::runtime_error

namespace Utils {
	std::string ReadFile(const std::string &p_path);
	void        WriteFile(const std::string &p_path, const std::string &p_content);
	bool        FileExists(const std::string &p_path);
}

#endif
