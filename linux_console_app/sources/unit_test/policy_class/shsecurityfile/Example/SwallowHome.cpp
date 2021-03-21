#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "SHSecurityFile.h"

using namespace std;


int main () {

	SHSecurityFile sf;
	sf.AddFile("d:/a\\SwallowHome25.cpp");
	sf.AddFile("D:/DenDayThoi-KhongTuQuynhSeth-5835212.flac");
	sf.AddFile("d:/ImLang-LiLKnightP.A-2455485_hq.mp3");

	vector<string> vs = sf.GetListFile();
	for (int i = 0; i < vs.size(); i++) {
		cout << vs[i].c_str() << " -> " << sf.GetPathFile(vs[i]).c_str() << endl;
	}

	
	//sf.DeleteFile("SwallowHome25.cpp");

	//sf.Restore("SwallowHome25.cpp", "D:\\a");
	return 0;
}
