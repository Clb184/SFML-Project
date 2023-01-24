#pragma once
#include "script.h"
#include "Engine.h"

typedef struct {
	uint32_t startTxt;
	uint32_t startSnd;
	uint32_t startTex;
	uint32_t startAnm;
	uint32_t startScpt;
	std::string* Text;
	std::string* Sound;
	std::string* Texture;
	uint32_t* Animation;
	uint32_t* Text;
} ScriptFileHeader;


/*
"This is a string for text", "Another one too", "And another one";
"sound0.wav", "sound5.ogg", "sound8.wav";
"image.jpg", "another.png", "test.bmp";
//Animation code







*/