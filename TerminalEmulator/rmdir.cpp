#include "rmdir.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

extern std::wstring current_directory;

void rmdir(std::vector<std::wstring>& directories) {
	for (auto directory : directories) {
		if (directory[0] == std::wstring(L"\\")[0] && std::filesystem::exists(directory) && std::filesystem::is_directory(directory) && std::filesystem::is_empty(directory)) {
			std::filesystem::remove(directory);

		}
		else if (directory[0] != std::wstring(L"\\")[0] && current_directory != L"\\" && std::filesystem::exists(current_directory + L"\\" + directory) && std::filesystem::is_directory(current_directory + L"\\" + directory) && std::filesystem::is_empty(current_directory + L"\\" + directory)) {
			std::filesystem::remove(current_directory + L"\\" + directory);
		}
		else if (directory[0] != std::wstring(L"\\")[0] && std::filesystem::exists(current_directory + directory) && std::filesystem::is_directory(current_directory + directory) && std::filesystem::is_empty(current_directory + directory)) {
			std::filesystem::remove(current_directory + directory);
		}
		else std::wcout << L"The specified file cannot be found\n";
	}
}