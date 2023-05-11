#include "CGameMain.h"
#include "Engine.h"
#include <GL/glew.h>
#include "SFML\System\Time.hpp"
#include "Commons.h"

enum {
	GAME_CONTINUE = -1,
	GAME_EXIT,
	GAME_RESUME,
	GAME_RELOAD,
	GAME_CHANGE_SCRIPT
}GameState3;

bool CGameMain::initScene(std::string script) {
	cleanUp();/*
	m_RenderTex = new sf::RenderTexture[20];
	for (int i = 0; i < 20; i++) {
		m_RenderTex[i].create(1280.0f / 1.5f, 480);
	}
	for (int i = 0; i < 20; i++) {
		m_RenderTex[i].clear(sf::Color::Transparent);
	}
	constant a, inttest;*/
	if(!m_PauseMenu) m_PauseMenu = new CPauseMenu();
	std::vector<std::string> pauseMenu{
		"Resume",
		"Title"
	};
	m_PauseMenu->initMenu(320 - 64,240 - (1.5 * 24), 128, 2, 24, "Pause Menu", { 20, 30, 40, 128 }, pauseMenu);
	char* temp = this->initScript(script);
	m_MusicMan.Initialize(temp);
	//m_Anim.Initialize(temp);
	this->m_pGame->m_Renderer2D.LoadTextures(temp);
	this->m_pGame->m_Renderer2D.Initialize();
	m_EnmMan.initialize(temp);

	/*
	m_tlv[0].position = { (1280.0f / 1.5f) / -2.0f, -240};
	m_tlv[1].position = { (1280.0f / 1.5f) / 2.0f, -240};
	m_tlv[2].position = { (1280.0f / 1.5f) / 2.0f, 240};
	m_tlv[3].position = { (1280.0f / 1.5f) / -2.0f, 240};
	m_tlv[0].texCoords = { 0, 0 };
	m_tlv[1].texCoords = { 1280.0f / 1.5f, 0 };
	m_tlv[2].texCoords = { 1280.0f / 1.5f, 480 };
	m_tlv[3].texCoords = { 0, 480 };
	*/
	/*
	m_Music.openFromFile("resource\\BOSS_Xeno_a.ogg");
	m_Music.setLoopPoints(sf::Music::TimeSpan(sf::milliseconds(sf::Int64(3355)), sf::milliseconds(sf::Int64(110687))));
	m_Music.setLoop(true);
	m_Music.setVolume(30);*/
	//m_Music.play();
	m_Time = 0;
	//uint32_t test2 = 2;
	//a = 40.0;
	//inttest = int(float(a));
	return true;
}

char* CGameMain::initScript(std::string script) {
	FILE* fp;
	if (fp = fopen(script.c_str(), "rb")) {
			fseek(fp, 0, SEEK_END);
			size_t size = ftell(fp);
			m_File = new char[size];
			rewind(fp);
			fread(m_File, size, 1, fp);
			fclose(fp);
			return m_File;
	}
	else {
		return nullptr;
	}
}


uint32_t CGameMain::updateLogic() {
	uint32_t code;
	static sf::Keyboard kbd;
	if (!this->m_IsPaused) {
		if (kbd.isKeyPressed(sf::Keyboard::Escape)) {
			this->m_IsPaused = true;
			//m_Music.pause();
		}
		code = this->m_EnmMan.updateLogic();
		this->m_Time++;
	}
	else {
		code = m_PauseMenu->updateLogic();
		switch (code) {
		case RESUME:
			this->m_IsPaused = false;
			break;
		case TITLE:
			this->m_IsPaused = false;
			cleanUp();
			return	GAME_CHANGE_SCRIPT;
		}
	}/*
	float vol;
	vol = m_Music.getVolume();
	if (kbd.isKeyPressed(sf::Keyboard::Up)) {
		m_Music.setVolume(vol + 0.1);
	} else if (kbd.isKeyPressed(sf::Keyboard::Down)) {
		m_Music.setVolume(vol - 0.1);
	}*/

	return code;
}

void CGameMain::updateDraw(sf::RenderWindow* target) {
	if (!this->m_IsPaused) {
		//ang += 1.5;
		
		m_EnmMan.updateDraw( target);
	}
	const float rot = this->m_GlobalVars.screenRot;
	const float scrx = this->m_GlobalVars.screenX;
	const float scry = this->m_GlobalVars.screenY;
	const float scrsx = this->m_GlobalVars.screenSx;
	const float scrsy = this->m_GlobalVars.screenSy;
	/*
	this->m_Transform = sf::Transform::Identity;
	this->m_Transform.translate(scrx, scry)
		.rotate(rot, (1280.0f / 1.5f) / 2.0f, 240.0f)
		.scale(scrsx, scrsy, (1280.0f / 1.5f) / 2.0f, 240.0f);
	this->m_RenderState.transform = this->m_Transform;
	for (size_t i = 0; i < 20; i++) {
		this->m_RenderTex[i].display();
		this->m_RenderState.texture = &this->m_RenderTex[i].getTexture();
		target->draw(this->m_tlv, 4, sf::TriangleFan, this->m_RenderState);
	}*/
	if (this->m_IsPaused) {	
		/*
		this->m_PauseMenu->updateDraw(target);
		*/
	}
}

bool CGameMain::cleanUp() {
	//if (m_Music.getStatus() != m_Music.Stopped)
	//	m_Music.stop();
	
	//m_Music.~Music();
	m_EnmMan.cleanUp();
	m_MusicMan.cleanUp();
	//if (this->m_File)
		//delete[] this->m_File;
	//if (this->m_RenderTex)
		//delete[] this->m_RenderTex;
	//if (m_DrawTex)
		//delete[] m_DrawTex;
	return true;
}

uint32_t CPauseMenu::updateLogic() {
	uint32_t code = updateMove();
	if (code != -1) {
		switch (code) {
		case RESUME:
			break;
		case TITLE:
			break;
		}
	}
	return code;
}

CGameMain::~CGameMain() {
	cleanUp();
}

/*
template<typename T, typename ... args>
void render3D(const T& func , args... param) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	func(param...);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
}*/