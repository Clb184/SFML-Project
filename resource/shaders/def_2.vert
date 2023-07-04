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
layout (location = 6) in float aLayer;
// Anchor...
layout (location = 7) in vec2 aAnchor;
//Color stuff
layout (location = 8) in vec4 aColor;

uniform mat4 camMat;
//uniform vec4 inColor;
uniform vec2 quad;
uniform vec2 quad2;
uniform float intime;

//uniform vec2 quadWH2;
//uniform vec2 scale;
//uniform vec2 movePos;
//uniform float dir;
//uniform int layer;

//For geom Shader
//out vec2 posXY;
//out vec2 texXY;
//out vec2 quadSize;
out float time;
out vec4 color;
out vec2 texCoord;
out vec2 texCoord2;
out float isBlur;
//out vec2 center;

void main()
{
	//center = vec2((aTex.x + aQuadWH.x * 0.5) / quadWH.x, (aTex.y + aQuadWH.y * 0.5) / quadWH.y);
	vec2 pos = aPos - vec2(aQuadWH.x * 0.5, aQuadWH.y * 0.5);
	pos.x *= aScale.x;
	pos.y *= aScale.y;
	float dist = sqrt(abs(pos.x) * abs(pos.x) + abs(pos.y) * abs(pos.y));
	float ang = atan(pos.y, pos.x) + aDir;
	pos = vec2(cos(ang) * dist, sin(ang) * dist);
	pos += aTranslate;
	//pos = vec2(pos.x / 640.0f, pos.y / 480.0f);
	//pos.y = 480.0f - pos.y;
	gl_Position = camMat * vec4(pos, aLayer, 1.0);
	//gl_Position.y = 480.0f - gl_Position.y;
	color = vec4(aColor.r / 255.0f, aColor.g / 255.0f, aColor.b / 255.0f, aColor.a / 255.0f);
	texCoord = vec2(aTex.x / quad.x, 1.0 - (aTex.y / quad.y));
	texCoord2 = quad;
	time = intime;
	isBlur = aAnchor.x;
	//texCoord = vec2(0.0, gl_Position.y);
	//color = vec4(1.0);	
}