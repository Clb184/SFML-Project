#pragma once
//#include <SFML/Graphics.hpp>
#include "Shader.h"
#include "Animation.h"
#include "OpenGLObject.h"
//#include "..\System\FixedVector.h"
#include <list>


/*
2023/05/05? - Started 

2023/05/08 - Going back to batch rendering
*/

//2D sprite stuff
typedef struct SpriteBatchInfo{
	GLfloat x;
	GLfloat y;

	GLfloat ou;
	GLfloat ov;

	GLfloat sx;
	GLfloat sy;
	GLfloat dir;

	int ah;
	int av;
	int r;
	int g;
	int b;
	int a;

	int layer;
	int texslot;
	int quadid;
	int order;
	//int pad[15];
};

typedef struct VertexSpriteInfo {
	GLfloat x;
	GLfloat y;
	GLfloat u;
	GLfloat v;
	GLfloat tx;
	GLfloat ty;
	GLfloat qx;
	GLfloat qy;
	GLfloat sx;
	GLfloat sy;
	GLfloat dir;
	GLfloat layer;
	GLfloat ah;
	GLfloat av;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
	constexpr bool operator==(const VertexSpriteInfo&);
};

struct OpenGLDrawInfo {
	OpenGLObj obj;
	VertexSpriteInfo* pTriangles;
	GLuint* pIndices;
};

struct Sprite {
	OpenGLObj obj;
	VertexSpriteInfo triangles[4] = {0};
	GLuint indices[6] = { 0, 1, 3, 1, 3, 2 };
};
typedef std::map<int, std::list<SpriteBatchInfo>> LayeredSpritebatch;

class Renderer2D {
public:
	Renderer2D();
	Renderer2D(GLFWwindow*);
	~Renderer2D();

	//Draw Stuff
	void InitShader(std::string, std::string);
	void configureRenderer();
	//void draw(std::map<int, std::vector<SpriteBatchInfo>>&, uint32_t);
	void draw(LayeredSpritebatch&, uint32_t);
	void drawEx(TextureBase&, uint32_t, const SpriteBatchInfo&);

	//Load Textures
	//void LoadTextures(char*&);
	void LoadTextures(const std::vector<std::string>&);
	void Initialize();

	//How many slots are loaded
	size_t getSlotCount() const;

	//Cleanup
	void cleanUp();
private:

private:
	//std::vector<Texture> m_TexturesEx;//For menus and those things
	std::vector<Texture> m_Textures; //For game usage
	AnimationSetup m_Anim;
	//sf::Shader m_RenderShader;
	//sf::RenderWindow* m_pWin;
	GLFWwindow* m_pWin;
	//sf::RenderTexture m_RenderTexture;
	Shader m_RenderShader;
	//A sprite, not inteded for all the uses
	Sprite m_AuxSprite;
	//std::vector<VertexSpriteInfo*> m_Triangles;
	VertexSpriteInfo* m_pTriangles;
	GLuint* m_pIndices;
	OpenGLObj m_GLObject;
	//std::vector<OpenGLDrawInfo> m_VertexObjects;
};