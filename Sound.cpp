#include "Sound.h"
#include "LogFile.h"
#include <iostream>

Sound::Sound() : m_BufferIndex(0) {

}

void Sound::Initialize() {
	//this->m_SndBuffer.loadFromFile(this->m_Name);
	for (int i = 0; i < SOUND_MAX; i++) {
		this->m_Sound[i].setBuffer(this->m_SndBuffer);
	}
}

bool Sound::loadSound(std::string name) {
	//this->m_Name = name;
	return this->m_SndBuffer.loadFromFile(name);
}

void Sound::playSound() {
	this->m_BufferIndex %= SOUND_MAX;
	this->m_Sound[this->m_BufferIndex].play();
	this->m_BufferIndex++;
}

bool Sound::isLastPlaying() {
	const int before = this->m_BufferIndex - !(this->m_BufferIndex - 1 < 0);
	return this->m_Sound[before].getStatus() == sf::Sound::Playing;
}

bool Sound::isAllPlaying() {
	bool ret = false;
	for (int i = 0; i < SOUND_MAX; i++) {
		ret |= this->m_Sound[i].getStatus() == sf::Sound::Playing;
	}
	return ret;
}

void Sound::destroy() {
	for (int i = 0; i < SOUND_MAX; i++) {
		this->m_Sound[i].stop();
		//this->m_Sound[i].setBuffer();
	}
}

//Load sound list
bool SoundManager::Initialize(const std::vector<std::string>& list) {
	int onErrors = 0;
	Sound temp;
	for (auto& a : list) {
		if (this->loadSound(a, temp)) {
			this->m_SoundArray.push_back(temp);
			//temp.Initialize();
		}
		else {
			this->m_SoundArray.push_back(temp);
			onErrors++;
		}
	}
	if (onErrors) {
		LogFile::writeLog( "Warning: Couldn't load " + std::to_string(onErrors) + " sounds, used last loaded sounds.");
		LogFile::writeLog( "Not sure if first sound is loaded, so it may crash!");
	}
	for (int i = 0; i < this->m_SoundArray.size(); i++) {
		this->m_SoundArray[i].Initialize();
	}

	return true;
}

void SoundManager::cleanUp() {
	for (auto& it : this->m_SoundArray) {
		it.destroy();
	}
	this->m_SoundArray.clear();
}

bool SoundManager::loadSound(const std::string& name, Sound& out) {
	try {
		Sound snd;
		if (snd.loadSound(name)) {
			out = snd;
			LogFile::writeLog("SoundManager::loadSound() > Loaded: \"" + name + "\" successfuly.");
			return true;
		}
		else 
			throw -1;
		
	}
	catch (...) {
		LogFile::writeLog("SoundManager::loadSound() > Error while loading ");
	}
	return false;
}

void SoundManager::playSound(int id) {
	this->m_SoundArray[id].playSound();
}

bool SoundManager::isAllPlaying(int id) {
	return this->m_SoundArray[id].isAllPlaying();
}

bool SoundManager::isLastPlaying(int id) {
	return this->m_SoundArray[id].isLastPlaying();
}