//#pragma once
#include <iostream>
#include <string.h>
#include <vector>

class SHSecurityFile
{
public:
	SHSecurityFile();
	~SHSecurityFile();

	int AddFile(std::string FilePath);
	std::string GetPathFile(std::string FileName);
	std::vector<std::string> GetListFile();
	int DeleteFile(std::string FileName);
	int Restore(std::string FileName);
	int Restore(std::string FileName, std::string Path);

private:
	std::string USBPath = "/home/NinhNN/Music/USB/";
	std::string RandomName(const int len) {
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		char* name = new char[len+1];
		memset(name, '\0', len+1);
		for (int i = 0; i < len; ++i) {
			name[i] = alphanum[rand() % (62)];
		}

		std::string result = std::string(name);
		delete[] name;
		return result;
	}
};

