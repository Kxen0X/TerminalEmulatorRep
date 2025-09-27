#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include "dir.h"
#include "cd.h"
#include "mkdir.h"
#include "rmdir.h"

std::wstring current_command;
std::wstring current_directory = LR"(\)";

// реализовать cls, rmdir, help


std::map<std::wstring, void(*)(std::vector<std::wstring>&)> commands{ {L"dir", dir}, {L"cd", cd}, {L"mkdir", mkdir}, {L"rmdir", rmdir} };

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	
	std::wcout << current_directory + L">";

	while (std::getline(std::wcin, current_command)) {
		
		std::wstring tmp;
		std::vector<std::wstring> line;
		std::wistringstream stream(current_command);
		while (stream >> tmp) {
			line.push_back(tmp);
		}
		std::wstring cmd = line[0];
		line.erase(line.begin());

		if (commands.find(cmd) != commands.end()) {
			commands[cmd](line);
		}
		else{
			std::wcout << std::format(L"\"{}\" is not recognized as internal or external command, executable program or batch file.\n", cmd);
	}
		std::wcout << current_directory + L">";

	}


}