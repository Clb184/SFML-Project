#include "Enemy.h"
#include "ScriptBase.h"
#include "CGameMain.h"
#include "Engine.h"
#include "HitCalc.inl"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <algorithm>


Enemy::Enemy() {
	//m_VBO = sf::VertexBuffer(sf::Quads);
	//m_VBO.create(4);
	//m_VBO.setUsage(m_VBO.Stream);
	m_SpriteSlot = UINT32_MAX;
	m_QuadId = UINT32_MAX;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	m_sprsx = 1.0f;
	m_sprsy = 1.0f;
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;

	m_sproffx = 0.0f;
	m_sproffy = 0.0f;

	m_Time = 0;
	m_Flags = EFLAG_HITBOX | EFLAG_HURTBOX | EFLAG_DRAW | EFLAG_CLIP;
	
	m_life = 0;

	m_vx = 0.0f;
	m_vy = 0.0f;
	m_vz = 0.0f;
	m_vax = 0.0f;
	m_vay = 0.0f;
	m_vaz = 0.0f;

	this->m_HitboxKind = HITBOX_NONE;
	this->m_HitWidth = 24.0f;
	this->m_HitHeight = 24.0f;

	m_pParent = nullptr;
	m_drawLayer = 0;
	m_pScript.push_back(nullptr);

	this->m_r = this->m_g = this->m_b = this->m_a = 255;
}

uint32_t Enemy::updateLogic(EnemyManager* EnemyList, CGameMain* game) {
	m_AnglePlayer = atan2(game->m_GlobalVars.player_X - m_x, game->m_GlobalVars.player_Y - m_y) * (180.0f / PI);
	const uint32_t ret = scriptRead(EnemyList, game);
	m_vx += m_vax;
	m_vy += m_vay;
	m_x += m_vx;
	m_y += m_vy;

	

	m_Time++;
	return ret;
}

