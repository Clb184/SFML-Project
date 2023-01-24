#pragma once
#include "Sprite.h"
#include <stack>


#define LAYER_MAX 32

class Entity;

class CAnimation {
public:
	void setSpeed(const uint32_t&);
	bool updateAnime(sf::RenderWindow* target, Entity* p_Entity);

	CAnimation operator << (const CAnimation& anm) {
		if (this->m_Sprites)
			delete[] this->m_Sprites;
		this->m_Sprites = anm.m_Sprites;
		this->m_CurFrame = -1;
		this->m_Frames = anm.m_Frames;
		this->m_Time = 0;
		return *this;
	}

	CAnimation operator <<= (const CAnimation& anm) {
		*this = *this << anm;
		return *this;
	}

	/*
	push id spr_1
	push id spr_2
	push id spr_3
	push id spr_4

	push sprite cnt
	(pop)
	->cnt times pop from stack

	*/
	CAnimation() {}
	CAnimation(uint32_t num_sprites, std::stack<int>& targetStack, CSpriteManager* spr_man) {
		m_Sprites = new CSprite[num_sprites];
		CSprite temp;
		for (int i = 0;i < num_sprites; i++) {
			temp = spr_man->getSprite(targetStack.top());
			m_Sprites[i] = temp;
			targetStack.pop();
			m_Frames++;
		}
	}
	~CAnimation() {
		delete[] m_Sprites;
	}
private:
	uint32_t m_Speed = 0;
	uint32_t m_Time = 0;
	uint32_t m_CurFrame = -1;
	uint32_t m_Frames = 0;

	sf::RenderStates m_RStates;
	CSprite* m_Sprites;
};

class CAnmContainer {
public:
	void createAnimation(const uint32_t& id,const uint32_t& num_sprites, std::stack<int>& targetStack) {
		CAnimation* temp = new CAnimation(num_sprites, targetStack, m_pSpriteManager);
		m_Animation.insert({ id, temp });
	}

	CAnimation getAnimation(uint32_t id) {
		return *m_Animation[id];
	}

	CAnmContainer(CSpriteManager* spr_man) : m_pSpriteManager(spr_man) {}
	~CAnmContainer() {
		for (std::map<uint32_t, CAnimation*>::iterator i = m_Animation.begin(); i != m_Animation.end(); ++i) {
			delete i->second;
		}
		m_Animation.clear();
	}

private:
	std::map<uint32_t, CAnimation*> m_Animation;
	CSpriteManager* m_pSpriteManager;
};