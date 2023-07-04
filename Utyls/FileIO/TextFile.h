#pragma once
#include "FileIO.h"
#include <string>

class TextFile {
public:
	//Constructor and destructor
	TextFile();
	~TextFile();

	//Load manually
	bool loadFile(const std::string&);

	std::string m_DataStr = "";
private:
	std::string m_FileName = "";
	char* m_pBuffer = nullptr;
	size_t m_Size;
};