uint32_t Enemy::scriptRead(EnemyManager* EnemyList, CGameMain* game) {
	//uint32_t ret;
	bool retflag = false;
	for (auto it = m_pScript.begin(); it != m_pScript.end(); ++it) {
		constant* temp = *it;
		while (1) {
			int test = (int)temp[0];
			switch (test) {
				//Math stuff
			case PUSHC:
				//std::cout << "Enemy.cpp : Enemy::scriptRead() - PUSH Constant (int) = " << int(temp[1]) << ".\n";
				//std::cout << "                                              (float) = " << float(temp[1]) << ".\n";
				EnemyList->m_CalcStack.push<int>(int(temp[1]));
				temp++;
				break;

			case PUSHR: {
				const int reg = int(temp[1]);
				//std::cout << "Enemy.cpp : Enemy::scriptRead() - PUSH Register " << reg << ".\n";
				/*
				switch (reg) {
				case ENM_X: EnemyList->m_CalcStack.push<float>(m_x); break;
				case ENM_Y: EnemyList->m_CalcStack.push<float>(m_y); break;
				case ENM_SPRSCALEX: EnemyList->m_CalcStack.push<float>(m_sprsx); break;
				case ENM_SPRSCALEY: EnemyList->m_CalcStack.push<float>(m_sprsy); break;
				case ENM_OFFSPRX: EnemyList->m_CalcStack.push<float>(m_sproffx); break;
				case ENM_OFFSPRY: EnemyList->m_CalcStack.push<float>(m_sproffy); break;
				case ENM_SPRDIR: EnemyList->m_CalcStack.push<float>(m_roll); break;
				case ENM_LIFE: EnemyList->m_CalcStack.push<int>(m_life); break;
				case ENM_FLAG: EnemyList->m_CalcStack.push<int>(m_Flags); break;
				case ENM_GRI0:  case ENM_GRI1:  case ENM_GRI2:  case ENM_GRI3:
				case ENM_GRI4:  case ENM_GRI5:  case ENM_GRI6:  case ENM_GRI7:
				case ENM_GRI8:  case ENM_GRI9:  case ENM_GRI10: case ENM_GRI11:
				case ENM_GRI12: case ENM_GRI13: case ENM_GRI14: case ENM_GRI15:
					EnemyList->m_CalcStack.push<int>(m_GRI[reg - ENM_GRI0]);
					break;
				case ENM_GRF0:  case ENM_GRF1:  case ENM_GRF2:  case ENM_GRF3:
				case ENM_GRF4:  case ENM_GRF5:  case ENM_GRF6:  case ENM_GRF7:
				case ENM_GRF8:  case ENM_GRF9:  case ENM_GRF10: case ENM_GRF11:
				case ENM_GRF12: case ENM_GRF13: case ENM_GRF14: case ENM_GRF15:
					EnemyList->m_CalcStack.push<float>(m_GRF[reg - ENM_GRF0]);
					break;
				}*/
				//auto add = (constant*)(&m_x + reg);
				EnemyList->m_CalcStack.push<int>(constant(*(constant*)(&m_x + reg)));
				temp++;

			} break;

			case POPR:
			{
				constant ret = EnemyList->m_CalcStack.pop<int>();
				const int reg = int(temp[1]);
				//std::cout << "Enemy.cpp : Enemy::scriptRead() - POP Register :  " << reg << " =   (int) " << int(ret)<< " .\n";
				//std::cout << "                                                  " << reg << " = (float) " << float(ret)<< " .\n";
				/*
				switch (reg) {
				case ENM_X: m_x = float(ret); break;
				case ENM_Y: m_y = float(ret); break;
				case ENM_SPRSCALEX: m_sprsx = float(ret); break;
				case ENM_SPRSCALEY: m_sprsy = float(ret); break;
				case ENM_OFFSPRX: m_sproffx = float(ret); break;
				case ENM_OFFSPRY: m_sproffy = float(ret); break;
				case ENM_SPRDIR: m_roll = float(ret); break;
				case ENM_LIFE: m_life = int(ret); break;
				case ENM_FLAG: m_Flags = int(ret); break;
				case ENM_GRI0:  case ENM_GRI1:  case ENM_GRI2:  case ENM_GRI3:
				case ENM_GRI4:  case ENM_GRI5:  case ENM_GRI6:  case ENM_GRI7:
				case ENM_GRI8:  case ENM_GRI9:  case ENM_GRI10: case ENM_GRI11:
				case ENM_GRI12: case ENM_GRI13: case ENM_GRI14: case ENM_GRI15:
					m_GRI[reg - ENM_GRI0] = int(ret);
					break;
				case ENM_GRF0:  case ENM_GRF1:  case ENM_GRF2:  case ENM_GRF3:
				case ENM_GRF4:  case ENM_GRF5:  case ENM_GRF6:  case ENM_GRF7:
				case ENM_GRF8:  case ENM_GRF9:  case ENM_GRF10: case ENM_GRF11:
				case ENM_GRF12: case ENM_GRF13: case ENM_GRF14: case ENM_GRF15:
					m_GRF[reg - ENM_GRF0] = float(ret);
					break;
				}*/
				*(&m_x + reg) = ret;
				temp++;
			} break;

			case MOVC: {
				const int reg = int(temp[1]);
				constant num = int(temp[2]);
				*(&m_x + reg) = num;
				temp+= 2;
			}break;

			case ADDI:
				EnemyList->m_CalcStack.add<int>();
				break;
			case ADDF:
				EnemyList->m_CalcStack.add<float>();
				break;
			case SUBI:
				EnemyList->m_CalcStack.sub<int>();
				break;
			case SUBF:
				EnemyList->m_CalcStack.sub<float>();
				break;
			case MULI:
				EnemyList->m_CalcStack.mul<int>();
				break;
			case MULF:
				EnemyList->m_CalcStack.mul<float>();
				break;
			case DIVI:
				EnemyList->m_CalcStack.div<int>();
				break;
			case DIVF:
				EnemyList->m_CalcStack.div<float>();
				break;
			case MOD:
				EnemyList->m_CalcStack.mod();
				break;

			case SIN:
				EnemyList->m_CalcStack.sin();
				break;
			case COS:
				EnemyList->m_CalcStack.cos();
				break;
			case ATAN2I:
				EnemyList->m_CalcStack.atan2<int>();
				break;
			case ATAN2F:
				EnemyList->m_CalcStack.atan2<float>();
				break;
			case HYPOTI:
				EnemyList->m_CalcStack.hypot<int>();
				break;
			case HYPOTF:
				EnemyList->m_CalcStack.hypot<float>();
				break;
			case NORMRAD:
				EnemyList->m_CalcStack.normrad();
				break;

			case NEGI:
				EnemyList->m_CalcStack.neg<int>();
				break;
			case NEGF:
				EnemyList->m_CalcStack.neg<float>();
				break;
			case ITOF:
				EnemyList->m_CalcStack.itof();
				break;
			case FTOI:
				EnemyList->m_CalcStack.ftoi();
				break;
			case SHL:
				EnemyList->m_CalcStack.shl();
				break;
			case SHR:
				EnemyList->m_CalcStack.shr();
				break;

			case EQI:
				EnemyList->m_CalcStack.eq<int>();
				break;
			case EQF:
				EnemyList->m_CalcStack.eq<float>();
				break;
			case NEQI:
				EnemyList->m_CalcStack.neg<int>();
				break;
			case NEQF:
				EnemyList->m_CalcStack.neg<float>();
				break;
			case GREATI:
				EnemyList->m_CalcStack.neg<int>();
				break;
			case GREATF:
				EnemyList->m_CalcStack.neg<float>();
				break;
			case GEQI:
				EnemyList->m_CalcStack.neg<int>();
				break;
			case GEQF:
				EnemyList->m_CalcStack.neg<float>();
				break;
			case LESSI:
				EnemyList->m_CalcStack.neg<int>();
				break;
			case LESSF:
				EnemyList->m_CalcStack.neg<float>();
				break;
			case LEQI:
				EnemyList->m_CalcStack.neg<int>();
				break;
			case LEQF:
				EnemyList->m_CalcStack.neg<float>();
				break;

			case AND:
				EnemyList->m_CalcStack.andop();
				break;
			case OR:
				EnemyList->m_CalcStack.orop();
				break;
			case XOR:
				EnemyList->m_CalcStack.xorop();
				break;
			case NOT:
				EnemyList->m_CalcStack.notop();
				break;

			case CRAND:
				EnemyList->m_CalcStack.crand();
				break;

			case RANDI:
				EnemyList->m_CalcStack.randi();
				break;
			case RANDF:
				EnemyList->m_CalcStack.randf();
				break;
			case RANDANG:
				EnemyList->m_CalcStack.randAng();
				break;


				//Enemy stuff
			case ENMCREATE:
			{
				constant* offset = (constant*)((int)temp + int(temp[1]));
				const uint32_t type = int(temp[2]);
				EnemyList->addEnemy(offset);
			}
			temp += 2;
			break;
			//Sprite stuff
			/*
			case SETSLOT:
				m_SpriteId.first = EnemyList->m_CalcStack.pop<int>();
				break;
			case SETSPRITE:
				m_SpriteId.second = EnemyList->m_CalcStack.pop<int>();
				break;*/
			case SETDRAWLAYER:
				m_drawLayer = EnemyList->m_CalcStack.pop<int>();
				break;

				//System stuff
			case NOP:
				if (!m_nop) {
					m_nop = int(temp[1]) + 1;
					//std::cout << "Enemy.cpp : Enemy::scriptRead() - Wait for:  " << int(m_pScript[1]) << " frames.\n";
				}

				if (--m_nop) goto LABEL_NEXT;
				temp++;
				break;

			case JMP: {
				const int offset = int(temp[1]);
				//std::cout << "Enemy.cpp : Enemy::scriptRead() - Jump with offset:  " << offset << ".\n";
				temp += offset -1;
			}	break;

			case SETINTERRUPT:
				m_pInterrupt = temp + int(temp[1]);
				break;

			case RETCODE: {
				const uint32_t ret = int(temp[1]);
				switch(ret) {
				case ERET_KILL:
					m_pScript.clear();
					m_pScript.push_back(m_pInterrupt);
					it = m_pScript.begin();
					break;
				case ERET_FORCEKILL:
					break;
				}
				return ret;
			}

			//Audio stuff

			case PLAYMUSIC: {
				const int music = EnemyList->m_CalcStack.pop<int>();
				game->m_pGame->m_MusicManager.playMusic(music);
			} break;

			case PAUSEMUSIC: {
				const int music = EnemyList->m_CalcStack.pop<int>();
				game->m_pGame->m_MusicManager.pauseMusic(music);
			}	break;
			case RESUMEMUSIC: {
				const int music = EnemyList->m_CalcStack.pop<int>();
				game->m_pGame->m_MusicManager.resumeMusic(music);
			}	break;
			case STOPMUSIC: {
				const int music = EnemyList->m_CalcStack.pop<int>();
				game->m_pGame->m_MusicManager.stopMusic(music);
			}	break;
			case ADDVOLUME: {
				const float vol = EnemyList->m_CalcStack.pop<float>();
				const int music = EnemyList->m_CalcStack.pop<int>();
				game->m_pGame->m_MusicManager.addVolume(music, vol);
				} break;
			case SETVOLUME: {
				const float vol = EnemyList->m_CalcStack.pop<float>();
				const int music = EnemyList->m_CalcStack.pop<int>();
				game->m_pGame->m_MusicManager.setVolume(music, vol);
				} break;
			case PLAYSOUND: {
				const int sound = EnemyList->m_CalcStack.pop<int>();
				game->m_pGame->m_SoundManager.playSound(sound);
			} break;
			}
			temp++;
		}

	LABEL_NEXT:
		*it = temp;

	}
	return -1;
}

