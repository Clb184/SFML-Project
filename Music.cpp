#include "Music.h"
#include "LogFile.h"
#include <iostream>
/*
void MusicManager::Initialize(const std::vector<Music>& list) {
	for (auto& n: list) {
		FILE* pCurrentMusic;
		if (pCurrentMusic = fopen(n.FileName.c_str(), "rb")) {
			Music temp;
			size_t size, end;
			char* fBuffer;

			fseek(pCurrentMusic, 0, SEEK_END);
			end = ftell(pCurrentMusic);
			rewind(pCurrentMusic);
			size = end - ftell(pCurrentMusic);
			fBuffer = new char[size];
			fread(fBuffer, size, 1, pCurrentMusic);
			fclose(pCurrentMusic);

			temp = parseFile(fBuffer);
			m_MusicFile.push_back(temp);
			delete[] fBuffer;
		}
	}
	return;

}*/

void MusicManager::Initialize(const std::vector<Music>& list) {
	uint32_t onErrors = 0;
	sf::Music temp = {};
	this->m_Music = std::vector<sf::Music>(list.size());
	int i = 0;
	for (auto& n : list) {
		try {
			if (this->m_Music[i].openFromFile(n.FileName)) {
				this->m_Music[i].setLoop(true);
				this->m_Music[i].setLoopPoints({ sf::microseconds(n.loopStart), sf::microseconds(n.loopEnd) });
				//this->m_Music.push_back(temp);
				LogFile::writeLog("MusicManager::Initialize() > Loaded: \"" + n.FileName + "\" successfuly.");
			}
			else
				throw -1;
		}
		catch (...) {
			LogFile::writeLog("MusicManager::Initialize() > Error while loading " + n.FileName);
			//this->m_Music.push_back(temp);
			onErrors++;
		}
	}
	if (onErrors) {
		LogFile::writeLog("Warning: Couldn't load " + std::to_string(onErrors) + " Music files, used last loaded music files.");
		LogFile::writeLog("Not sure if first music file is loaded, so it may crash!");
	}
}

Music MusicManager::parseFile(char* buffer) {
	Music ret;
	char curChar;
	std::string fileName = "";

	while (curChar = *buffer++) {
		fileName.push_back(curChar);
	}
	//buffer++;
	ret.FileName = fileName;
	memcpy(&ret.loopStart, buffer, sizeof(sf::Int64) * 2);
	return ret;
}

void MusicManager::playMusic(int id) {
	this->m_Music[id].stop();
	this->m_Music[id].play();
}

void MusicManager::resumeMusic(int id) {
	this->m_Music[id].play();
}

void MusicManager::stopMusic(int id) {
	this->m_Music[id].stop();
}

void MusicManager::pauseMusic(int id) {
	this->m_Music[id].pause();
}


void MusicManager::addVolume(int id, float amn) {
	this->m_Music[id].setVolume(this->m_Music[id].getVolume() + amn);
}

void MusicManager::setVolume(int id, float amn) {
	this->m_Music[id].setVolume(amn);
}


void MusicManager::cleanUp() {
	for (auto& m : this->m_Music) {
		//if (m.getStatus() != m.Stopped)
			m.stop();
	}
	//if (m_Music.getStatus() != m_Music.Stopped)
	//	m_Music.stop();
	this->m_Music.clear();
}