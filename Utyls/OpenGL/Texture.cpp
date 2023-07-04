#include "Texture.h"
#include "..\..\LogFile.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>

Texture::Texture() {

}

Texture::Texture(const std::string& init, bool pixelated) {
	this->loadFromFile(init, pixelated);
}

bool Texture::loadFromFile(const std::string& file, bool pixelated) {
	int hoge;
	stbi_set_flip_vertically_on_load(true);
	if (unsigned char* pPixels = stbi_load(file.c_str(), &this->m_Width, &this->m_Height, &hoge, 0)) {
		glGenTextures(1, &this->m_TexID);
		glBindTexture(GL_TEXTURE_2D, this->m_TexID);

		//Here i prefer pixelated stuff
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (pixelated) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		if (pPixels) {
			LogFile::writeLog("Texture::loadFromFile() > Loaded \"" + file + "\" succesfully!");
			//std::cout << "Texture::loadFromFile() > Loaded \"" << file << "\" succesfully.\n";
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(pPixels);
		}

		this->unbindTexture();
		return true;
	}
	return false;
	std::cout << "Texture::loadFromFile() > Error while loading \"" << file << "\".\n";
}