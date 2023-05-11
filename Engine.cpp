#include "Engine.h"
#include "CGameMain.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>

//sf::RenderWindow* Game::m_pWin = nullptr;
//bool Game::m_isFullScreen = false; 
//sf::View Game::m_cutView;

Game::Game(sf::RenderWindow* win) : m_pWin(win), m_Renderer2D(win) {
	std::string vertexSrc = "#version 330 core"

		"// Positions/Coordinates								  "
		"layout(location = 0) in vec2 aPos;						  "
		"// Texture Coordinates									  "
		"layout(location = 1) in vec2 aTex;						  "
		"														  "
		"// Outputs the texture coordinates to the fragment shader"
		"out vec2 texCoord;										  "
		"														  "
		"uniform mat4 model;									  "
		"uniform mat4 camMat;									  "
		"														  "
		"void main()											  "
		"{														  "
		"	// Outputs the positions/coordinates of all vertices  "
		"	vec3 tempPos = vec3(aPos, 0.0);						  "
		"	vec3 curPos = vec4(model * vec4(tempPos, 1.0)).xyz;	  "
		"	//gl_Position = camMat * vec4(curPos, 1.0);			  "
		"	gl_Position = camMat * model * vec4(aPos, 0.0, 1.0);  "
		"														  "
		"	texCoord.xy = vec2(aTex.x, aTex.y);					  "
		"};														  ";
	std::string fragmentSrc = "#version 330 core"

		"// Outputs colors in RGBA								 "
		"out vec4 FragColor;									 "
																 
		"// Inputs the color from the Vertex Shader				 "
		"in vec4 color;											 "
		"														 "
		"// Inputs the texture coordinates from the Vertex Shader"
		"in vec2 texCoord;										 "
		"														 "
		"// Gets the Texture Unit from the main function		 "
		"uniform sampler2D tex0;								 "
		"														 "
		"void main()											 "
		"{														 "
		"	FragColor = texture(tex0, texCoord);				 "
		"	FragColor = vec4(1.0);				 "
		"};														 ";

	//m_pWin = win;
	this->m_FpsDraw.loadFromMemory(vertexSrc, fragmentSrc);
	this->m_WinStyle = sf::Style::Titlebar | sf::Style::Close;

	//this->m_Quad[4] = this->m_Quad[8] = m_Text.getSize().x;
	//this->m_Quad[9] = this->m_Quad[13] = m_Text.getSize().y;
	this->m_ProgName = "Uchuy Rikchay Engine";
	this->m_VideoMode = ENGINE_WH_DEFAULT;
	this->m_isFullScreen = false;
	UpdateEngineWindow();
	this->m_State = new CGameState(this);
	this->m_Renderer2D.InitShader("def_2.vert", "def_2.geom", "def_2.frag");
}

Game::~Game() {
	if (this->m_State) {
		delete this->m_State;
	}
	//m_State.~CGameState();
}

inline void Game::changeWinSize() {
	const bool add = m_kbd.isKeyPressed(m_kbd.Add);
	const bool sub = m_kbd.isKeyPressed(m_kbd.Subtract);
	if ((add || sub) && !this->m_ChgDelay) {
		this->m_currKind = (add) ? (++m_currKind) % 5 : ((sub) ? (--m_currKind) % 5 : m_currKind);
		this->m_VideoMode = videoModeChg();
		//this->m_pWin->setSize({ this->m_VideoMode.width, this->m_VideoMode.height });
		this->m_ChgDelay = 10;
		UpdateEngineWindow();
	}
	else if (this->m_ChgDelay)
		this->m_ChgDelay--;
}

inline void Game::checkForFullScreen() {
	if (const bool LAlt = this->m_kbd.isKeyPressed(this->m_kbd.LAlt)) {
		if (!m_isFullScreen)
			this->changeWinSize();
		if (const bool Enter = this->m_kbd.isKeyPressed(this->m_kbd.Enter)) {
			if (!m_isFullScreen) {
				this->m_WinStyle = sf::Style::Fullscreen;
				m_VideoMode = sf::VideoMode::getDesktopMode();
			}
			else {
				this->m_WinStyle = sf::Style::Titlebar | sf::Style::Close;
				m_VideoMode = this->videoModeChg();
			}
			m_isFullScreen = !m_isFullScreen;
			UpdateEngineWindow();
		}
	}
}

void Game::UpdateEngineWindow() {
	//m_pWin->pushGLStates();
	sf::ContextSettings context;
	context.depthBits = 24;
	context.sRgbCapable = true;
	context.antialiasingLevel = 16;
	context.majorVersion = 4;
	context.minorVersion = 4;

	m_pWin->setActive(false);
	m_pWin->create(m_VideoMode, this->m_ProgName + ENGINE_TITLE_CUSTOM, this->m_WinStyle, context);
	//m_ScreenCap.create(m_VideoMode.width, m_VideoMode.height);
	//m_cutView.setCenter((1280.0f / 1.5f) / 2, 240.0f);
	//m_cutView.setSize(1280.0f / 1.5f, 480.0f);
	//m_pWin->setView(m_cutView);
	m_pWin->setFramerateLimit(60);
	//m_pWin->popGLStates();
	m_pWin->setActive(true);
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK)
		std::cout << "GLEW started...\n";
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_FOG);

	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDepthMask(GL_TRUE);
	glDisable(GL_LIGHTING);
	glViewport(0, 0, m_pWin->getSize().x, m_pWin->getSize().y);
	glClearDepth(1.0f);
	//m_pWin->setActive(false);
}

uint32_t Game::UpdateLogic() {

	uint32_t retCode = 1;
	float fps;
	if (m_pWin->hasFocus()) {
		this->checkForFullScreen();
		m_Fpstime = m_Clock.getElapsedTime();
		fps = 1.0 / m_Fpstime.asSeconds();
		m_Clock.restart().asSeconds();
		retCode = m_State->updateLogic();
		sf::sleep(sf::milliseconds(10));
		//Sleep(10);
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		if (m_Time > 0 && !(m_Time % 60))
			std::cout << "FPS: " << fps << " @ " << this->m_Time << "\n";
		m_Time++;
	}
	else {
		//m_pWin->draw(sf::Sprite(this->m_ScreenCap));
	}
	return retCode;
}

void Game::UpdateDraw() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	m_State->m_pGame->updateDraw(m_pWin);
	//this->drawFPS();
}

//void Game::changeVideoMode() 

sf::VideoMode Game::videoModeChg() {
	sf::VideoMode ret;
	switch (this->m_currKind) {
		case VIDEO_360:
			ret = sf::VideoMode(640, 360);
			break;
		case VIDEO_480:
			ret = sf::VideoMode(853.3, 480);
			break;
		case VIDEO_720:
			ret = sf::VideoMode(1280, 720);
			break;
		case VIDEO_1080:
			ret = sf::VideoMode(1920, 1080);
			break;
		case VIDEO_2160:
			ret = sf::VideoMode(3840, 2160);
			break;
	}
	return ret;
}

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
}