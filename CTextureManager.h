#pragma once
#include "Sprite.h"
#include <vector>

class CTexture {
public:
	CTexture(const char* fName) {
		this->m_Texture.loadFromFile(fName);
	}
	sf::Texture __getTexture() {
		return this->m_Texture;
	}
private:
	sf::Texture m_Texture;
};

class CTextureManager {
public:
	void setTexture(const char* fName) {
		this->m_Texture.push_back(CTexture(fName));
	}

	sf::Texture getTexture(uint32_t id) {
		return this->m_Texture[id].__getTexture();
	}

private:
	std::vector<CTexture> m_Texture;
};