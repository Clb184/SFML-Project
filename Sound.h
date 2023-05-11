#pragma once
#include <SFML/Audio.hpp>
#include <map>

class SoundManager;

class Sound {
public:
	void Initialize(uint32_t);
	friend class SoundManager;
private:
	uint32_t m_BufferIndex = 0;
	uint32_t m_SoundMax;
	sf::Sound* m_Sound;
	sf::SoundBuffer m_SndBuffer;
};

class SoundManager {
public:
	void Initialize(char*&);
	Sound parseFile(char*);
	void playSound(int);
	//void setVolume(float);
	//void setMasterVolume(float);
	void cleanUp();
private:
	std::map<uint32_t, Sound> m_SoundArray;
};