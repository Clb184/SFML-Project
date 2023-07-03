#include "Engine.h"
#include "CGameMain.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sysinfoapi.h>

//sf::RenderWindow* Game::m_pWin = nullptr;
//bool Game::m_isFullScreen = false; 
//sf::View Game::m_cutView;

std::string IntelMakeString() {
	std::string ret = "";
	int storage[4];
	char cputext[17] = { 0 };
	for (int i = 0; i < 3; i++) {
		int key = 0x80000002 + i;
		_asm {
			push eax
			mov eax, key
			cpuid
			mov storage[0], eax
			mov storage[4], ebx
			mov storage[8], ecx
			mov storage[12], edx
			pop eax
		}
		memcpy(&cputext[0], &storage[0], 16);
		ret += cputext;
	}
	return ret;

}

std::string retrieveCPUInfo() {
	std::string ret;
	int storage[4];
	char cputext[13] = { 0 };
	_asm {
		push eax
		mov eax, 0x00
		cpuid
		mov storage[0], ebx
		mov storage[4], edx
		mov storage[8], ecx
		pop eax
	}
	memcpy(&cputext[0], &storage[0], 12);
	ret = cputext;
	return ret;
}

Game::Game(GLFWwindow*& win, CFrameLimiter* fps) : m_pWin(win), m_Renderer2D(win), m_Renderer2DEx(win), m_pFpsLimit(fps) {
	/*
	std::string vertexSrc = "#version 330 core"

		"// Positions/Coordinates								  "
		"layout(location = 0) in vec2 aPos;						  "
		"// Texture Coordinates									  "
		"layout(location = 1) in vec3 aCol;						  "
		"														  "
		"uniform mat4 camMat;									  "
		"out vec4 color; "
		"														  "
		"void main()											  "
		"{														  "
		"	// Outputs the positions/coordinates of all vertices  "
		"	gl_Position = camMat * vec4(aPos, 0.0, 1.0);  "
		"														  "
		"	color = vec4(aCol, 1.0f);				  "
		"};														  ";
	std::string fragmentSrc = "#version 330 core"

		"// Outputs colors in RGBA								 "
		"out vec4 FragColor;									 "
																 
		"// Inputs the color from the Vertex Shader				 "
		"in vec4 color;											 "
		"														 "
		"void main()											 "
		"{														 "
		"	FragColor = color;				 "
		"};														 ";
	*/
	//this->m_WinStyle = sf::Style::Titlebar | sf::Style::Close;

	this->m_WinStyle = 0;//sf::Style::Titlebar | sf::Style::Close;

	//this->m_ProgName = "これは試練だ！";
	this->m_ProgName = "Uchuy Rikchay Engine";
	//this->m_VideoMode = ENGINE_WH_DEFAULT;
	this->m_isFullScreen = false;
	UpdateEngineWindow();
	//static ImGuiIO& io =
	this->m_CarryFlag = true;

	LogFile::Initialize("Engine.log");

	std::string GPUname = (const char*)glGetString(GL_RENDERER);
	unsigned long long RAMSize;
	GetPhysicallyInstalledSystemMemory(&RAMSize);
	double MemInGB = ((double)RAMSize / 1024.0) / 1024.0;
	LogFile::writeLog("Initializing...\n");
	LogFile::writeLog("====================================================");
	LogFile::writeLog("|                 CPU and GPU info                 |");
	LogFile::writeLog("====================================================");
	LogFile::writeLog("- CPU: " + IntelMakeString() + " (" + retrieveCPUInfo() + ")");
	LogFile::writeLog("- RAM installed: " + std::to_string(MemInGB) + " GBs ");
	LogFile::writeLog("- GPU: " + GPUname + "\n");
	LogFile::writeLog("====================================================");
	LogFile::writeLog("|                    System info                   |");
	LogFile::writeLog("====================================================");

	this->m_State = new CGameState(this);

	//logger << ("- OS: " + std::to_string(osver->dwMajorVersion) + "." + std::to_string(osver->dwMinorVersion) + "\n");
}


Game::~Game() {
	if (this->m_State) {
		delete this->m_State;
	}
}
/*
inline void Game::changeWinSize() {
	const bool add = m_kbd.isKeyPressed(m_kbd.Add);
	const bool sub = m_kbd.isKeyPressed(m_kbd.Subtract);
	if ((add || sub) && !this->m_ChgDelay) {
		this->m_currKind = (add) ? (++m_currKind) % 5 : ((sub) ? (--m_currKind) % 5 : m_currKind);
		this->m_VideoMode = videoModeChg();
		//this->m_pWin->setSize({ this->m_VideoMode.width, this->m_VideoMode.height });
		this->m_ChgDelay = 10;
		UpdateEngineWindow();
		m_pWin->setSize({ this->m_VideoMode.width, this->m_VideoMode.height });
	}
	else if (this->m_ChgDelay)
		this->m_ChgDelay--;
}*/
/*
inline void Game::checkForFullScreen() {
	if (const bool LAlt = this->m_kbd.isKeyPressed(this->m_kbd.LAlt)) {
		//if (!m_isFullScreen)
		//	this->changeWinSize();
		if (const bool Enter = this->m_kbd.isKeyPressed(this->m_kbd.Enter)) {
			if (!m_isFullScreen) {
				this->m_WinStyle = sf::Style::Fullscreen;
				//m_VideoMode = sf::VideoMode::getDesktopMode();
				//m_VideoMode = this->videoModeChg();
			}
			else {
				this->m_WinStyle = sf::Style::Titlebar | sf::Style::Close;
				//m_VideoMode = this->videoModeChg();
			}
			this->m_isFullScreen = !m_isFullScreen;
			UpdateEngineWindow();
		}
	}
}
*/

