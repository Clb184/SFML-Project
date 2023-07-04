#pragma once
#include <cstdio>
#include <iostream>
#include <map>
#include <glm/glm/matrix.hpp>
#include "3DModel.h"

class OBJModel {
public:
	void loadFromFile(std::string);

	std::vector<vertGroup> m_ModelVertex;
	~OBJModel();
private:
	class __file {
	public:
		char* __load(std::string);
		size_t size;
		char* buffer = nullptr;
		void __free();
	};

	void parseObj();
	void parseMat();

	void loadObj(std::string);
	void loadMaterial(std::string);

	//Store the XYZ of vertex
	std::vector<glm::vec3> m_Vec3Vec;
	//UV for texCoords
	std::vector<glm::vec2> m_UVVec;
	//Normals (For shading!)
	std::vector<glm::vec3> m_NormalVec;
	__file m_Obj;
	__file m_Mat;
	std::map<std::string, Material> m_MatArray;
};