#version 330 core

// Position
layout (location = 0) in vec2 aPos;
// Texture coordinates
layout (location = 1) in vec2 aTex;
// Translate
layout (location = 2) in vec2 aTranslate;
// Quad width, height
layout (location = 3) in vec2 aQuadWH;
// Scale
layout (location = 4) in vec2 aScale;
// Direction of sprite
layout (location = 5) in float aDir;
// Draw order bottom >>>> top
layout (location = 6) in int aLayer;

uniform mat4 camMat;
uniform vec4 inColor;
uniform vec2 quadWH;

//uniform vec2 quadWH2;
//uniform vec2 scale;
//uniform vec2 movePos;
//uniform float dir;
//uniform int layer;

//For geom Shader
//out vec2 posXY;
//out vec2 texXY;
//out vec2 quadSize;

out vec4 color;
out vec2 texCoord;

void main()
{
	vec2 pos = aPos - vec2(aQuadWH.x / 2.0, aQuadWH.y / 2.0);
	pos.x *= aScale.x;
	pos.y *= aScale.y;
	float dist = sqrt(abs(pos.x) * abs(pos.x) + abs(pos.y) * abs(pos.y));
	float ang = atan(pos.y, pos.x) + aDir;
	pos = vec2(cos(ang) * dist, sin(ang) * dist);
	pos += aTranslate;

	gl_Position = camMat * vec4(pos, aLayer * 0.01, 1.0);
	color = inColor;
	texCoord = vec2(aTex.x / quadWH.x, aTex.y / quadWH.y);
}