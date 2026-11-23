#include "dir.h"
#include <vector>
#include <filesystem>
#include <string>
#include <iostream>

extern std::wstring current_directory;

void dir(std::vector<std::wstring>& directories) {
	if (directories.size() != 0) {
		for (std::wstring directory : directories) {
			if (!std::filesystem::exists(directory)) {
				std::wcout << "Syntactical error in file name, folder name, or volume label\n";
				continue;
			}
			std::wcout << std::format(L"\nContent inside the folder {}\n\n", directory);
			for (const auto entry : std::filesystem::directory_iterator(directory)) {
				if (entry.is_directory()) {
					std::wcout << entry.last_write_time() << "\t\t" << L"<DIR>\t\t" << entry.path().filename() << std::endl;
				}
				if (entry.is_regular_file()) {
					std::wcout << entry.last_write_time() << "\t\t" << L"\t\t" << entry.path().filename() << std::endl;
				}
			}
			std::wcout << "\n";
		}
	}
	else {
		std::wcout << std::format(L"\nContent inside the folder {}\n\n", current_directory);
		for (const auto entry : std::filesystem::directory_iterator(current_directory)) {
			if (entry.is_directory()) {
				std::wcout << entry.last_write_time() << "\t\t" << L"<DIR>\t\t" << entry.path().filename() << std::endl;
			}
			if (entry.is_regular_file()) {
				std::wcout << entry.last_write_time() << "\t\t" << L"\t\t" << entry.path().filename() << std::endl;
			}
		}
	}
}