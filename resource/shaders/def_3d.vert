#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec4 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;
// Texture Coordinates
layout (location = 3) in vec3 aNormals;


// Outputs the color for the Fragment Shader
out vec4 color;
out vec3 curPos;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;
out vec3 normVec;

// Controls the scale of the vertices
uniform float scale;

uniform float time;

//uniform vec2 wh;
//uniform sampler2D tex0;
//uniform sampler2D tex2;
// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model;
//uniform mat4 view;
//uniform mat4 proj;
uniform mat4 camMat;
uniform mat3 normMat;

out float visib;

const float density = 0.002;
const float grad = 1.0;

void main()
{
	vec3 tempPos = aPos;
	//tempPos.x += sin(tempPos.y + time);
	//tempPos.y += cos(tempPos.z + time);
	//tempPos.z += atan(tempPos.x + time);
	curPos = vec4(model * vec4(tempPos, 1.0)).xyz;
	gl_Position = camMat * vec4(curPos, 1.0);
	//curPos = gl_Position.xyz;
	//curPos = vec3(model * vec4(aPos, 1.0));
	texCoord = vec2(aTex.x, aTex.y);
	color = aColor;
	normVec = normMat * aNormals;

	float dist = length(vec4(vec4(curPos, 1.0) * camMat).xyz);
	visib = clamp(exp(-pow(dist * density, grad)), 0.0, 1.0);
	visib = 1.0;
}