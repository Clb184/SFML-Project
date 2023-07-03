#include "LogFile.h"

LogFile::~LogFile() {
	m_LogFile << "Ending...";
	close();
}

void LogFile::Initialize(std::string name) {
	m_LogFile.open(name, std::ios::out);
	m_LogName = name;
}

void LogFile::writeLog(std::string in) {
	m_LogFile.open(m_LogName, std::ios::app);
	m_LogFile << (in + "\n");
	m_LogFile.close();
}

void LogFile::close() {
	m_LogFile.close();
}

std::ofstream LogFile::m_LogFile;
std::string LogFile::m_LogName;