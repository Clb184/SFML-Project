#pragma once
#include <SFML/Graphics.hpp>
#include <list>
struct AnimeFileHeader {
	int sign;
	char FileName[32] = { 0 };//Image to load
	//int RectCnt; // How many rects has this file
	//int animeCnt; // How many animations there are
};

struct AnimeRect {
	int id;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
};

struct Anime {
	int frameCnt;
	int speed;
	int* frameIds;
};

struct Rect {
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;
};

//class Animation {
//public:
//	Animation() {};
//	~Animation();
//	void setAnimation(const Anime&, std::map<uint32_t, AnimeRect>&);
//private:
//	int m_texId;
//	int m_frameCnt = 1;
//	int m_frameSpeed = 1;
//	AnimeRect* m_frames;
//};

struct AnimeSlot {
	uint32_t texId;
	//std::map<uint32_t, sf::IntRect> vRect;
	std::map<uint32_t, Rect> vRect;
	//std::vector<Animation> vAnime;
};

class AnimationSetup {
public:
	~AnimationSetup();

	void Initialize(char*&);
	void Initialize(const std::list<std::string>&);
	AnimeSlot parseFile(char*, size_t);
	void cleanUp();
	std::vector<sf::Texture> initializeTexture();

//private:
	std::map<int, std::string> m_TexIDContainer;
	std::vector<AnimeSlot> m_AnimeArr;
};