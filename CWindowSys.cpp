#include "CWindowSys.h"
#include <SFML/OpenGL.hpp>

void CMenu::initMenu(int ox, int oy, float w, uint32_t options, uint32_t size, std::string title, 
	sf::Color col,const std::vector<std::string>& str) {

	m_xPos = ox;
	m_yPos = oy;
	m_Width = w;
	m_Height = size * (options + 1);

	m_OptCnt = options;

	m_Font.loadFromFile("C:\\Windows\\Fonts\\MSGOTHIC.TTC");

	m_Str.setFont(m_Font);
	m_Str.setString(title);
	m_Str.setCharacterSize(size);
	m_Str.setPosition(m_xPos + 2, m_yPos);

	m_Rect.setPosition(ox, oy);
	m_Rect.setSize(sf::Vector2f(w, size * (options + 1)));
	m_Rect.setFillColor(col);
	m_Rect.setOutlineColor({255, 255, 255, 255});
	m_Rect.setOutlineThickness(2);


	m_pOptions = new COption[m_OptCnt];
	for (int i = 0; i < m_OptCnt; i++) {
		m_pOptions[i] = COption(this, m_Str.getCharacterSize());
		m_pOptions[i].m_Id = i + 1;
		if(i >= str.size())
			m_pOptions[i].initOption("", i + 1);
		else
			m_pOptions[i].initOption(str[i], i + 1);
	}

	
}

uint32_t CMenu::updateMove() {
	static sf::Keyboard kbd;
	if (!m_Delay) {
		if (kbd.isKeyPressed(kbd.Up)) {
			m_pOptions[m_Current].m_isSelected = false;
			if(m_Current)
				m_Current--;
			else {
				m_Current = m_OptCnt - 1;
			}
			m_Delay = 5;
		}
		else if (kbd.isKeyPressed(kbd.Down)) {
			m_pOptions[m_Current].m_isSelected = false;
			m_Current++;
			m_Delay = 5;
		}
		else if (kbd.isKeyPressed(kbd.Escape)) {

		}
	} else {
		m_Delay--;
	}
	m_Current %= m_OptCnt;
	m_pOptions[m_Current].m_isSelected = true;
	for (int i = 0; i < m_OptCnt; i++) {
		uint32_t ret;
		if ((ret = m_pOptions[i].updateLogic()) != -1) {
			return ret;
		}
	}
	return -1;
}

void CMenu::updateDraw(sf::RenderWindow* target) {
	target->draw(m_Rect);
	target->draw(m_Str);
	for (int i = 0; i < m_OptCnt; i++) {
		m_pOptions[i].updateDraw(target);
	}
}


void COption::initOption(std::string text, uint32_t id) {
	float pos = 0;
	
	m_Id = id;

	m_Str.setFont(m_pMenu->m_Font);
	m_Str.setString(text);
	m_Str.setCharacterSize(m_Size);

	
	m_Str.setPosition(m_pMenu->m_xPos, m_pMenu->m_yPos + (id * (m_Size)));
	m_Rect.setPosition(m_pMenu->m_xPos, m_pMenu->m_yPos + (id * (m_Size)));
	m_Rect.setSize(sf::Vector2f(m_pMenu->m_Width, m_Size));
	m_Rect.setFillColor({128, 128, 100, 100});
}

void COption::updateDraw(sf::RenderWindow* target) {
	target->draw(m_Rect);
	target->draw(m_Str);
}

uint32_t COption::updateLogic() {
	static sf::Keyboard kbd;
	if (m_isSelected) {
		m_Rect.setFillColor({ 200, 200, 184, 100 });
		if (kbd.isKeyPressed(kbd.Z) || kbd.isKeyPressed(kbd.Enter)) {

			m_Rect.setFillColor({ 108, 255, 220, 255 });
			return m_Id;
		}
	}	else {
		m_Rect.setFillColor({ 128, 128, 100, 100 });
	}
	return -1;
}