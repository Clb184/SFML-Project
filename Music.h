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
	void Initialize(const std::vector<Music>&);
	Music parseFile(char*);
	void cleanUp();

	void playMusic(int);
	void resumeMusic(int);
	void stopMusic(int);
	void pauseMusic(int);

	void setVolume(int, float);
	void addVolume(int, float);

	
private:
	std::vector<Music> m_MusicFile; 
	std::vector<sf::Music> m_Music;
};

#endif