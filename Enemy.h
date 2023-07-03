#ifndef ENEMY_INCLUDED
#define ENEMY_INCLUDED
//#include <SFML/System.hpp>
#include <list>

#include "Utyls\OpenGL\Renderer2D.h"
#include "Commons.h"
#include "CalcStack.h"
#include "EnemyEnums.h"
#include "Utyls\System\FixedVector.h"

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

typedef enum {
	HITBOX_NONE = 0,
	HITBOX_RECT_NO_ROT = 1,
	HITBOX_CIRCLE = 2,
	HITBOX_RECT_ROT = 3
} HITBOX_KIND;


class Enemy {
public:
	uint32_t updateLogic(EnemyManager* , CGameMain*);
	uint32_t scriptRead(EnemyManager* , CGameMain*);
	void updateDraw(GLFWwindow*, CGameMain*);

	//Enemy() {}
	Enemy();
	friend class EnemyManager;
private:
	constant* m_pInterrupt = nullptr;
	constant* m_pOnHit = nullptr;
	constant* m_pMove = nullptr;
	uint32_t m_nop = 0;
	//std::pair<int, uint32_t> m_SpriteId = { -1, -1 };
	std::vector<constant*> m_pScript;

public:
	//X, Y pos and more stuff
	float m_x;
	float m_y;
	float m_z;
	float m_sprsx;
	float m_sprsy;
	float m_yaw;
	float m_pitch;
	float m_roll;

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
	int m_AnchorH;
	int m_AnchorV;
	int m_drawFlags;
	int m_r;
	int m_g;
	int m_b;
	int m_a;

	Enemy* m_pParent;
	Enemy* m_pChild[16];

	//Hitbox stuff
	int m_HitboxKind;
	union {
		float m_HitWidth;
		float m_Radius;
	};
	float m_HitHeight;
	float m_RectRot;

	//Movement stuff
	float m_vx;
	float m_vy;
	float m_vz;
	float m_vax;
	float m_vay;
	float m_vaz;

private:
	//Player angle
	float m_AnglePlayer;
};

class EnemyManager {
public:
	EnemyManager(CGameMain*, Renderer2D*, Game*);
	~EnemyManager();

	void initialize(char*&);
	uint32_t updateLogic();
	void updateCollission();
	void addEnemy(constant*);
	void addEnemy(const Enemy&);
	void killAllEnemy(bool);

	void updateDraw( GLFWwindow*);
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
	//std::vector<std::vector<std::pair<uint32_t, const SpriteBatchInfo&>>> m_DrawInfoArray;
	std::vector<FixedVector<std::pair<uint32_t, SpriteBatchInfo>, ENEMY_MAX>> m_DrawEx;

	uint32_t m_Time = 0;

	//sf::Texture m_Tex;
	CGameMain* m_pGame = nullptr;
	Renderer2D* m_pRenderer = nullptr;
	Game* m_pEngine = nullptr;
private:
};

#endif