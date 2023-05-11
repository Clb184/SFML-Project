#pragma once
#include <SFML/Graphics.hpp>

struct TextSlot{
	sf::Font font; //Font to load
	std::map<uint32_t, std::string> stringMap; //Pick a custom id for string
};

class TextManager {
public:
	void Initialize(char* );
	TextSlot parseFile(char*);
private:
	sf::Text m_Text;
public:
	//Making this public for easy manipulation
	std::map<uint32_t, std::string> m_TextSlots;
};