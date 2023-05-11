#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Renderer2D.h"

#include <windows.h>
#include "Commons.h"
#include "Renderer2D.h"
#include "CGameState.h"

#define WIN32_LEAN_AND_MEAN

//std::mutex CheckMutex;
#define ENGINE_WH_DEFAULT sf::VideoMode(1280, 720)

#ifdef _DEBUG
	#define ENGINE_TITLE "SFML Engine | Debug Version"
	#define ENGINE_TITLE_CUSTOM " | Debug Version"
#else
	#define ENGINE_TITLE "SFML Engine"
	#define ENGINE_TITLE_CUSTOM ""
#endif

enum {
	VIDEO_360,
	VIDEO_480,
	VIDEO_720,
	VIDEO_1080,
	VIDEO_2160,
};

class Game {
public:

	Game(sf::RenderWindow*);
	~Game();
	uint32_t UpdateLogic();
	void UpdateDraw();
	void UpdateEngineWindow();

	Renderer2D m_Renderer2D;

	sf::Texture m_ScreenCap;
private:
	//Some Functions for internal use
	sf::VideoMode videoModeChg();
	void drawFPS();
	void changeWinSize();
	void checkForFullScreen();

private:
	//Variables for internal use
	uint32_t m_Time = 0;
	sf::Shader m_FpsDraw;
	sf::Clock m_Clock;
	sf::Time m_Fpstime;
	CGameState* m_State;

	//Window stuff
	std::string m_ProgName;
	//sf::View m_cutView;
	sf::RenderWindow* m_pWin;
	sf::VideoMode m_VideoMode;
	uint32_t m_WinStyle;
	uint32_t m_ChgDelay = 0;
	uint32_t m_currKind = 2; //Video mode kind: 360p, 480p, 720p, 1080p, 2160p
	bool m_isFullScreen;

	//Other system stuff
	sf::Keyboard m_kbd;

	GLfloat m_Quad[16]{
		0.0f, 0.0f,   0.0f, 0.0f,
		0.0f, 0.0f,   1.0f, 0.0f,
		0.0f, 0.0f,   1.0f, 1.0f,
		0.0f, 0.0f,   0.0f, 1.0f
	};
};
