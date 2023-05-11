#include "CGameState.h"
#include "CGameMain.h"
#include <ctime>

typedef enum {
	RETURN_NORMAL = -1,
	RETURN_EXIT,
	RETURN_RESUME,
	RETURN_RELOAD,
	RETURN_CHANGE
} ReturnCode;

CGameState::CGameState(Game* pGame) {
	//m_pTitle = new CMainTitle;
	this->Initialize();
	m_pGame = new CGameMain(pGame);
	//m_pScene = m_pGame;
	if (!m_pGame->initScene(m_ScriptFile[0])) {
		std::string errStr = "Couldn't load script \"" + m_ScriptFile[0] + "\".";
		MessageBoxA(NULL, errStr.c_str(), "Error loading script", MB_OK);
		exit(-1);
	}
}

CGameState::~CGameState() {
	//m_pScene = nullptr;
	//safeDelete(m_pTitle);
	safeDelete(m_pGame);
}

void CGameState::Initialize() {
	FILE* pScriptContainer;
	char* buffer;
	char curChar;
	size_t size;
	uint32_t id;
	std::string tempName = "";

	if (pScriptContainer = fopen("scripts.bin", "rb")) {
		size_t pos = 0;
		fseek(pScriptContainer, 0, SEEK_END);
		size = ftell(pScriptContainer);
		rewind(pScriptContainer);
		buffer = new char[size];
		fread(buffer, size, 1, pScriptContainer);
		fclose(pScriptContainer);

		while (pos < size) {
			if (curChar = buffer[pos++]) {
				tempName.push_back(curChar);
			} else {
				//pos++;
				memcpy(&id, &buffer[pos], 4);
				m_ScriptFile.insert({id, tempName});
				tempName = "";
				pos += 4;
			}
		}

		delete[] buffer;
	} else {
		MessageBox(NULL, L"Couldn't open \"scripts.bin\".", L"Error", MB_OK);
		exit(-1);
	}
}

uint32_t CGameState::updateLogic() {
	time_t Timer;
	static tm* Time;
	static GameGlobals& gameVars = m_pGame->m_GlobalVars;

	time(&Timer);

	Time = localtime(&Timer);

	gameVars.year = Time->tm_year + 1900;
	gameVars.month = Time->tm_mon + 1;
	gameVars.day = Time->tm_mday;
	gameVars.hour = Time->tm_hour;
	gameVars.minute = Time->tm_min;
	gameVars.second = Time->tm_sec;

	const uint32_t retCode = m_pGame->updateLogic();
	switch (retCode) {
	case RETURN_NORMAL:
	case RETURN_EXIT:
	case RETURN_RESUME:
		break;
	case RETURN_RELOAD:
		if(!m_pGame->initScene(this->m_ScriptFile[gameVars.currentScriptId])) {
			std::string errStr = "Couldn't load script \"" + m_ScriptFile[0] + "\".";
			MessageBoxA(NULL, errStr.c_str(), "Error loading script", MB_OK);
			exit(-1);
		}
		break;
	case RETURN_CHANGE:
		if(!m_pGame->initScene(this->m_ScriptFile[gameVars.expectedScriptId])) {
			std::string errStr = "Couldn't load script \"" + m_ScriptFile[0] + "\".";
			MessageBoxA(NULL, errStr.c_str(), "Error loading script", MB_OK);
			exit(-1);
		}
		break;
		//changeState(retCode);
	}
	//if (retCode != -1 && retCode != 0)
	return retCode;
}

void CGameState::updateDraw(sf::RenderWindow* target) {
	m_pGame->updateDraw(target);
}

void CGameState::changeState(uint32_t retCode) {
	/*switch (m_CurrentScene) {
	case SCENE_TITLE:
		switch (retCode) {
		case TITLE_PLAY:
			m_CurrentScene = SCENE_GAME;
			m_pScene = m_pGame;
			break;
		}
	case SCENE_GAME:
		if (retCode == GAME_TITLE) {
			m_CurrentScene = SCENE_TITLE;
			m_pScene = m_pTitle;
			break;
		}
	}
	m_pScene->initScene();*/
}