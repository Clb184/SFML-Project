#pragma once
#include "Commons.h"
#include <SFML\Audio.hpp>
#include <vector>


class CSound {
public:
	void __playSound() {
		this->m_Sound.play();
	}

	CSound(const char* fName) {
		this->m_SoundBuffer.loadFromFile(fName);
		this->m_Sound.setBuffer(this->m_SoundBuffer);
	}
private:
	sf::SoundBuffer m_SoundBuffer;
	sf::Sound m_Sound;
};

class CSoundManager {
public:
	void loadSound(const char* fName) {
		this->m_Sound.push_back(CSound(fName));
	}
	void playSound(uint32_t id) {
		this->m_Sound[id].__playSound();
	}

	~CSoundManager() {
		this->m_Sound.clear();
	}
private:
	std::vector<CSound> m_Sound;
};

class CMusic {
public:

	void updateStatus() {

	}

	void setLoop(uint32_t loop_Start, uint32_t loop_End) {
		this->m_Loop = true;
		//this->m_Music.setLoopPoints(sf::Music::Span<uint32_t>(loop_Start, loop_End));

	}

	void __fadeOut(uint32_t time) {
		float vol = this->m_Music.getVolume() / time;
		for (; time; time--) {
			this->m_Music.setVolume(this->m_Music.getVolume() - vol);
		}
		this->m_Music.setVolume(0);
	}

	void __pauseMusic() {
		this->m_Music.pause();
	}

	void __stopMusic() {
		this->m_Music.stop();
	}

	void __playMusic() {
		this->m_Music.play();
		this->m_Active = true;
	}

	CMusic(const char* fName) {
		this->m_Music.openFromFile(fName);
	}
private:
	bool m_Active = false;
	bool m_Loop = false;
	sf::Music m_Music;
};

class CMusicManager {
public:

	void musicManagerReset() {
		for (int i = m_Music.size(); i; i--) {
			delete m_Music[i - 1];
		}
	}

	void updateMusic() {
	}

	void stopMusic(uint32_t id) {
		this->m_Music[id]->__stopMusic();
	}

	void loadMusic(const char* fName) {
		CMusic* temp = new CMusic(fName);
		this->m_Music.insert(this->m_Music.end(),temp);
	}
	void playMusic(uint32_t id) {
		if (this->m_CurrentPlaying != -1)
			this->m_Music[m_CurrentPlaying]->__stopMusic();
		this->m_Music[id]->__playMusic();
	}

	void pauseMusic(uint32_t id) {
		this->m_Music[id]->__pauseMusic();
	}
	void fadeOut(uint32_t id, uint32_t time) {
		this->m_Music[id]->__fadeOut(time);
	}

	~CMusicManager() {
		musicManagerReset();
	}
private:
	uint32_t m_CurrentPlaying = -1;
	std::vector<CMusic*> m_Music;
};