#include "mkdir.h"
#include <vector>
#include <string>
#include <filesystem>


extern std::wstring current_directory;

void mkdir(std::vector<std::wstring>& directories) {
	for (std::wstring& directory : directories) {
		std::filesystem::create_directory(std::filesystem::path(current_directory + std::format(LR"(\{})", directory)));
	}
}
