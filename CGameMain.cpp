#include "Engine.h"
//#include "SFML\System\Time.hpp"
#include "CGameMain.h"
#include "ScriptBase.h"
#include "Commons.h"
#include "LogFile.h"
#include <SFML\Window\Keyboard.hpp>

enum {
	GAME_CONTINUE = -1,
	GAME_EXIT,
	GAME_RESUME,
	GAME_RELOAD,
	GAME_CHANGE_SCRIPT
}GameState3;

CGameMain::CGameMain(Game* pGame) : 
	m_EnmMan(this, &pGame->m_Renderer2D, pGame),
	m_EnmManEx(this, &pGame->m_Renderer2DEx, pGame), 
	m_pGame(pGame) {

}


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
	//if(!m_PauseMenu) m_PauseMenu = new CPauseMenu();
	//std::vector<std::string> pauseMenu{
	//	"Resume",
	//	"Title"
	//};
	//m_PauseMenu->initMenu(320 - 64,240 - (1.5 * 24), 128, 2, 24, "Pause Menu", { 20, 30, 40, 128 }, pauseMenu);
	this->m_pGame->m_Cam.setRatio(800.0f / 600.0f);
	this->m_RenderTex.createRenderTexture({800, 600});
	char* temp = this->initScript(script);
	this->m_File = temp;
	//this->m_MusicMan.Initialize(temp);
	//m_Anim.Initialize(temp);
	this->loadResources(temp);
	//this->m_pGame->m_Renderer2D.LoadTextures(temp);
	//this->m_pGame->m_Renderer2D.Initialize();
	//this->m_pGame->m_Renderer2D.configureRenderer();
	this->m_EnmMan.initialize(temp);
	//
	//temp = this->m_File2;
	//this->m_pGame->m_Renderer2DEx.LoadTextures(temp);
	//this->m_pGame->m_Renderer2DEx.Initialize();
	//this->m_pGame->m_Renderer2DEx.configureRenderer();
	//this->m_EnmManEx.initialize(temp);
	//
	//this->m_File2 = this->m_File;
	
	
	
	
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

	this->m_GlobalVars.player_X = 400.0f;
	this->m_GlobalVars.player_Y = 240.0f;

	this->m_Time = 0;
	//uint32_t test2 = 2;
	//a = 40.0;
	//inttest = int(float(a));
	//glDepthMask(GL_FALSE);
	return true;
}

