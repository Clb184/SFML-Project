#ifndef ENEMY_INCLUDED
#define ENEMY_INCLUDED
#include "SFML/System.hpp"
#include "Commons.h"
#include "CalcStack.h"
#include <list>
#include "EnemyEnums.h"
#include "FixedVector.h"

struct SpriteBatchInfo;
class EnemyManager;
class CGameMain;
class Game;
/*
enum {
	ENEMY_X,
	ENEMY_Y,
	ENEMY_SPRSX,
	ENEMY_SPRSY,
	ENEMY_SPRDIR,
	ENEMY_SPROFFX,
	ENEMY_SPROFFY,
	ENEMY_TIME,
	ENEMY_FLAGS,
	ENEMY_LIFE,
	ENEMY_GRI0,
	ENEMY_GRF0 = ENEMY_GRI0 + 16,
	ENEMY_DRAWLAYER = ENEMY_GRF0 + 16,
	ENEMY_SPRITESLOT,
	ENEMY_QUAD,
	ENEMY_PARENT,
	ENEMY_CHILD0,

}offsetM_x;*/

class Enemy {
public:
	uint32_t updateLogic(EnemyManager* , CGameMain*);
	uint32_t scriptRead(EnemyManager* , CGameMain*);
	void updateDraw(sf::RenderWindow*, CGameMain*);

	//Enemy() {}
	Enemy();
	friend class EnemyManager;
private:
	constant* m_pInterrupt = nullptr;
	uint32_t m_nop = 0;
	//std::pair<int, uint32_t> m_SpriteId = { -1, -1 };
	std::vector<constant*> m_pScript;
	float m_AnglePlayer;

	//X, Y pos and more stuff
	float m_x;
	float m_y;
	float m_sprsx;
	float m_sprsy;
	float m_sprdir;

	float m_sproffx;
	float m_sproffy;

	uint32_t m_Time;
	uint32_t m_Flags;
	int m_life;
	int m_GRI[16];
	float m_GRF[16];

	//Drawing stuff
	int m_drawLayer;
	int m_SpriteSlot;
	uint32_t m_QuadId;

	Enemy* m_pParent;
	Enemy* m_pChild[16];

};

class EnemyManager {
public:
	EnemyManager(CGameMain*, Game*);
	~EnemyManager();

	void initialize(char*&);
	uint32_t updateLogic();
	void addEnemy(constant*);
	void updateDraw( sf::RenderWindow*);
	void cleanUp();

	CalcStack m_CalcStack;

	Enemy m_Player;
	std::list<Enemy> m_PlBulletArray;
	std::list<Enemy> m_EnmArray;
	std::list<Enemy> m_EnmBulletArray;
	std::list<Enemy> m_PortraitArray;
	std::list<Enemy> m_TextArray;
	//sf::Shader m_Shader;
	//sf::VertexBuffer m_VBO;
	std::vector<std::vector<std::pair<uint32_t, const SpriteBatchInfo&>>> m_DrawInfoArray;
	std::vector<FixedVector<std::pair<uint32_t, SpriteBatchInfo>>> m_DrawEx;

	sf::Texture m_Tex;
	CGameMain* m_pGame = nullptr;
	Game* m_pEngine = nullptr;
private:
};

#endif