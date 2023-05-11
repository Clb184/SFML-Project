#include "Enemy.h"
#include "ScriptBase.h"
#include "CGameMain.h"
#include "Engine.h"

#define ENEMY_MAX 2000

Enemy::Enemy() {
	//m_VBO = sf::VertexBuffer(sf::Quads);
	//m_VBO.create(4);
	//m_VBO.setUsage(m_VBO.Stream);


	m_x = 0.0f;
	m_y = 0.0f;
	m_sprsx = 1.0f;
	m_sprsy = 1.0f;
	m_sprdir = 0.0f;

	m_sproffx = 0.0f;
	m_sproffy = 0.0f;

	m_Time = 0;
	m_Flags = EFLAG_HITBOX | EFLAG_HURTBOX | EFLAG_DRAW | EFLAG_CLIP;
	
	m_life = 0;

	m_pParent = nullptr;
	m_drawLayer = 0;
	m_pScript.push_back(nullptr);
}

uint32_t Enemy::updateLogic(EnemyManager* EnemyList, CGameMain* game) {
	m_AnglePlayer = atan2(game->m_GlobalVars.player_X - m_x, game->m_GlobalVars.player_Y - m_y) * (180.0f / PI);
	const uint32_t ret = scriptRead(EnemyList, game);
	m_Time++;
	return ret;
}

uint32_t Enemy::scriptRead(EnemyManager* EnemyList, CGameMain* game) {
	//uint32_t ret;
	bool retflag = false;
	for (auto it = m_pScript.begin(); it != m_pScript.end(); ++it) {
		constant* temp = *it;
		while (1) {
			switch (int(temp[0])) {
				//Math stuff
			case PUSHC:
				//std::cout << "Enemy.cpp : Enemy::scriptRead() - PUSH Constant (int) = " << int(m_pScript[1]) << ".\n";
				//std::cout << "                                              (float) = " << float(m_pScript[1]) << ".\n";
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
				case ENM_SPRDIR: EnemyList->m_CalcStack.push<float>(m_sprdir); break;
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
				case ENM_SPRDIR: m_sprdir = float(ret); break;
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
					//std::cout << "Enemy.cpp : Enemy::scriptRead() - Watemp for:  " << int(m_pScript[1]) << " frames.\n";
				}

				if (--m_nop) goto LABEL_NEXT;
				temp++;
				break;

			case JMP: {
				const int offset = int(temp[1]);
				//std::cout << "Enemy.cpp : Enemy::scriptRead() - Jump wtemph offset:  " << offset << ".\n";
				temp += offset;
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
				game->m_MusicMan.playMusic(music);
			} break;

			case PAUSEMUSIC:
				game->m_MusicMan.pauseMusic();
				break;
			case RESUMEMUSIC:
				game->m_MusicMan.resumeMusic();
				break;
			case STOPMUSIC:
				game->m_MusicMan.stopMusic();
				break;
			case ADDVOLUME: {
				const float vol = EnemyList->m_CalcStack.pop<float>();
				game->m_MusicMan.addVolume(vol);
				} break;
			case SETVOLUME: {
				const float vol = EnemyList->m_CalcStack.pop<float>();
				game->m_MusicMan.setVolume(vol);
				} break;
			}
			temp++;
		}

	LABEL_NEXT:
		*it = temp;

	}
	return -1;
}