void Enemy::updateDraw(GLFWwindow* target, CGameMain* game) {
	/*
	const uint32_t slot = m_SpriteId.first, rect = m_SpriteId.second;
	if (slot == -1 || rect  == -1)
		return;

	static sf::RenderStates renderState;
	//static sf::Sprite sprite;
	sf::Vertex tlv[4];
	static uint32_t texId = game->m_Anim.m_AnimeArr[slot].texId;

	//sprite.setPosition({m_x, y});
	renderState.texture = &game->m_Texture[texId];
	Rect quad = game->m_Anim.m_AnimeArr[slot].vRect[rect];
	m_tlv[0].position = {m_x, m_y};
	m_tlv[1].position = {m_x + quad.w, m_y};
	m_tlv[2].position = {m_x + quad.w, m_y + quad.h};
	m_tlv[3].position = {m_x, m_y + quad.h};

	m_tlv[0].texCoords = { quad.x, quad.y };
	m_tlv[1].texCoords = { quad.x + quad.w, quad.y };
	m_tlv[2].texCoords = { quad.x + quad.w, quad.y + quad.h };
	m_tlv[3].texCoords = { quad.x, quad.y + quad.h };
	//sprite.setTexture(*renderState.texture);
	//sprite.setTextureRect(game->m_Anim.m_AnimeArr[slot].vRect[rect]);
	m_VBO.update(m_tlv);
	target->draw(m_VBO, 0, 4, renderState);*/
}

