#pragma once
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "Animation.h"
#include "FixedVector.h"
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

	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;

	int layer;
};

typedef struct VertexSpriteInfo {
	float x;
	float y;
	float u;
	float v;
	float tx;
	float ty;
	float qx;
	float qy;
	float sx;
	float sy;
	float dir;
	int layer;
};


class Renderer2D {
public:
	Renderer2D();
	Renderer2D(sf::RenderWindow*);
	~Renderer2D();
	void InitShader(std::string, std::string, std::string);

	//Draw Stuff
	void configureRenderer();
	void activateDraw(uint32_t);
	void deactivateDraw();
	void draw(int, int, const SpriteBatchInfo&);
	void draw(const std::vector<FixedVector< std::pair<uint32_t, SpriteBatchInfo>>>&);

	//Load Textures
	void LoadTextures(char*&);
	void LoadTextures(const std::list<std::string>&);
	void Initialize();
	void InitializeEx();

	//How many slots are loaded
	size_t getSlotCount() const;

	//Cleanup
	void cleanUp();
private:
	std::vector<sf::Texture> m_TexturesEx;//For menus and those things
	std::vector<sf::Texture> m_Textures; //For game usage
	AnimationSetup m_Anim;
	sf::Shader m_RenderShader;
	sf::RenderWindow* m_pWin;

	GLuint m_VAO;
	GLuint m_VBO;

	std::vector<GLfloat*> m_Triangles;
	GLuint* m_pIndices;
};