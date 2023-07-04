#pragma once
#include <vector>
#include "..\Texture.h"
#include "..\OpenGLObject.h"

struct VertexGL {
	//Position
	GLfloat vx;
	GLfloat vy;
	GLfloat vz;
	//Colors
	GLfloat r = 1.0;
	GLfloat g = 1.0;
	GLfloat b = 1.0;
	GLfloat a = 1.0;
	//TexCoords
	GLfloat u;
	GLfloat v;
	//Normals
	GLfloat vni;
	GLfloat vnj;
	GLfloat vnk;
};

struct Material {
	std::string MatName;
	std::string MatFileName;
	Texture mat;

	//AmbientCol
	GLfloat ar = 1.0;
	GLfloat ag = 1.0;
	GLfloat ab = 1.0;
	//DiffuseCol
	GLfloat dr = 1.0;
	GLfloat dg = 1.0;
	GLfloat db = 1.0;
	//SpecularCol
	GLfloat sr = 1.0;
	GLfloat sg = 1.0;
	GLfloat sb = 1.0;
	//ECol???
	GLfloat er = 1.0;
	GLfloat eg = 1.0;
	GLfloat eb = 1.0;
	//Alpha
	GLfloat alpha = 1.0;
};

struct vertGroup {
	VertexGL* pVert = nullptr;
	std::string texname;
	Texture tex;
	size_t size;
	OpenGLObj obj;
};

struct VertexArray {
	Material* pMaterial = nullptr;
	std::vector<VertexGL> vertex;
};

struct PartEx {
	std::string PartName;
	std::string MatName;
	Texture texture;
	VertexGL* VxArray = nullptr;
	size_t size;
};

struct Part {
	std::string PartName;
	Material material;
	std::vector<VertexGL> VxArray;
};

struct Mesh {
	std::string MeshName;
	std::vector<Part> Parts;
};

struct _3DModel {
	std::string ModelName;
	std::vector<Mesh> Meshes;
};