EnemyManager::EnemyManager(CGameMain* game, Renderer2D* renderer, Game* pGame) : m_pGame(game), m_pRenderer(renderer), m_pEngine(pGame) {
	m_EnmArray.resize((size_t) ENEMY_MAX);
}

EnemyManager::~EnemyManager() {
	cleanUp();
}
constant* pScr;

void EnemyManager::initialize(char*& file) {
	Enemy temp;//Background
	temp.m_x = (1280.0f / 1.5f) / 2.0f;
	temp.m_y = 240.0f;
	temp.m_pScript[0] = (constant*)file;
	temp.m_SpriteSlot = -1;
	temp.m_QuadId = 2;
	temp.m_drawLayer = 4;
	//m_EnmArray.insert(m_EnmArray.begin(), temp);
	addEnemy(temp);
	//Tsurubamis used for testing stuff...
	temp.m_pScript[0] = (constant*)(file + (39 << 2));
	pScr = temp.m_pScript[0];
	temp.m_x = 0.0f;
	temp.m_drawLayer = 5;
	temp.m_SpriteSlot = 2;
	temp.m_QuadId = 1;
	for (int i = 0; i < 0; i++) {
		temp.m_x = 50 + rand() % 750;
		temp.m_y = 40 + rand() % 400;
		temp.m_roll = 0;
		if (i >= 5000) {
			//if(temp.m_Flags & EFLAG_DRAW)
			//	temp.m_Flags -= EFLAG_DRAW;
		}
		else {
			//if (i % 2) {
			//	if (temp.m_Flags & EFLAG_DRAW)
			//		temp.m_Flags -= EFLAG_DRAW;
			//}
			//else {
			//	
			//		temp.m_Flags |= EFLAG_DRAW;
			//}
		}
		m_EnmArray.push_back(temp);
	}
	//m_Tex.loadFromFile("resource/line_strip.png");
	//m_Tex.setRepeated(true);
	//m_Tex.generateMipmap();
	//m_Tex.setSrgb(true);
	//m_Tex.setSmooth(false);

	this->m_Player.m_QuadId = 1;
	this->m_Player.m_SpriteSlot = 0;
	this->m_Player.m_x = 400.0f;
	this->m_Player.m_y = 240.0f;
	this->m_Player.m_HitWidth =  5.0f;
	this->m_Player.m_HitHeight = 5.0f;
	this->m_Player.m_drawLayer = 6;


	const size_t alloc = this->m_pRenderer->getSlotCount();
	//this->m_DrawInfoArray.reserve(alloc);
	//this->m_DrawEx = FixedVector(alloc);
	for (int i = 0; i < alloc; i++) {
		this->m_DrawEx.push_back(FixedVector<std::pair<uint32_t, SpriteBatchInfo>, ENEMY_MAX>());
	}
}

