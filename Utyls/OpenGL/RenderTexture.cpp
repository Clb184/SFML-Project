#include "RenderTexture.h"
#include <iostream>

RenderTexture::RenderTexture() {
	this->m_Framebuffer = 0;
	this->m_Renderbuffer = 0;
}

RenderTexture::~RenderTexture() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (this->m_Framebuffer)
		glDeleteFramebuffers(1, &this->m_Framebuffer);
}


void RenderTexture::createRenderTexture(glm::vec2 wh) {
	glGenFramebuffers(1, &this->m_Framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_Framebuffer);
	glGenTextures(1, &this->m_TexID);
	glBindTexture(GL_TEXTURE_2D, this->m_TexID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wh.x, wh.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	this->unbindTexture();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_TexID, 0);
	glGenRenderbuffers(1, &this->m_Renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, this->m_Renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, wh.x, wh.y); 
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->m_Renderbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	this->m_Width = wh.x;
	this->m_Height = wh.y;

	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
	}
}

void RenderTexture::clear() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void RenderTexture::bindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_Framebuffer);
}

void RenderTexture::unbindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
