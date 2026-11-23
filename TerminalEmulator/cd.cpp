#include "cd.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <algorithm>

extern std::wstring current_directory;

void cd(std::vector<std::wstring>& new_directory) {
	

	if (new_directory.size() == 1) {
		std::replace(new_directory[0].begin(), new_directory[0].end(), L'/', L'\\');
		if (new_directory[0][0] == std::wstring(L"\\")[0] && std::filesystem::exists(new_directory[0])) {
			new_directory[0] == L"\\.." || new_directory[0] == L"\\." ? current_directory = L"\\" : current_directory = new_directory[0];
			
		}
		else if (new_directory[0][0] != std::wstring(L"\\")[0] && current_directory != L"\\" && std::filesystem::exists(current_directory + L"\\" + new_directory[0])) {
			new_directory[0] == L"\\.."
				? current_directory = std::filesystem::path(current_directory).parent_path().wstring()
				: new_directory[0] == L"\\." ? L"" : current_directory += L"\\" + new_directory[0];
		}
		else if (new_directory[0][0] != std::wstring(L"\\")[0] && std::filesystem::exists(current_directory + new_directory[0])) {
			new_directory[0] == L"\\.."
				? current_directory = std::filesystem::path(current_directory).parent_path().wstring()
				: new_directory[0] == L"\\." ? L"" : current_directory += new_directory[0];	
		}
		else std::wcout << L"The system can not find the specified path.\n\n";
	}
	else if (new_directory.size() > 1){
		std::wstring tmp;
		for (std::wstring& el : new_directory) {
			std::replace(el.begin(), el.end(), L'/', L'\\');
			tmp += L" " + el;
		}
		tmp = tmp.substr(1, tmp.size());
		if (tmp[0] == '.' || tmp.substr(0, 2) == L".." || tmp.substr(0, 3) == L"\\." || tmp.substr(0, 4) == L"\\..") {
			std::wcout << L"The system can not find the specified path.\n\n";
			return;
		}
		if (tmp.substr(tmp.size() - 2, 2) == L"..") {
			current_directory = tmp.substr(0, tmp.size() - 3);
			return;
		}
		else if (tmp[tmp.size() - 1] == '.') { 
			current_directory = tmp.substr(0, tmp.size() - 2);
			return;
		}
		if (tmp[0] == std::wstring(L"\\")[0] && std::filesystem::exists(tmp)) {
			current_directory = tmp;
		}
		else if (tmp[0] != std::wstring(L"\\")[0] && current_directory != L"\\" && std::filesystem::exists(current_directory + L"\\" + tmp)) {
			current_directory += L"\\" + tmp;

		}
		else if (tmp[0] != std::wstring(L"\\")[0] && std::filesystem::exists(current_directory + tmp)) {
			current_directory += tmp;
		}
		else {
			tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](wchar_t sym) {return std::isspace(sym);}), tmp.end());

			if (tmp[0] == std::wstring(L"\\")[0] && std::filesystem::exists(tmp)) {
				tmp.substr(tmp.size() - 2, 2) == L".."
					? current_directory = tmp.substr(0, tmp.size() - 2)
					: tmp[tmp.size() - 1] == '.' ? current_directory = tmp.substr(0, tmp.size() - 1)
					: current_directory = tmp;
			}
			else if (tmp[0] != std::wstring(L"\\")[0] && current_directory != L"\\" && std::filesystem::exists(current_directory + L"\\" + tmp)) {
				if (tmp.substr(tmp.size() - 2, 2) == L".." || tmp[tmp.size() - 1] == '.') {
					std::wcout << L"The system can not find the specified path.\n\n";
					return;
				}
				current_directory += L"\\" + tmp;

			}
			else if (tmp[0] != std::wstring(L"\\")[0] && std::filesystem::exists(current_directory + tmp)) {
				if (tmp.substr(tmp.size() - 2, 2) == L".." || tmp[tmp.size() - 1] == '.') {
					std::wcout << L"The system can not find the specified path.\n\n";
					return;
				}
				current_directory += tmp;
			}
			else std::wcout << L"The system can not find the specified path.\n\n";
		}
	}
}