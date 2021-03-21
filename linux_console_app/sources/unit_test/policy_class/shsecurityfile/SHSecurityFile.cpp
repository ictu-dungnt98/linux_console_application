#include <iostream>
#include <fstream>
#include "SHSecurityFile.h"
#include "DB.h"

using namespace std;

SHSecurityFile::SHSecurityFile() {}

SHSecurityFile::~SHSecurityFile() {}

int SHSecurityFile::AddFile(string FilePath) {
	string FileName, Path;

	int off = FilePath.find_last_of("/\\");
	Path = FilePath.substr(0, off);
	FileName = FilePath.substr(off + 1);
	cout << "Path: " << Path << endl;
	cout << "FileName: " << FileName << endl;

	DB db;
	// Check Filename is exist on database?
	string p = db.Read(FileName);
	if (p.length() != 0) {
		// exixts -> delete from db
		this->DeleteFile(FileName);
	}
	string SecurityPath;
	while (true) {
		SecurityPath = USBPath + RandomName(15);
		// check path exists ?
		ifstream f(SecurityPath);
		if (!f.good())
		{
			break;
		}
	}

	db.Insert(FileName, SecurityPath);
	rename(FilePath.c_str(), SecurityPath.c_str());

	return 0;
}

string SHSecurityFile::GetPathFile(string FileName) {
	DB db;
	return db.Read(FileName);
}

vector<string> SHSecurityFile::GetListFile() {
	DB db;
	return db.GetAll();
}

int SHSecurityFile::DeleteFile(string FileName) {
	DB db;
	string p = db.Read(FileName);
	remove(p.c_str());
	return db.Delete(FileName);
}

// Restore to default path
int SHSecurityFile::Restore(string FileName) {
	return this->Restore(FileName, USBPath);
}

// Restore with specific path
int SHSecurityFile::Restore(string FileName, string Path) {
	DB db;
	string FilePath = db.Read(FileName);
	if (FilePath.length() == 0) {
		return -1;
	}
	if (Path[Path.length() - 1] != '\\' && Path[Path.length() - 1] != '/') {
		Path = Path + '/';
	}
	if (rename(FilePath.c_str(), (Path + FileName).c_str()) == 0) {
		return db.Delete(FileName);
	}
	else {
		return -1;
	}
}

