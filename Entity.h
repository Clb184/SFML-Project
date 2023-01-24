#pragma once
#include "Commons.h"
#include "Sprite.h"
#include "Player.h"
#include "Anm.h"
#include "script.h"

#define ENTITY_MAX 2000

#define EFLAG_HITBOX		0b0001
#define EFLAG_HURTBOX		0b0010
#define EFLAG_NOCLIP		0b0100
#define EFLAG_DRAW			0b1000

#define EFLAG_ROTATE		0b00010000

static std::stack<int> CalcStack;

static uint32_t test[]{
	MOVR, ENM_GRF0, ENM_X,
	MOVR, ENM_GRF1, ENM_Y,
	MOVC, ENM_GRF2, 0x3c8efa35,

	PUSHR, ENM_COUNT,
	PUSHC, 180,
	MODI,
	JMPF, 54,

	PUSHR, ENM_GRF0,
	PUSHR, ENM_DIR,
	COS,
	PUSHC, 0x42C80000,
	MULF,
	ADDF,
	POP, ENM_X,

	PUSHR, ENM_GRF1,
	PUSHR, ENM_DIR,
	SIN,
	PUSHC, 0x42C80000,
	MULF,
	ADDF,
	POP, ENM_Y,

	PUSHR, ENM_DIR,
	PUSHR, ENM_GRF2,
	PUSHC, 2,
	ITOF,
	MULF,
	ADDF,
	POP, ENM_DIR,

	PUSHC, 1,
	NOP,

	JMP, 9,

	PUSHR, ENM_GRF2,
	NEGF,
	POP, ENM_GRF2,
	JMP, 16
};


class Entity {
public:
	float getX() const { return this->m_x; }
	float getY() const { return this->m_y; }
	float getAnmDir() const { return this->m_SprDir; }

	void  __entitySet(float x, float y) {
		this->m_Deleted = false;
		this->m_x = x;
		this->m_y = y;
	}

	void entityUpdateLogic(CAnmContainer* anm_cont) {
		if (this->m_Deleted)
			return;
		if (clipCheck(
			0, 800,
			0, 600, this->m_x, this->m_y, this->m_HitRad) && !(this->m_Flag & EFLAG_NOCLIP)) {
			this->m_Deleted = true;
			return;
		}
		scriptRead(anm_cont);
		this->m_Count++;
	}

	void entitySetSprite(int id, CAnmContainer* anm) {
		this->m_AnmID = id;
		m_Anm = anm->getAnimation(id);
	}

	bool entityIsAlive() {
		return !this->m_Deleted;
	}

	void entityUpdateDraw(sf::RenderWindow* target) {
		if (this->m_Deleted || m_AnmID == -1)
			return;
		m_Anm.updateAnime(target, this);
	}

	void entityDrawDebug(sf::RenderWindow* target) {

		//if (this->m_Deleted)
			//return;
		//float rnd = this->m_Dir * 180 / PI; //(this->m_Count % 360);
		drawLine(m_x, m_y, m_HitRad + 60.0f, m_Dir, 0, sf::Color{ 0xffffffff }, target);
		//drawRect(this->m_x + (cos(RAD(rnd) + RAD(90)) * 70), this->m_y + (sin(RAD(rnd) + RAD(90)) * 70), 400, 30, RAD(rnd), 200, 0, 0xff00ff00, this->p_Gfx);
		//drawRect(this->m_x + (cos(RAD(rnd) - RAD(90)) * 70), this->m_y + (sin(RAD(rnd) - RAD(90)) * 70), 400, 30, RAD(rnd), 200, 0, 0xff00ff00, this->p_Gfx);
		drawCircle(m_x, m_y, m_HitRad, sf::Color{ 0xffff00ff }, target);
	}

	void scriptRead(CAnmContainer*);

	void entityInitialize(uint32_t id) {
		for (int i = 0; i < 8; i++) {

			this->GRI[i * 2] = 0;
			this->GRI[(i * 2) + 1] = 0;
			this->GRF[i * 2] = 0.0f;
			this->GRF[(i * 2) + 1] = 0.0f;

			this->m_Child[i] = nullptr;
		}
		this->m_ID = id;
	}

	void setAnmId(uint32_t id) {
		
	}

	Entity() {}

	friend class CAnimation;
	friend class CEntityManager;
private:

	//Will touch these with instructions...
	uint32_t m_AnmID = -1;
	uint32_t m_ID;

	//Pos on the screen and that...
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_Dir = 0.0f;
	float m_Speed = 0.0f;

	float m_HitRad = 8.0f;
	float m_HitRot = 0.0f;
	float m_HurtRad = 8.0f;
	float m_HurtRot = 0.0f;

	uint32_t m_Flag = EFLAG_HITBOX | EFLAG_HURTBOX | EFLAG_DRAW;
	uint32_t m_Count = 0;

	int GRI[16];
	float GRF[16];

	//Animation stuff
	float m_SprDir = 0.0f;
	sf::Color m_Color = { 0, 0, 0, 255 };
	float m_sx = 1.0f;
	float m_sy = 1.0f;
	uint32_t m_BlendMode = 0;
	float m_ox = 0.0f;
	float m_oy = 0.0f;

	Entity* m_Parent = nullptr;
	Entity* m_Child[8];


	std::stack<int> m_RetStack;

	bool m_Deleted = true;
	uint32_t* p_Script = test;
	uint32_t m_Offset = 0;
	uint32_t m_Rep = 0;
	CAnimation m_Anm;
	//uint32_t m_Type;
};

class CEntityManager {
public:

	Entity* getEntityPtr(uint32_t id) {
		return &p_Entity[id];
	}

	void entityUpdateAllLogic(CAnmContainer* layer_cont) {
		for (int i = 0; i < ENTITY_MAX; i++) {
			this->p_Entity[i].entityUpdateLogic(layer_cont);
		}
	}
	void entityUpdateAllDraw(sf::RenderWindow* target) {
		for (int i = 0; i < ENTITY_MAX; i++) {
			this->p_Entity[i].entityUpdateDraw(target);
		}
	}
	void entityDrawAllDebug(sf::RenderWindow* target) {
		for (int i = 0; i < ENTITY_MAX; i++) {
			this->p_Entity[i].entityDrawDebug(target);
		}
	}
	void entitySet(const float& x,const float& y) {
		uint32_t eId;

		if ((eId = findAvailableEntity()) != -1) {
			this->p_Entity[eId].__entitySet(x, y);
		}
	}

	CEntityManager() {
		this->p_Entity = new Entity[ENTITY_MAX];
		for (int i = 0; i < ENTITY_MAX;i++) {
			this->p_Entity[i].entityInitialize(i);
		}
	}

	~CEntityManager() {
		delete[] this->p_Entity;
	}

	inline uint32_t findAvailableEntity() {
		for (int i = 0; i < ENTITY_MAX; i++) {
			if (this->p_Entity[i].m_Deleted)
				return i;
			else
				continue;
		}
		return -1;
	}

private:

	Entity m_TEntity;
	Entity* p_Entity = nullptr;

	uint32_t m_EntityCnt;
	uint32_t m_Entity_Max = 0;
};