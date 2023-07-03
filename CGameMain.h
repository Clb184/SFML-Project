#pragma once
//#include <GL/glew.h>
//#include <SFML/Audio.hpp>

//#include "CGameState.h"
//#include "Utyls\OpenGL\Animation.h"
#include "Utyls\OpenGL\Renderer2D.h"
#include "Utyls\OpenGL\RenderTexture.h"
#include "Enemy.h"
#include "Music.h"

#include "ScriptBase.h"
//#include "CBullet.h"

//class Game;

//#include "CScene.h"
//#include "CWindowSys.h"
//#include "script_test.h"

//extern class CGameState;

#define GFLAG_GAME		0x00000001
#define GFLAG_SHOWUI	0x00000002
#define GFLAG_REPLAY	0x00010000

struct GameGlobals {
	//Script stuff
	int currentScriptId = 0;
	int expectedScriptId = 0;

	//Player stuff
	int playerShot = 0;
	uint32_t lives = 0;
	uint32_t bombs = 0;
	float player_X = 0.0f;
	float player_Y = 0.0f;

	//General purpose registers...
	int GGRI[16];
	float GGRF[16];

	//For future usage...
	float cam_x = 0.0f;
	float cam_y = -7.0f;
	float cam_z = -5.0f;
	float cam_fov = RAD(90.0f);

	//Score stuff
	uint64_t score = 0;
	uint64_t highscore = 0;

	//Day month stuff...
	uint32_t day;
	uint32_t month;
	uint32_t year;
	uint32_t hour;
	uint32_t minute;
	uint32_t second;

	//Misc
	float screenRot = 0.0f;
	float screenX = (1280.0f / 1.5f) / 2.0f;
	float screenY = 240.0f;
	float screenSx = 1.0f;
	float screenSy = 1.0f;
};

typedef enum {
	SECTION_UNKNOWN = -1,
	SECTION_MUSIC = 0,
	SECTION_SOUND,
	SECTION_QUAD,
	SECTION_SHADER2D,
	SECTION_3DMODEL,
	SECTION_SHADER3D,
}SECTION_KIND;

typedef struct {
	SECTION_KIND sectionKind;
	std::vector<int> stringIDs;
	std::vector<Music> musicIDs;
	std::vector<std::pair<int, int>> shaderIDs;
	std::pair<std::string, std::string> shaderBase;
} ScriptSection;

typedef enum {
	RESUME = 1,
	TITLE
} PauseOptions2;
/*
class CPauseMenu : public CMenu {
public:
	CPauseMenu() {}
	uint32_t updateLogic();
};
*/
class CGameMain {
public:
	bool initScene(std::string);
	char* initScript(std::string);
	uint32_t updateLogic();
	void updateDraw(GLFWwindow*);
	bool cleanUp();
	bool IsPaused() const;

	CGameMain(Game*);
	~CGameMain();
private:
	void loadResources(char*&);
	ScriptSection __getSection(char*&);
	void __getAllStrings(char*&);
	std::vector<std::string> __getStringList(std::vector<int>); 
	std::vector<std::pair<std::string, std::string>> __getStringList(std::vector<std::pair<int, int>>);
private:
	//Script itself and flags
	bool m_IsPaused = false;
	uint32_t m_Flags = 0;
	char* m_File = nullptr;
	char* m_File2 = nullptr;
	//CPauseMenu* m_PauseMenu = nullptr; 

	//Graphic stuff
	RenderTexture m_RenderTex;
	/*
	sf::Vertex m_tlv[4];
	sf::RenderTexture* m_RenderTex = nullptr;
	sf::RenderStates m_RenderState;
	sf::Transform m_Transform;
	void* m_pBaseProgram = nullptr;*/
public:
	GameGlobals m_GlobalVars;
	
	EnemyManager m_EnmMan;
	EnemyManager m_EnmManEx;

	std::vector<std::string> m_StrContainer;

	Game* m_pGame;
	uint32_t m_Time;
};

template<typename T, typename ...args>
void render3D(const T& func, args... param) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	func(param...);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
	//glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE);
	//glBlendFuncSeparate();
}
