#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

//#define GLEW_STATIC
//#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Utyls/System/FrameLimit.h"
//#include <SFML/System.hpp>
#include "Utyls/OpenGL/Renderer2D.h"
#include "Sound.h"
#include "Music.h"
#include "LogFile.h"
//#include <windows.h>
//#include "Commons.h"
#include "Utyls/OpenGL/3D/TriDiObject.h"
#include "CGameState.h"
//#include <SFML/Audio.hpp>

//#define WIN32_LEAN_AND_MEAN

//std::mutex CheckMutex;
#define ENGINE_WH_DEFAULT //sf::VideoMode(640, 480)

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

	sf::Music music;
	Game(GLFWwindow*&, CFrameLimiter*);
	~Game();
	uint32_t UpdateLogic();
	void UpdateDraw();
	void UpdateEngineWindow();
public:
	//Public vars
	uint32_t m_Time = 0;
	float r = 0.07f;
	float g = 0.13f;
	float b = 0.17f;
	float a = 1.0f;
	Renderer2D m_Renderer2D;
	Renderer2D m_Renderer2DEx;
	SoundManager m_SoundManager;
	MusicManager m_MusicManager;
	std::vector<TriDiObject> m_3DObjectArr;
	std::map<std::string, OBJModel*> m_ModelCache;
	Camera m_Cam;
	Light m_GlobalLight; 
	//sf::Shader m_AuxRender;
	//sf::Texture m_ScreenCap;
private:
	//Some Functions for internal use
	//sf::VideoMode videoModeChg();
	//void drawFPS();
	//void changeWinSize();
	//void checkForFullScreen();

private:
	//Variables for internal use
	//sf::Shader m_FpsDraw;
	//sf::Clock m_Clock;
	//sf::Time m_Fpstime;
	CGameState* m_State;
	CFrameLimiter* m_pFpsLimit;
	bool m_CarryFlag;
	LogFile m_LogFile;
	//Window stuff
	std::string m_ProgName;
	//sf::View m_cutView;
	//sf::RenderWindow* m_pWin;
	GLFWwindow*& m_pWin;
	//sf::VideoMode m_VideoMode;
	uint32_t m_WinStyle;
	uint32_t m_ChgDelay = 0;
	uint32_t m_currKind = 2; //Video mode kind: 360p, 480p, 720p, 1080p, 2160p
	bool m_isFullScreen;

	//Other system stuff
	//sf::Keyboard m_kbd;
};
