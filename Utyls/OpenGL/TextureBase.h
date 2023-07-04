#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm/gtc/type_ptr.hpp>

//class Texture;

class TextureBase {
public:
	TextureBase();
	//Bind and unbind;
	virtual void bindTexture();
	bool setTextureSlot(int);
	void unbindTexture();

	glm::vec2 getSize();
	//Image config
	//void mipmapCreate();

	//In case wanna create placeholders or so...
	void createEmptyTexture();
	friend class Texture;
	friend class RenderTexture;
private:
	GLuint m_TexID;
	int m_Width;
	int m_Height;
};