void EnemyManager::addEnemy(constant* ScriptOff) {
	Enemy newEnm;
	newEnm.m_pScript[0] = ScriptOff;
	newEnm.updateLogic(this, this->m_pGame);
	if(this->m_EnmArray.size() < ENEMY_MAX)
		this->m_EnmArray.push_back(newEnm);
}

void EnemyManager::addEnemy(const Enemy& enm) {
	if (this->m_EnmArray.size() < ENEMY_MAX)
		this->m_EnmArray.push_back(enm);
}

void EnemyManager::killAllEnemy(bool all) {
	
	for (std::list<Enemy>::iterator it = this->m_EnmArray.begin(); it != this->m_EnmArray.end();) {
		if (!(it->m_Flags & EFLAG_NODELETE) || all) {
			auto delEnm = it; 
			++it;
			this->m_EnmArray.erase(delEnm);
		}
	}

}



//std::mutex Mut;
void stupidfunc(size_t size) {
	//Mut.lock();
	const int loop = 100;
	size = 10;
	const int a =  size * size;
	for (int i = 0; i < a; i++) {

		float operations = cos(1256.19490f) * atan(26230.546f) - sin(540984.045f);
		operations = pow(cos(1256.19490f) * atan(26230.546f) - sin(540984.045f), operations);
		//float more = operations * hypot(cos(1236.21656) - 165.256f, operations);
		//float evenmore = sqrt(more) * pow(more, cos(15623994.594) * operations + 2560.546 - 802649049) * tan(operations);
		//float stopPlease = pow(sqrt(more) * evenmore, sqrt(sqrt(sqrt(operations * tan(more)))));
		//float* pMore = &more;
		//float** ppMore = &pMore;
		//float*** pppMore = &ppMore;
		//float**** ppppMore = &pppMore;
		//float***** pppppMore = &ppppMore;
		//float****** ppppppMore = &pppppMore;
		//float no = pow(sqrt(cos(******ppppppMore) * tan(***pppMore)) - *****pppppMore, atan2(*****pppppMore, evenmore * sin(more)));
		//continue;
	}
	//Mut.unlock();
}


