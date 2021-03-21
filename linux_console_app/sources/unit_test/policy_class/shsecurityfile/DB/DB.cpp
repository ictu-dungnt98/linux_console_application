#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "DB.h"
#include "SHCrypt.h"
#include "AES.h"

using namespace std;

DB::DB() {
	if (this->IsDbExists()) {
		//cout << "DB Exists" << endl;
	}
	else
	{
		cout << "DB NOT Exists" << endl;
		this->CreateDb();
	}
}
DB::~DB() {}

int DB::Insert(std::string FileName, std::string PathOfFile) {
	if (this->Read(FileName).length() != 0) {
		return -1;
	}
	ofstream DbFile(this->DBFileName.c_str(), ios::binary | ios::out | ios::in);
	if (DbFile.is_open()) {
		uint32_t FileNameEncryptLength = CalSize(FileName.length() + 1);
		uint32_t PathOfFileEncryptLength = CalSize(PathOfFile.length() + 1);

		uint8_t FileNameEncrypt[255];// = new uint8_t[FileNameEncryptLength];
		uint8_t PathOfFileEncrypt[255];// = new uint8_t[PathOfFileEncryptLength];

		uint8_t InfoEncrypt[AES_BLOCKLEN];
		memcpy(InfoEncrypt, &FileNameEncryptLength, sizeof(uint32_t));
		memcpy(InfoEncrypt + sizeof(uint32_t), &PathOfFileEncryptLength, sizeof(uint32_t));

		SHCrypt cr;
		cr.Encrypt(InfoEncrypt, AES_BLOCKLEN);
		cr.Encrypt((uint8_t*)FileName.c_str(), FileName.length() + 1, FileNameEncrypt);
		cr.Encrypt((uint8_t*)PathOfFile.c_str(), PathOfFile.length() + 1, PathOfFileEncrypt);

		DbFile.seekp(0, DbFile.end);
		int tell = DbFile.tellp();
		DbFile.write((const char*)InfoEncrypt, AES_BLOCKLEN);
		DbFile.write((const char*)FileNameEncrypt, FileNameEncryptLength);
		DbFile.write((const char*)PathOfFileEncrypt, PathOfFileEncryptLength);

		/*delete FileNameEncrypt;
		delete PathOfFileEncrypt;*/
		DbFile.close();
	}
	else {
		return -1;
	}
	return 0;
}

std::string DB::Read(std::string FileName) {
	string result = "";
	ifstream DbFile(this->DBFileName.c_str(), ios::binary);
	if (DbFile.is_open()) {
		DbFile.seekg(0, DbFile.end);
		int FileSize = DbFile.tellg();
		DbFile.seekg(0, DbFile.beg);
		while (DbFile.tellg() < FileSize)
		{
			uint32_t FileNameEncryptedLength = 0;
			uint32_t PathOfFileEncryptedLength = 0;

			uint8_t FileNameEncrypted[255];
			uint8_t PathOfFileEncrypted[255];

			uint8_t InfoDecrypt[AES_BLOCKLEN];
			DbFile.read((char*)InfoDecrypt, AES_BLOCKLEN);

			SHCrypt cr;
			cr.Decrypt(InfoDecrypt, AES_BLOCKLEN);
			memcpy(&FileNameEncryptedLength, InfoDecrypt, sizeof(uint32_t));
			memcpy(&PathOfFileEncryptedLength, InfoDecrypt + sizeof(uint32_t), sizeof(uint32_t));

			DbFile.read((char*)FileNameEncrypted, FileNameEncryptedLength);
			cr.Decrypt(FileNameEncrypted, FileNameEncryptedLength);

			if (string((const char*)FileNameEncrypted) == FileName) {
				DbFile.read((char*)PathOfFileEncrypted, PathOfFileEncryptedLength);
				cr.Decrypt(PathOfFileEncrypted, PathOfFileEncryptedLength);
				result = string((const char*)PathOfFileEncrypted);
				break;
			}
			else {
				DbFile.seekg(PathOfFileEncryptedLength, DbFile.cur);
			}
		}
		DbFile.close();
	}
	return result;
}