void Enemy::updateDraw(sf::RenderWindow* target, CGameMain* game) {
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



EnemyManager::EnemyManager(CGameMain* game, Game* engine) : m_pGame(game), m_pEngine(engine) {
	m_EnmArray = std::list<Enemy>(ENEMY_MAX * 25);
}

EnemyManager::~EnemyManager() {
	cleanUp();
}


void EnemyManager::initialize(char*& file) {
	Enemy temp;//Background
	temp.m_x = (1280.0f / 1.5f) / 2.0f;
	temp.m_y = 240.0f;
	temp.m_pScript[0] = (constant*)++file;
	temp.m_SpriteSlot = 1;
	temp.m_QuadId = 2;
	temp.m_drawLayer = 4;
	m_EnmArray.push_back(temp);

	//Tsurubamis used for testing stuff...
	temp.m_pScript[0] = (constant*)(file + (17 << 2));

	temp.m_x = 0.0f;
	temp.m_drawLayer = 5;
	temp.m_SpriteSlot = 2;
	temp.m_QuadId = 1;
	for (int i = 0; i < 4000; i++) {
		temp.m_x = 50 + rand() % 750;
		temp.m_y = 40 + rand() % 400;
		temp.m_sprdir = 0;
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
	m_Tex.loadFromFile("resource/line_strip.png");
	m_Tex.setRepeated(true);
	m_Tex.generateMipmap();
	m_Tex.setSrgb(true);
	m_Tex.setSmooth(false);

	const size_t alloc = this->m_pEngine->m_Renderer2D.getSlotCount();
	this->m_DrawInfoArray.reserve(alloc);
	//this->m_DrawEx = FixedVector(alloc);
	for (int i = 0; i < alloc; i++) {
		this->m_DrawEx.push_back(FixedVector<std::pair<uint32_t, SpriteBatchInfo>>(100000));
	}
	this->m_pEngine->m_Renderer2D.configureRenderer();
}

void EnemyManager::addEnemy(constant* ScriptOff) {
	Enemy newEnm;
	newEnm.m_pScript.push_back(ScriptOff);
	newEnm.updateLogic(this, this->m_pGame);
	this->m_EnmArray.push_back(newEnm);
}

/*
std::mutex Mut;
void stupidfunc() {
	Mut.lock();
	for (int i = 0; i < 70000; i++) {

		float operations = cos(1256.19490f) * atan(26230.546f) - sin(540984.045f);
		operations = pow(cos(1256.19490f) * atan(26230.546f) - sin(540984.045f), operations);
		float more = operations * hypot(cos(1236.21656) - 165.256f, operations);
		float evenmore = sqrt(more) * pow(more, cos(15623994.594) * operations + 2560.546 - 802649049) * tan(operations);
		float stopPlease = pow(sqrt(more) * evenmore, sqrt(sqrt(sqrt(operations * tan(more)))));
		float* pMore = &more;
		float** ppMore = &pMore;
		float*** pppMore = &ppMore;
		float**** ppppMore = &pppMore;
		float***** pppppMore = &ppppMore;
		float****** ppppppMore = &pppppMore;
		float no = pow(sqrt(cos(******ppppppMore) * tan(***pppMore)) - *****pppppMore, atan2(*****pppppMore, evenmore * sin(more)));
		//continue;
	}
	Mut.unlock();
}
*/

uint32_t EnemyManager::updateLogic() {
	uint32_t retEx = -1;
	//m_Player.updateLogic(this, m_pGame);
	ThisForEach(it, this->m_PlBulletArray) {
	}
	ThisForEach(it, this->m_EnmArray) {
		if (it->m_Flags & EFLAG_CLIP) {

		}
		const uint32_t ret = it->updateLogic(this, m_pGame);
		switch (ret) {
		case ERET_KILL:
			m_EnmArray.erase(it);
		case ERET_NORMAL:
		case ERET_EXIT:
		case ERET_RESUME:
			retEx = ret;
			break;
		case ERET_RELOAD:
		case ERET_CHANGE:
			return ret;
		}
	}
	ThisForEach(it, this->m_EnmBulletArray) {
	}
	ThisForEach(it, this->m_PortraitArray) {
	}
	ThisForEach(it, this->m_TextArray) {
	}
	return retEx;
	//m_pEnmArray.updateLogic(this);
}

void EnemyManager::updateDraw(sf::RenderWindow* pWin) {
	this->m_pEngine->m_Renderer2D.activateDraw(0);
	int i = 0;
	render3D([]() {
		//std::cout << "Here's where i render 3D.\n"; 
		});
	ThisForEach(it, this->m_EnmArray) {
		
		const uint32_t slot = it->m_SpriteSlot, rect = it->m_QuadId;
		bool ondraw = (it->m_Flags & EFLAG_DRAW);
		if ((slot == UINT32_MAX || rect == UINT32_MAX) || !ondraw || i > 200000) {
			if (i > 2000) {
				//printf("Reached more than 2000 enemies, stopping drawing EnemyManager::m_EnmArray\n");
				//break;
			}
			//continue;
		}
		i++;
		SpriteBatchInfo info = { it->m_x,
								it->m_y,

								it->m_sproffx,
								it->m_sproffy,

								it->m_sprsx,
								it->m_sprsy,
								it->m_sprdir,

								1.0f,
								1.0f,
								1.0f,
								1.0f,

								it->m_drawLayer };
		//this->m_DrawInfoArray[slot].push_back
		this->m_DrawEx[slot].insert_back({ rect, info });
		//this->m_pEngine->m_Renderer2D.draw(slot, rect, info);
	}
	this->m_pEngine->m_Renderer2D.draw(m_DrawEx);
	for (auto& i : m_DrawEx)
		i.clear();
}

void EnemyManager::cleanUp() {
	this->m_EnmArray.clear();
	this->m_PortraitArray.clear();
	this->m_TextArray.clear();
	this->m_PlBulletArray.clear();
	
}