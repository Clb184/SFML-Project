#ifndef MUSIC_INCLUDED
#define MUSIC_INCLUDED
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

struct Music {
	std::string FileName = "";
	sf::Int64 loopStart;
	sf::Int64 loopEnd;
};

class MusicManager {
public:
	void Initialize(char*&);
	Music parseFile(char*);
	void cleanUp();

	void playMusic(int);
	void resumeMusic();
	void stopMusic();
	void pauseMusic();

	void setVolume(float);
	void addVolume(float);

private:
	std::vector<Music> m_MusicFile;
	sf::Music m_Music;
};

#endif