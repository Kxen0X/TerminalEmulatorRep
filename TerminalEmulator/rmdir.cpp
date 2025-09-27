#include "rmdir.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

extern std::wstring current_directory;

void rmdir(std::vector<std::wstring>& directories) {
	for (auto directory : directories) {
		if (std::filesystem::exists(current_directory + std::format(LR"(\{})", directory)) && std::filesystem::is_directory(current_directory + std::format(LR"(\{})", directory))) {
			std::wcout << L"hello";
		}
	}
}