vector<string> DB::GetAll() {
	vector<string> result;
	ifstream DbFile(this->DBFileName.c_str(), ios::binary);
	if (DbFile.is_open()) {
		DbFile.seekg(0, DbFile.end);
		int FileSize = DbFile.tellg();
		DbFile.seekg(0, DbFile.beg);
		while (DbFile.tellg() < FileSize)
		{
			uint32_t FileNameEncryptedLength = 0;
			uint32_t PathOfFileEncryptedLength = 0;

			uint8_t FileNameEncrypted[255];
			uint8_t PathOfFileEncrypted[255];

			uint8_t InfoDecrypt[AES_BLOCKLEN];
			DbFile.read((char*)InfoDecrypt, AES_BLOCKLEN);

			SHCrypt cr;
			cr.Decrypt(InfoDecrypt, AES_BLOCKLEN);
			memcpy(&FileNameEncryptedLength, InfoDecrypt, sizeof(uint32_t));
			memcpy(&PathOfFileEncryptedLength, InfoDecrypt + sizeof(uint32_t), sizeof(uint32_t));

			DbFile.read((char*)FileNameEncrypted, FileNameEncryptedLength);
			cr.Decrypt(FileNameEncrypted, FileNameEncryptedLength);

			DbFile.seekg(PathOfFileEncryptedLength, DbFile.cur);

			result.push_back(string((const char*)FileNameEncrypted));
		}
		DbFile.close();
	}
	return result;
}

int DB::Delete(std::string FileName) {
	if (this->Read(FileName).length() == 0) {
		return 0;
	}
	ofstream DbTempFile((this->DBFileName + ".temp").c_str(), ios::binary);
	if (DbTempFile.is_open()) {
		ifstream DbFile(this->DBFileName.c_str(), ios::binary);
		if (DbFile.is_open()) {
			DbFile.seekg(0, DbFile.end);
			int FileSize = DbFile.tellg();
			DbFile.seekg(0, DbFile.beg);
			while (DbFile.tellg() < FileSize)
			{
				uint32_t FileNameEncryptedLength = 0;
				uint32_t PathOfFileEncryptedLength = 0;

				uint8_t FileNameEncrypted[255];// = new uint8_t[FileNameEncryptLength];
				uint8_t PathOfFileEncrypted[255];// = new uint8_t[PathOfFileEncryptLength];

				uint8_t InfoDecrypt[AES_BLOCKLEN];
				uint8_t bufferInfoDecrypt[AES_BLOCKLEN];

				SHCrypt cr;
				DbFile.read((char*)InfoDecrypt, AES_BLOCKLEN);
				cr.Decrypt(InfoDecrypt, AES_BLOCKLEN, bufferInfoDecrypt);
				memcpy(&FileNameEncryptedLength, bufferInfoDecrypt, sizeof(uint32_t));
				memcpy(&PathOfFileEncryptedLength, bufferInfoDecrypt + sizeof(uint32_t), sizeof(uint32_t));

				uint8_t bufferFN[255];
				DbFile.read((char*)FileNameEncrypted, FileNameEncryptedLength);
				cr.Decrypt(FileNameEncrypted, FileNameEncryptedLength, bufferFN);

				if (string((const char*)bufferFN) != FileName) {
					DbFile.read((char*)PathOfFileEncrypted, PathOfFileEncryptedLength);

					DbTempFile.write((const char*)InfoDecrypt, AES_BLOCKLEN);
					DbTempFile.write((const char*)FileNameEncrypted, FileNameEncryptedLength);
					DbTempFile.write((const char*)PathOfFileEncrypted, PathOfFileEncryptedLength);
				}
				else {
					DbFile.seekg(PathOfFileEncryptedLength, DbFile.cur);
				}
			}
			DbFile.close();
		}
		else {
			return -1;
		}
		DbTempFile.close();
		remove(this->DBFileName.c_str());
		rename((this->DBFileName + ".temp").c_str(), this->DBFileName.c_str());
	}
	else {
		return -1;
	}
	return 0;
}


bool DB::IsDbExists() {
	return this->IsDbExists(this->DBFileName);
}

bool DB::IsDbExists(std::string Name) {
	ifstream DbFile(Name.c_str(), ios::binary);
	return DbFile.good();
}

int DB::CreateDb() {
	return this->CreateDb(this->DBFileName);
}

int DB::CreateDb(std::string Name) {
	cout << "Create DB : " << Name.c_str() << endl;
	if (this->IsDbExists(Name)) {
		return true;
	}
	ofstream DbFile(this->DBFileName.c_str(), ios::binary);
	bool result = DbFile.is_open();
	DbFile.close();
	return result;
}
