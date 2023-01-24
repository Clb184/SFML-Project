#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "CSound.h"
#include "Player.h"
#include "Sprite.h"
#include "Commons.h"
#include "CTextureManager.h"
#include "Anm.h"

class Game {
public:
	Game(sf::RenderWindow*);

	void Update();
	void UpdateLogic();
	void UpdateDraw();
private:

	CSoundManager m_SoundManager;

	CMusicManager m_MusicManager;

	CEntityManager m_EntityManager;

	CTextureManager m_TextureManager;
	CSpriteManager m_SpriteManager;
	CAnmContainer m_AnimeContainer;

	Player m_Player;

	sf::RenderWindow* m_pWin = nullptr;
};