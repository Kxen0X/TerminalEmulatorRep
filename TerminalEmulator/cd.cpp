#include "cd.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

extern std::wstring current_directory;

void cd(std::vector<std::wstring>& new_directory) {
	if (new_directory.size() == 1) {
		if (std::filesystem::exists(new_directory[0])) {
			current_directory = new_directory[0];
		}
		else std::wcout << L"The system can not find the specified path.\n\n";
	}
	else if (new_directory.size() == 0) current_directory = LR"(\)";
	else {
		std::wstring tmp;
		for (std::wstring& el : new_directory) {
			tmp += el;
		}
		if (std::filesystem::exists(tmp)) {
			current_directory = tmp;
		}
		else std::wcout << L"The system can not find the specified path.\n\n";
	}
}