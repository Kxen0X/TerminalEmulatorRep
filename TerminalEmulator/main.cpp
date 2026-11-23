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
#include <functional>
#include "dir.h"
#include "cd.h"
#include "mkdir.h"
#include "rmdir.h"
#include "cls.h"
#include "exit.h"
#include "help.h"


std::wstring current_command;
std::wstring current_directory = LR"(\)";



std::map<std::wstring, void(*)(std::vector<std::wstring>&)> commands{ {L"dir", dir}, {L"cd", cd}, {L"mkdir", mkdir}, {L"rmdir", rmdir}, {L"cls", cls}, {L"exit", exit}, {L"help", help} };





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
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
		line.erase(line.begin());

		if (commands.find(cmd) != commands.end()) {
			commands[cmd](line);
		}
		else{
			std::wcout << std::format(L"\"{}\" is not recognized as internal or external command, executable program or batch file.\n", cmd);
	}
		std::wcout << current_directory + L">";

	}
	return 0;
}