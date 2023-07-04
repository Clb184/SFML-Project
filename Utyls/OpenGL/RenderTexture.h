#pragma once
#include "TextureBase.h"

class RenderTexture : public TextureBase {
public:
	RenderTexture();
	~RenderTexture();
	void createRenderTexture(glm::vec2);
	void clear();
	void bindFrameBuffer();
	void unbindFrameBuffer();
private:
	GLuint m_Framebuffer;
	GLuint m_Renderbuffer;
};