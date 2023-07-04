#pragma once
#include "OBJModel.h"
#include "Camera.h"
#include "..\Shader.h"
#include "Light.h"
#include <iostream>

class TriDiObject {
public:
	TriDiObject();

	Shader& setShader();

	void loadModel(std::string file, std::map<std::string, OBJModel*>& cache) {
		if (cache.find(file) == cache.end()) {
			this->TriDiModel = new OBJModel();
			this->TriDiModel->loadFromFile(file);
			cache.insert({ file, this->TriDiModel });
		}
		else {
			this->TriDiModel = cache[file];
		}
	}

	void restartShader() {
	}

	void draw(Camera& cam, Light& light, float tm) {
		static glm::vec3 lpos(0.0f, 0.0f, 50.0f);
		glm::vec4 lightCol(1.0);
		glm::mat3 normMat(1.0);
#ifdef _DEBUG
		while (GLenum err = glGetError()) {
			std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
		}
#endif
		this->m_Shader.useProgram();
#ifdef _DEBUG
		while (GLenum err = glGetError()) {
			std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
		}
#endif
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		this->m_Shader.setUniform("time", tm);
		glm::mat4 tempCam = cam.getCamMat();
		this->m_Shader.setUniform("camMat", tempCam);
		this->m_Shader.setUniform("lightCnt", 1);
#ifdef _DEBUG
		while (GLenum err = glGetError()) {
			std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
		}
#endif
		int i = 0; {
			std::string var0 = "lightVec[" + std::to_string(i) + "].pos";
			std::string var1 = "lightVec[" + std::to_string(i) + "].color";
			glm::vec3 lightPos = light.getPos();
			glm::vec4 lightColor = light.getColor();
			this->m_Shader.setUniform(var0, lightPos);
#ifdef _DEBUG
			while (GLenum err = glGetError()) {
				std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
			}
#endif
			this->m_Shader.setUniform(var1, lightColor);
#ifdef _DEBUG
			while (GLenum err = glGetError()) {
				std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
			}
#endif
		}
		glm::vec3 camPos = glm::vec3(pos.x, pos.y, pos.z);
		this->m_Shader.setUniform("camPos", camPos);
#ifdef _DEBUG
		while (GLenum err = glGetError()) {
			std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
		}
#endif
		//this->TriDiModel->m_ModelVertex[0].tex.bindTexture();
		//glDisable(GL_DEPTH_TEST);
		for (auto& it : this->TriDiModel->m_ModelVertex) {
			it.obj.bind();
#ifdef _DEBUG
			while (GLenum err = glGetError()) {
				std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
			}
#endif
			it.tex.bindTexture();
#ifdef _DEBUG
			while (GLenum err = glGetError()) {
				std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
			}
#endif
			glm::vec2 texUV = it.tex.getSize();
			model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
			model = glm::translate(model, pos);
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
			normMat = glm::transpose(glm::inverse(model));

			m_Shader.setUniform("model", model);
#ifdef _DEBUG
			while (GLenum err = glGetError()) {
				std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
			}
#endif
			m_Shader.setUniform("normMat", normMat);
#ifdef _DEBUG
			while (GLenum err = glGetError()) {
				std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
			}
#endif
			//m_Shader.setUniform("view", sf::Glsl::Mat4(glm::value_ptr(view)));
			//m_Shader.setUniform("proj", sf::Glsl::Mat4(glm::value_ptr(proj)));
			//m_Shader.setUniform("wh", texUV);
#ifdef _DEBUG
			while (GLenum err = glGetError()) {
				std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
			}
#endif

			// Draw the cube
			glDrawArrays(GL_TRIANGLES, 0, GLsizei(it.size));
		}
		glEnable(GL_DEPTH_TEST);
	}

	~TriDiObject() {
	}

	OBJModel* TriDiModel = nullptr;

private:
	GLuint img;
	glm::vec3 pos;
	Shader m_Shader;
	glm::mat4 model;
};