inline void EnemyManager::updateCollission() {
	//this->m_pEngine->m_AuxRender.bind(&this->m_pEngine->m_AuxRender);
	bool onHit = false;
	for (auto& it: this->m_EnmArray) {
		//if (HITBOX_NONE == it.m_HitboxKind)
		//	continue;
		if (hitCheckNRBNRB(this->m_Player, it)) {
			it.m_g = it.m_b = 0;
			onHit = true;
			
		}
		else {
			it.m_g = it.m_b = 255;
			//it.m_roll = 0;
			
		}
	}
	if (onHit) {
		this->m_Player.m_g = this->m_Player.m_b = 0;
	}
	else {
		this->m_Player.m_g = this->m_Player.m_b = 255;
	}
	//this->m_pEngine->m_pWin->display();
}


uint32_t EnemyManager::updateLogic() {
	Enemy enm;
	enm.m_pScript[0] = pScr;
	enm.m_pMove = pScr;
	enm.m_drawLayer = 5;
	enm.m_SpriteSlot = 2;
	enm.m_QuadId = 1;
	sf::Keyboard kbd;
	const float vel = 5.0f;
	m_Player.m_x += (kbd.isKeyPressed(kbd.A)) ? -vel : (kbd.isKeyPressed(kbd.D)) ? vel : 0.0f;
	m_Player.m_y += (kbd.isKeyPressed(kbd.W)) ? -vel : (kbd.isKeyPressed(kbd.S)) ? vel : 0.0f;
	
	enm.m_x = 200.0f;
	enm.m_y = 200.0f;
	enm.m_HitWidth = 64.0f;
	enm.m_HitHeight = 85.0f;
	enm.m_RectRot = RAD(60.0f); 
	enm.m_roll = RAD(60.0f);
	if(!this->m_Time)
		this->addEnemy(enm);
	uint32_t retEx = -1;
	static sf::Clock clock;
	float tm = clock.getElapsedTime().asSeconds();
	float add = 0.0f;
	if (!(this->m_Time % 10)) {
		const float num = 6;
		for (float i = 0; i < num; i++) {
			enm.m_x = 320.0f + cos(tm) * 200.0f;
			enm.m_y = 240.0f;// +sin(RAD((this->m_pGame->m_Time * 4)));
			enm.m_vx = cos(RAD((i *  (360.0f / num)))) * 3.0f;
			enm.m_vax = cos(RAD((i * (360.0f / num)))) * 0.0f;
			enm.m_vy = sin(RAD((i *  (360.0f / num)))) * 3.0f;
			enm.m_vay = sin(RAD((i * (360.0f / num)))) * 0.0f;
			//enm.m_vy = -3.0f;
			enm.m_roll = RAD((i * (360.0f / num))) - RAD(90.0f);
			enm.m_RectRot = RAD((i * (360.0f / num))) - RAD(90.0f);
			//enm.m_SpriteSlot++;
			this->addEnemy(enm);
			add += RAD(1.0f);
		}
	}
	//if (!(this->m_pGame->m_Time % 600) && this->m_pGame->m_Time >= 600) {
	//	this->killAllEnemy(false);
	//}
	//stupidfunc(this->m_EnmArray.size());
	//m_Player.updateLogic(this, m_pGame);
	ThisForEach(it, this->m_PlBulletArray) {
	}
	for(std::list<Enemy>::iterator it = this->m_EnmArray.begin(); it != this->m_EnmArray.end();) {
		
		if (it->m_Flags & EFLAG_CLIP) {
			if (it->m_x < 0.0f || it->m_x > 800.0f
				|| it->m_y < 0.0f || it->m_y > 600.0f) {
				auto delEnm = it;
				++it;
				m_EnmArray.erase(delEnm);
				continue;
				//continue;
			}
		}

		const uint32_t ret = it->updateLogic(this, this->m_pGame);
		//it->m_roll += (PI / 180.0) * 0.3f;
		//it->m_RectRot += (PI / 180.0) * 0.3f;
		//it->m_x += cos(tm);
		//it->m_y += sin(tm);

		//it->m_roll = tm;

		switch (ret) {
		case ERET_KILL: {
			auto delEnm = it;
			++it;
			m_EnmArray.erase(delEnm);
			continue;
		}
		case ERET_NORMAL:
		case ERET_EXIT:
		case ERET_RESUME:
			retEx = ret;
			++it;
			break;
		case ERET_RELOAD:
		case ERET_CHANGE:
			this->killAllEnemy(true);
			return ret;
		}
	}

	this->updateCollission();
	ThisForEach(it, this->m_EnmBulletArray) {
	}
	ThisForEach(it, this->m_PortraitArray) {
	}
	ThisForEach(it, this->m_TextArray) {
	}
	this->m_Time++;
	return retEx;
	//m_pEnmArray.updateLogic(this);
}

