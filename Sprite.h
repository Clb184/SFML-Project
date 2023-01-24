#pragma once
#include "D:\repos\ClbLib\ClbLib\ClbLib.h"
#include <SFML\Graphics.hpp>
#include <map>

class CAnimation;
class CSprite;
class CSpriteManager;

typedef std::map<int, CSprite*> SpriteContainer;

class CSprite {
public:
	void __setSprite(sf::Texture tex, const float& ox, const float& oy, const float& w,  const float& h) {


		tex.setRepeated(true);
		this->m_Width = fabs(w);
		this->m_Height = fabs(h);

		this->m_ox = w / 2;
		this->m_oy = h / 2;

		this->m_Sprite.setOrigin(w /2, h /2 );
		this->m_Sprite.setTexture(tex);
		this->m_Sprite.setTextureRect(sf::IntRect(ox, oy, w, h));
	}

	//
	CSprite() {
		this->m_Sprite.setTextureRect(sf::IntRect(0, 0, 1, 1));
	}
	~CSprite() {
	}

	friend class CSpriteManager;
	friend class CAnimation;

private:
	float m_ox;
	float m_oy;

	int32_t m_Width;
	int32_t m_Height;

	sf::Sprite m_Sprite = {};
	//sf::Texture* m_pTex = nullptr;
};

class CSpriteManager {
public:
	void setSprite(const int& id, sf::Texture tex, const uint32_t& ox, const uint32_t& oy, const uint32_t& w, const uint32_t& h) {
		CSprite* sprite = new CSprite;
		sprite->__setSprite(tex, ox, oy, w, h);
		this->m_SpriteContainer.insert({id, sprite});
	}

	CSprite getSprite(int id) {
		return *m_SpriteContainer[id];
	}

	~CSpriteManager() {
		for (SpriteContainer::iterator i = m_SpriteContainer.begin(); i != m_SpriteContainer.end(); ++i) {
			delete i->second;
		}
	}
private:
	SpriteContainer m_SpriteContainer;
};
