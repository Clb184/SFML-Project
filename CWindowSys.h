#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class CMenu {
	
public:
	//Public functions
	CMenu() {
	}

	void initMenu(int, int, float, uint32_t, uint32_t, std::string, sf::Color, const std::vector<std::string>&);
	virtual uint32_t updateLogic() = 0;
	uint32_t updateMove();
	void updateDraw(sf::RenderWindow*);

	~CMenu() {
		if (m_pOptions)
			delete[] m_pOptions;
	}

	friend class COption;
public:
	//Public vars
private:
	//Private vars
	int m_xPos;
	int m_yPos;

	uint32_t m_OptCnt;
	uint32_t m_Current = 0;
	sf::Text m_Str;
	sf::Font m_Font;
	sf::RectangleShape m_Rect;
	COption* m_pOptions;

	float m_Width;
	float m_Height;
	uint32_t m_Delay = 0;
};

class COption {
public:
	//Public functions
	COption() {}
	COption(CMenu* menu, int size): m_pMenu(menu) {
		m_Size = size;
	}

	void initOption(std::string, uint32_t);
	uint32_t updateLogic();
	void updateDraw(sf::RenderWindow*);

	friend class CMenu;
public:
	//Public vars

private:
	//Private vars
	bool m_isSelected = false;
	uint32_t m_Id;

	float m_xOff = 0;
	float m_yOff = 0;
	int m_Size = 11;

	sf::Text m_Str;
	sf::RectangleShape m_Rect;
	CMenu* m_pMenu;
};
