#pragma once
#include "help.h"
#include <vector>
#include <string>
#include <iostream>

void help(std::vector<std::wstring>& unusable) {
	std::wcout << L"DIR\t Displays a list of files and subdirectories in a specified directory.\nCD\t Displays or changes the current directory.\nMKDIR\t Creates a directory.\nRMDIR\t Removes a directory.\nCLS\t Clears the screen.\nEXIT\t program termination.\n";
}
