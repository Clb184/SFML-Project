#include "TextureBase.h"
#include <iostream>
TextureBase::TextureBase() {
	this->m_Width = 0;
	this->m_Height = 0;
	this->m_TexID = 0;
}


void TextureBase::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->m_TexID);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
	}
}

bool TextureBase::setTextureSlot(int slot) {
	if (slot < 32 || slot < 0) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, this->m_TexID);
		return true;
	}
	return false;
}

void TextureBase::unbindTexture() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 TextureBase::getSize() {
	return { this->m_Width, this->m_Height };
}