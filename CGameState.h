#ifndef CGAMESTATE_INCLUDED
#define CGAMESTATE_INCLUDED
//#pragma once
//#include "CScene.h"
//#include "CMainTitle.h"
#include <stack>
#include <map>
#include <string>
#include <GLFW/glfw3.h>
//#include "Commons.h"

class Game;
class CGameMain;

class CGameState {

public:
	CGameState(Game*);
	~CGameState();

	void Initialize();
	uint32_t updateLogic();
	void updateDraw(GLFWwindow*);
	void changeState(uint32_t);
	friend class Game;
private:

	//CMainTitle* m_pTitle;
	CGameMain* m_pGame;
	Game* m_pEngine;
	//CScene* m_pScene;
	//uint8_t m_CurrentScene = SCENE_TITLE;
	std::stack<uint32_t> m_GameState;
	std::map<uint32_t, std::string> m_ScriptFile;
};
#endif