void Game::UpdateEngineWindow() {
	//m_pWin->pushGLStates();
	//sf::ContextSettings context;
	//context.depthBits = 24;
	//context.sRgbCapable = true;
	//context.antialiasingLevel = 0;
	//context.majorVersion = 3;

	//m_pWin->setActive(false);
	//m_pWin->create(m_VideoMode, this->m_ProgName + ENGINE_TITLE_CUSTOM, this->m_WinStyle, context);
	//m_pWin->setFramerateLimit(60);

	//m_pWin->setActive(true);

	if (!glfwInit()) {
		std::cout << "Failed initializing GLFW";
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->m_pWin = glfwCreateWindow(800, 600, this->m_ProgName.c_str(), NULL, NULL);
	//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//glfwSetWindowMonitor(this->m_pWin, glfwGetPrimaryMonitor(), 0, 0, 800, 600, 60);

	glfwMakeContextCurrent(this->m_pWin);

	//glfwSwapInterval(1);
	glewExperimental = TRUE;
	if (glewInit() == GLEW_OK)
		std::cout << "GLEW started...\n";

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	//glEnable(GL_ALPHA_TEST);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
	}
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glViewport(0, 0, 800, 600);
	glClearDepth(1.0f);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
	}
}

uint32_t Game::UpdateLogic() {
	static bool play = false;
	static int count = 0;
	
	if (!(this->m_Time % 200) && this->m_Time > 4 * 60) {
		this->m_SoundManager.playSound(4);
		count = 0;
		play = true;
	} 
	if (play && !(this->m_Time % 5)) {
		r = float(rand() % 256) / 255.0f;
		g = float(rand() % 256) / 255.0f;
		b = float(rand() % 256) / 255.0f;
		//glClearColor(, rand() % 256, rand() % 256, 255);
		//glClear(GL_COLOR_BUFFER_BIT);
	}
	count++;
	if (!this->m_SoundManager.isAllPlaying(4) && !this->m_SoundManager.isAllPlaying(3) && play) {
		//std::cout << "Count: " << count << "\n";
		this->m_SoundManager.playSound(3);
		play = false;
		if (r > 0.5f)
			this->m_SoundManager.playSound(6);
	}
	uint32_t retCode = 1;
		
		retCode = m_State->updateLogic(); 
		if (m_Time > 0 && !(m_Time % 60))
			std::cout << "FPS: " << this->m_pFpsLimit->getFPS() << " @ " << this->m_Time << "\n";
		if(!this->m_State->m_pGame->IsPaused())
			this->m_Time++;
		this->m_CarryFlag = !(retCode == 2 || retCode == 3);
		if (!this->m_CarryFlag)
			this->m_Time = 0;
	return retCode;
}

void Game::UpdateDraw() {
	if (this->m_CarryFlag) {
		this->m_State->m_pGame->updateDraw(m_pWin);
	}
	else {
		this->m_CarryFlag = true;
	}
	
	//glfwSwapBuffers(this->m_pWin);
		//sf::sleep(sf::milliseconds(10));
	//this->drawFPS();
	//this->m_pWin->display();
}

//void Game::changeVideoMode() 
/*
sf::VideoMode Game::videoModeChg() {
	sf::VideoMode ret;
	switch (this->m_currKind) {
		case VIDEO_360:
			ret = sf::VideoMode(320, 240);
			break;
		case VIDEO_480:
			ret = sf::VideoMode(640, 480);
			break;
		case VIDEO_720:
			ret = sf::VideoMode(800, 600);
			break;
		case VIDEO_1080:
			ret = sf::VideoMode(1280, 960);
			break;
		case VIDEO_2160:
			ret = sf::VideoMode(2560, 1920);
			break;
	}
	//this->m_pWin->setSize({ ret.width, ret.height });
	return sf::VideoMode(640, 480);
}*/
/*
void Game::drawFPS() {
	
	//m_pWin->setActive(true);
	glm::mat4 Model(1.0);
	glm::mat4 Proj(1.0);
	Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, 0.0f));
	Proj = glm::ortho(0.0f, 1280.0f / 1.5f, 480.0f, 0.0f, -1.0f, 0.0f);
	sf::Shader::bind(&this->m_FpsDraw);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, this->m_Quad);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, this->m_Quad + 2);
	glEnableVertexAttribArray(1);
	m_FpsDraw.setUniform("model", sf::Glsl::Mat4(glm::value_ptr(Model)));
	m_FpsDraw.setUniform("camMat", sf::Glsl::Mat4(glm::value_ptr(Proj)));

	//sf::Texture::bind(&m_Text.getTexture());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//m_pWin->setActive(false);
}*/