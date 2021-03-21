#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include <iostream>
#include <string.h>

#include "SHSecurityFile.h"

using namespace std;

SHSecurityFile sf;

int main() {
	vector<string> vs = sf.GetListFile();
	for (int i = 0; i < vs.size(); i++) {
		cout << vs[i].c_str() << " -> " << sf.GetPathFile(vs[i]).c_str() << endl;
		sf.DeleteFile(vs[i]);
	}

	sf.AddFile("/home/NinhNN/Music/USB/44100_Mollado-SeungRiBIGBANGBI-5530989.mp3");
	sf.AddFile("/home/NinhNN/Music/USB/ChillingMusic.wav");
	sf.AddFile("/home/NinhNN/Music/USB/DeChoEmKhocValiTinhYeuOst-VyOanh-4778751.mp3");
	sf.AddFile("/home/NinhNN/Music/USB/ITookAPillInIbizaSeebRemix-MikePosner-4903157.mp3");
	sf.AddFile("/home/NinhNN/Music/USB/NinhNN_rename.mp3");
	exit(0);
}
