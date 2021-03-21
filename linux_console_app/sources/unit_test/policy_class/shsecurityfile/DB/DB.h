//#pragma once
#include <iostream>
#include <vector>

class DB
{
public:
	DB();
	~DB();
	// return 0 if success
	int Insert(std::string FileName, std::string PathOfFile);
	// return string length != 0 if success
	std::string Read(std::string FileName);
	int Delete(std::string FileName);
	std::vector<std::string> GetAll();

private:
	const std::string DBFileName = "SH.db";
	bool IsDbExists();
	bool IsDbExists(std::string Name);
	int CreateDb();
	int CreateDb(std::string Name);
};

