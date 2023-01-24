#include "Engine.h"

Game::Game(sf::RenderWindow* win)
	: m_pWin(win),
	m_Player(400, 300, 10, win),
	m_EntityManager(),
	m_AnimeContainer(&m_SpriteManager)
{
	std::stack<int> stack;
	stack.push(0);
	m_TextureManager.setTexture("enm5b.png");
	m_TextureManager.setTexture("STG5BOSS.bmp");
	m_SpriteManager.setSprite(1, m_TextureManager.getTexture(0), 0, 0, 64, 64);
	m_SpriteManager.setSprite(0, m_TextureManager.getTexture(1), 0, 0, 128, 128);
	m_AnimeContainer.createAnimation(0, 1, stack);
	m_EntityManager.entitySet(300, 180);
	m_EntityManager.getEntityPtr(0)->setAnmId(0);
	m_MusicManager.loadMusic("enigmatic_doll.ogg");
	m_MusicManager.playMusic(0);
}

void Game::Update() {
	UpdateLogic();
	UpdateDraw();
}

void Game::UpdateLogic() {
	m_EntityManager.entityUpdateAllLogic(&m_AnimeContainer);
	m_Player.PlayerUpdateLogic();
}

void Game::UpdateDraw() {
	//m_EntityManager.entityUpdateAllDraw(m_pWin);
	m_EntityManager.entityDrawAllDebug(m_pWin);
	m_Player.PlayerUpdateDraw();
}