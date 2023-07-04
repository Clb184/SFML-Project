#include "TextFile.h"

TextFile::TextFile() {

}

TextFile::~TextFile() {
	if (this->m_pBuffer)
		free(this->m_pBuffer);
}


bool TextFile::loadFile(const std::string& fName) {
	FILE* pFile;
	if (pFile = fopen(fName.c_str(), "r")) {
		this->m_FileName = fName;
		fseek(pFile, 0, SEEK_END);
		this->m_Size = ftell(pFile);
		rewind(pFile);

		this->m_pBuffer = (char*)malloc(this->m_Size + 1);
		std::memset(this->m_pBuffer, 0, this->m_Size + 1);
		fread(this->m_pBuffer, this->m_Size, 1, pFile);
		fclose(pFile);
		this->m_DataStr = std::string(this->m_pBuffer);
	}
	return this->m_pBuffer;
}