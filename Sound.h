#pragma once
#include <SFML/Audio.hpp>

constexpr int SOUND_MAX = 16;

class SoundManager;

class Sound {
public:
	Sound();
	void Initialize();
	bool loadSound(std::string);

	void playSound();
	void setVolume(float);
	void setPitch(float);
	bool isLastPlaying();
	bool isAllPlaying();
	void destroy();

private:
	uint32_t m_BufferIndex;
	sf::Sound m_Sound[SOUND_MAX]; //16 channels, for whatever
	sf::SoundBuffer m_SndBuffer;
	std::string m_Name;
};

class SoundManager {
public:
	bool Initialize(const std::vector<std::string>&);
	void playSound(int);
	void setVol(int);
	void setPitch(int);
	bool isLastPlaying(int);
	bool isAllPlaying(int);
	//void setVolume(float);
	//void setMasterVolume(float);
	void cleanUp();
private:
	bool loadSound(const std::string&, Sound&);
private:
	std::vector<Sound> m_SoundArray;
};