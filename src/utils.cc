#include "utils.hh"

std::string Utils::ReadFile(const std::string &p_path) {
	std::ifstream file(p_path);

	if (file.is_open()) {
		std::string line, content;
		while (std::getline(file, line))
			content += line + '\n';

		file.close();

		return content;
	} else
		throw std::runtime_error("Failed to open file '" + p_path + "' for reading");
}

void Utils::WriteFile(const std::string &p_path, const std::string &p_content) {
	std::ofstream file(p_path);

	if (file.is_open()) {
		file << p_content;

		file.close();
	} else
		throw std::runtime_error("Failed to open file '" + p_path + "' for writing");
}

bool Utils::FileExists(const std::string &p_path) {
	std::ifstream file(p_path);

	return file.good();
}