char* CGameMain::initScript(std::string script) {
	FILE* fp;
	if (fp = fopen(script.c_str(), "rb")) {
			fseek(fp, 0, SEEK_END);
			size_t size = ftell(fp);
			m_File = (char*)std::malloc(size);
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
	uint32_t code = -1;
	static sf::Keyboard kbd;
	const float speed = 0.25;
	this->m_GlobalVars.cam_x += (kbd.isKeyPressed(kbd.D)) ? speed : (kbd.isKeyPressed(kbd.A)) ? -speed : 0.0;
	this->m_GlobalVars.cam_z -= (kbd.isKeyPressed(kbd.W)) ? speed : (kbd.isKeyPressed(kbd.S)) ? -speed : 0.0;
	if(kbd.isKeyPressed(kbd.Space))
	this->m_GlobalVars.cam_y += (kbd.isKeyPressed(kbd.LShift)) ? -speed : speed;

	if (kbd.isKeyPressed(kbd.LAlt) && kbd.isKeyPressed(kbd.F5))
		return ReturnCodeEnm::ERET_RELOAD;

	this->m_pGame->m_Cam.move({ this->m_GlobalVars.cam_x, this->m_GlobalVars.cam_y, this->m_GlobalVars.cam_z });
	if (!this->m_IsPaused) {
		if (kbd.isKeyPressed(sf::Keyboard::Escape)) {
			this->m_IsPaused = true;
			Sleep(300);
			//m_Music.pause();
		}
		code = this->m_EnmMan.updateLogic();
		
	}
	else {
		if (kbd.isKeyPressed(sf::Keyboard::Escape)) {
			this->m_IsPaused = false;
			Sleep(300);
		}
		//code = this->m_EnmManEx.updateLogic();//m_PauseMenu->updateLogic(); 
		//if (kbd.isKeyPressed(sf::Keyboard::Escape)) {
		//	this->m_IsPaused = false;
		//	//m_Music.pause();
		//}
	}
	if(!this->m_IsPaused)
		this->m_Time++;

	return code;
}

bool CGameMain::IsPaused() const {
	return this->m_IsPaused;
}

void CGameMain::updateDraw(GLFWwindow* target) {
	const float rot = this->m_GlobalVars.screenRot;
	const float scrx = this->m_GlobalVars.screenX;
	const float scry = this->m_GlobalVars.screenY;
	const float scrsx = this->m_GlobalVars.screenSx;
	const float scrsy = this->m_GlobalVars.screenSy;
	//00 00 00 00 00 00 00 00 90 01 00 00
	static Texture tex("resource/assd/paru_title.png", false);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int size = this->m_pGame->m_3DObjectArr.size();
	glEnable(GL_DEPTH_TEST);
	for (int i = 0; i < size; i++) {
		this->m_pGame->m_3DObjectArr[i].draw(this->m_pGame->m_Cam, this->m_pGame->m_GlobalLight, this->m_Time);
	}
	this->m_RenderTex.bindFrameBuffer();
	this->m_RenderTex.clear();
	if (!this->m_IsPaused) {
		//m_EnmMan.updateDraw( target);
	}
	else {
		//m_EnmMan.updateDraw(target);
		//this->m_PauseMenu->updateDraw(target);
		
	}
	this->m_EnmMan.updateDraw(target);
	this->m_RenderTex.unbindFrameBuffer();
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	this->m_pGame->m_Renderer2D.drawEx(this->m_RenderTex, this->m_Time,
		{
			400.0, 300.0, 
			0.0, 0.0, 
			(float)cos(this->m_Time * 0.01) * 0.0f + 1.0f, 1.0, 
			(float)((this->m_Time * PI * 0.2) / 180.0) * 0.0f,
			1, 0, 
			255, 
			255, 
			255, 
			255,
			10
		});
	/*
	int asize = this->m_pGame->m_3DObjectArr[0].TriDiModel[0].m_ModelVertex.size();
	for (int i = 0; i < asize; i++) {
		this->m_pGame->m_Renderer2D.drawEx(this->m_pGame->m_3DObjectArr[0].TriDiModel[0].m_ModelVertex[0].tex, this->m_Time,
			{
				400.0, 300.0,
				0.0, 0.0,
				(float)cos(this->m_Time * 0.01) * 0.0f + 1.0f, -1.0,
				(float)((this->m_Time * PI * 0.2) / 180.0) * 0.0f,
				1, 0,
				255,
				255,
				255,
				256,
				20
			});
	}*/
}

bool CGameMain::cleanUp() {
	//if (m_Music.getStatus() != m_Music.Stopped)
	//	m_Music.stop();
	
	//m_Music.~Music();
	this->m_pGame->m_Renderer2D.cleanUp();
	this->m_pGame->m_Renderer2DEx.cleanUp();
	this->m_pGame->m_MusicManager.cleanUp();
	this->m_pGame->m_SoundManager.cleanUp();
	this->m_pGame->m_3DObjectArr.clear();
	for (auto& i: this->m_pGame->m_ModelCache) {
		delete i.second;
	}
	this->m_pGame->m_ModelCache.clear();
	this->m_EnmMan.cleanUp();
	this->m_EnmManEx.cleanUp();
	if (this->m_File)
		free(this->m_File);
	//if (this->m_RenderTex)
		//delete[] this->m_RenderTex;
	//if (m_DrawTex)
		//delete[] m_DrawTex;
	return true;
}
/*
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
}*/

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

void CGameMain::loadResources(char*& pfile) {
	this->__getAllStrings(pfile);
	ScriptSection Section;
	std::vector<std::string> StringList;
	std::vector<std::pair<std::string, std::string>> StringListEx;
	std::pair<std::string, std::string> StringPair;
	Shader _3DShader;
	while (*pfile) {
		Section = this->__getSection(pfile);
		switch (Section.sectionKind) {
		case SECTION_KIND::SECTION_MUSIC:
			this->m_pGame->m_MusicManager.Initialize(Section.musicIDs);
			break;
		case SECTION_KIND::SECTION_SOUND:
			StringList = this->__getStringList(Section.stringIDs);
			this->m_pGame->m_SoundManager.Initialize(StringList);
			break;
		case SECTION_KIND::SECTION_QUAD:
			StringList = this->__getStringList(Section.stringIDs);
			this->m_pGame->m_Renderer2D.LoadTextures(StringList);
			this->m_pGame->m_Renderer2D.Initialize();
			this->m_pGame->m_Renderer2D.configureRenderer();
			break;
		case SECTION_KIND::SECTION_SHADER2D:
			StringListEx = this->__getStringList(Section.shaderIDs);
			this->m_pGame->m_Renderer2D.InitShader(Section.shaderBase.first, Section.shaderBase.second);
			//this->m_pGame->m_Renderer2DEx.InitShader("def_2.vert", "def_2.frag");
			break;
		case SECTION_KIND::SECTION_3DMODEL: {
			StringList = this->__getStringList(Section.stringIDs);
			int size = StringList.size();
			this->m_pGame->m_3DObjectArr.reserve(size);
			for (int i = 0; i < size; i++) {
				this->m_pGame->m_3DObjectArr.push_back(TriDiObject());
				this->m_pGame->m_3DObjectArr[i].loadModel(StringList[i], this->m_pGame->m_ModelCache);
				this->m_pGame->m_3DObjectArr[i].setShader().loadFromFile(StringPair.first, StringPair.second);
			}
		}break;
		case SECTION_KIND::SECTION_SHADER3D:
			StringListEx = this->__getStringList(Section.shaderIDs);
			StringPair = { Section.shaderBase.first, Section.shaderBase.second };
			break;
		}
	}
	++pfile;
}


ScriptSection CGameMain::__getSection(char*& pfile) {
	constexpr uint32_t sections[]{
		MakeCStr('m', 'u', 's', 'c'),
		MakeCStr('s', 'n', 'd', 'm'),
		MakeCStr('q', 'u', 'a', 'd'),
		MakeCStr('s', 'h', '2', 'd'),
		MakeCStr('m', '3', 'd', 'l'),
		MakeCStr('s', 'h', '3', 'd'),
	};
	uint32_t temp[2] = { 0, 0}; //Sign and size
	SECTION_KIND sec = SECTION_KIND::SECTION_UNKNOWN;
	std::vector<int> idcont;
	std::vector<Music> musiccont;
	std::vector<std::pair<int, int>> shadercont; 
	std::pair<std::string, std::string> shadersing;
	uint32_t* ids = nullptr;

	memcpy(temp, pfile, sizeof(temp));
	pfile += sizeof(temp);
	for (int i = 0; i <= SECTION_KIND::SECTION_SHADER3D; i++) {
		if (temp[0] == sections[i]) {
			sec = (SECTION_KIND)i;
			break;
		}
	}
	switch(sec){
		case SECTION_KIND::SECTION_MUSIC:
			ids = (uint32_t*)malloc((sizeof(uint32_t) + 2 * sizeof(uint64_t)) * temp[1]);
			memcpy(ids, pfile, (sizeof(uint32_t) + 2 * sizeof(uint64_t)) * temp[1]);
			pfile += (sizeof(uint32_t) + 2 * sizeof(uint64_t)) * temp[1];
			for (int i = 0; i < temp[1]; i++) {
				Music temp;
				temp.loopStart = makeInt64(ids[i * 5 + 1], ids[i * 5 + 2]);
				temp.loopEnd = makeInt64(ids[i * 5 + 3], ids[i * 5 + 4]);
				temp.FileName = this->m_StrContainer[ids[i]];
				musiccont.push_back(temp);
			}
			break;
		case SECTION_KIND::SECTION_SHADER2D:
		case SECTION_KIND::SECTION_SHADER3D:
			shadersing = {this->m_StrContainer[temp[1]], this->m_StrContainer[pfile[0]]};
			pfile += 1 * sizeof(uint32_t);
			break;
		default:
			ids = (uint32_t*)malloc(sizeof(uint32_t) * temp[1]);
			memcpy(ids, pfile, sizeof(uint32_t) * temp[1]);
			pfile += sizeof(uint32_t) * temp[1];
			for (int i = 0; i < temp[1]; i++) {
				idcont.push_back(ids[i]);
			}
			break;
	}
	if (ids)
		free(ids);
	return { sec, idcont, musiccont, shadercont, shadersing };
}

void CGameMain::__getAllStrings(char*& pfile) {
	bool cont = true;
	std::string hoge = "";
	while (*pfile) {
		hoge.push_back(*pfile);
		if (*++pfile == 0x00) {
			this->m_StrContainer.push_back(hoge);
			hoge = "";
			pfile++;
		}
	}
	++pfile;
}

std::vector<std::string> CGameMain::__getStringList(std::vector<int> str_ids) {
	std::vector<std::string> ret = {};
	for (auto& a : str_ids) {
		ret.push_back(this->m_StrContainer[a]);
	}
	return ret;
}

std::vector<std::pair<std::string, std::string>> CGameMain::__getStringList(std::vector<std::pair<int, int>> str_pairs) {
	std::vector<std::pair<std::string, std::string>> ret = {};
	for (auto& a : str_pairs) {
		ret.push_back({ this->m_StrContainer[a.first], this->m_StrContainer[a.second] });
	}
	return ret;
}