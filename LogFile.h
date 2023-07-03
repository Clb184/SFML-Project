#pragma once
#include <fstream>
class LogFile {
public:
	~LogFile();
	static void Initialize(std::string);
	static void writeLog(std::string);
	static void close();
private:
	static std::string m_LogName;
	static std::ofstream m_LogFile;
};