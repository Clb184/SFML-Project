#pragma once
#include "TextureBase.h"

class Texture : public TextureBase {
public:
	//Constructor
	Texture();
	Texture(const std::string&, bool);

	//Input output stuff
	bool loadFromFile(const std::string&, bool);
private:
};