void EnemyManager::updateDraw(GLFWwindow* pWin) {
	static LayeredSpritebatch layerInfo;
	//this->m_pRenderer->activateDraw(0);
	int i = 0;
	//render3D([]() {
	//	//std::cout << "Here's where i render 3D.\n"; 
	//	});
	ThisForEach(it, this->m_EnmArray) {
		
		const uint32_t slot = it->m_SpriteSlot, rect = it->m_QuadId, layer = it->m_drawLayer;
		bool ondraw = (it->m_Flags & EFLAG_DRAW);
		if ((slot == UINT32_MAX || rect == UINT32_MAX) || !ondraw || i > ENEMY_MAX
			|| (it->m_x < -256.0f || it->m_x > 2000.0f) || (it->m_y < -256.0f || it->m_y > 560.0f)) {
			if (i > 2000) {
				//printf("Reached more than 2000 enemies, stopping drawing EnemyManager::m_EnmArray\n");
				//break;
			}
			if(slot == -1)
				continue;
		}
		//if (layerInfo.find(layer) == layerInfo.end())
			layerInfo.insert({ (int)layer, {} });
		i++;
		SpriteBatchInfo info = { it->m_x,
								it->m_y,

								it->m_sproffx,
								it->m_sproffy,

								it->m_sprsx,
								it->m_sprsy,
								it->m_roll,
								
								0,
								0,

								it->m_r,
								it->m_g,
								it->m_b,
								it->m_a,

								layer,
								slot,
								rect};
		layerInfo[layer].push_back(info);
		//this->m_DrawInfoArray[slot].push_back
		//this->m_DrawEx[slot].insert_back({ rect, info });
		//this->m_pRenderer->draw(slot, rect, info);
	}SpriteBatchInfo info = { this->m_Player.m_x,
								this->m_Player.m_y,

								this->m_Player.m_sproffx,
								this->m_Player.m_sproffy,

								this->m_Player.m_sprsx,
								this->m_Player.m_sprsy,
								this->m_Player.m_roll,

								0,
								0,

								this->m_Player.m_r,
								this->m_Player.m_g,
								this->m_Player.m_b,
								this->m_Player.m_a,

								this->m_Player.m_drawLayer,
								this->m_Player.m_SpriteSlot,
								this->m_Player.m_QuadId
	};
	//if(layerInfo.find((int)this->m_Player.m_drawLayer) == layerInfo.end())
		layerInfo.insert({ (int)this->m_Player.m_drawLayer, {} });
	layerInfo[this->m_Player.m_drawLayer].push_back(info);
	//this->m_DrawInfoArray[slot].push_back
	//this->m_DrawEx[this->m_Player.m_SpriteSlot].insert_back({ this->m_Player.m_QuadId, info });
	this->m_pRenderer->draw(layerInfo, this->m_pGame->m_Time);
	for (auto& i : m_DrawEx)
		i.clear();
	layerInfo.clear();
}

void EnemyManager::cleanUp() {
	for (auto& it : this->m_DrawEx)
		it.destroy();
	this->m_DrawEx.clear();
	this->m_EnmArray.clear();
	this->m_PortraitArray.clear();
	this->m_TextArray.clear();
	this->m_PlBulletArray.clear();
	
}