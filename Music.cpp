#include "Music.h"

void MusicManager::Initialize(char*& buffer) {
	if (buffer) {
		Music temp;
		FILE* pCurrentMusic;
		char curChar;
		std::string fileName = "";

		while (curChar = *buffer++) {
			fileName.push_back(curChar);
		}
		if (pCurrentMusic = fopen(fileName.c_str(), "rb")) {
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
		if (*buffer) {
			Initialize(buffer);
		}
	}
	return;

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
	Music temp = m_MusicFile[id];
	m_Music.openFromFile(temp.FileName);
	m_Music.setLoop(true);
	m_Music.setLoopPoints({sf::milliseconds(temp.loopStart), sf::milliseconds(temp.loopEnd)});
	m_Music.stop();
	//m_Music.play();
}

void MusicManager::resumeMusic() {
	m_Music.play();
}

void MusicManager::stopMusic() {
	m_Music.stop();
}

void MusicManager::pauseMusic() {
	m_Music.pause();
}


void MusicManager::addVolume(float amn) {
	m_Music.setVolume(m_Music.getVolume() + amn);
}

void MusicManager::setVolume(float amn) {
	m_Music.setVolume(amn);
}


void MusicManager::cleanUp() {
	if (m_Music.getStatus() != m_Music.Stopped)
		m_Music.stop();
	m_MusicFile.clear();
}