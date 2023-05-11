#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


//Matrices
uniform mat4 camMat;
uniform mat4 model;


//Some vertex data
in vec2 posXY[];
in vec2 texXY[];
in vec2 quadSize[];

out vec4 color;
out vec2 texCoord;

void main() {
	gl_Position = camMat * model * vec4(posXY[0], 0.0, 1.0);
	texCoord = texXY[0];
	color = vec4(1.0);
	EmitVertex();

	gl_Position = camMat * model * vec4(posXY[0] + vec2(quadSize[0].x, 0.0), 0.0, 1.0);
	texCoord = texXY[0] + vec2(quadSize[0].x, 0.0);
	EmitVertex();

	gl_Position = camMat * model * vec4(posXY[0] + vec2(quadSize[0].x, quadSize[0].y), 0.0, 1.0);
	texCoord = texXY[0] + vec2(quadSize[0].x, quadSize[0].y);
	EmitVertex();

	gl_Position = camMat * model * vec4(posXY[0] + vec2(0.0, quadSize[0].y), 0.0, 1.0);
	texCoord = texXY[0] + vec2(0.0, quadSize[0].y);
	EmitVertex();
}