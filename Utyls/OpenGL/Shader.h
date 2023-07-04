#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <string>
#include "..\FileIO\TextFile.h"

namespace Clb {
	typedef enum {
		VEC2 = 2,
		VEC3,
		VEC4,
		IVEC2,
		IVEC3,
		IVEC4,
		MAT2,
		MAT3,
		MAT4,
	} GLSL_types;
}
class Shader {
public:
	Shader();
	~Shader();

	//Shader(std::string, std::string, std::string);

	//Load from file
	bool loadFromFile(const std::string&, const std::string&);

	//Uniform stuff
	void setUniform(const std::string&, float);
	void setUniform(const std::string&, int);
	
	void setUniform(const std::string&, glm::vec2&);
	//void setUniform(const std::string&, glm::vec2&&);
	void setUniform(const std::string&, glm::vec3&);
	void setUniform(const std::string&, glm::vec4&);

	void setUniform(const std::string&, glm::ivec2&);
	void setUniform(const std::string&, glm::ivec3&);
	void setUniform(const std::string&, glm::ivec4&);

	void setUniform(const std::string&, glm::mat2&);
	void setUniform(const std::string&, glm::mat3&);
	void setUniform(const std::string&, glm::mat4&);

	//void setUniform(const std::string&, const GLvoid*, Clb::GLSL_types);
	//void setUniform(const std::string&, GLint*, int);


	//Binding and unbinding
	void useProgram();

private:
	GLuint createShader(const TextFile&, GLuint&, GLenum);
	GLuint m_ShaderProg = 0;
};

/*
inline void Shader::setUniform(const std::string& var, int val) {
	glUniform1i(glGetUniformLocation(this->m_ShaderProg, var.c_str()), val);
}

inline void Shader::setUniform(const std::string& var, float val) {
	glUniform1f(glGetUniformLocation(this->m_ShaderProg, var.c_str()), val);
}


//Float vectors
inline void Shader::setUniform(const std::string& var, glm::vec2& val) {
	glUniform2fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr<glm::vec2>(val));
}
inline void Shader::setUniform(const std::string& var, glm::vec2&& val) {
	glUniform2fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr<glm::vec2>(val));
}

inline void Shader::setUniform(const std::string& var, glm::vec3& val) {
	glUniform3fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr<glm::vec3>(val));
}

inline void Shader::setUniform(const std::string& var, glm::vec4& val) {
	glUniform4fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr<glm::vec4>(val));
}

//Integer vectors
inline void Shader::setUniform(const std::string& var, glm::ivec2& val) {
	glUniform2iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr<glm::ivec2>(val));
}

inline void Shader::setUniform(const std::string& var, glm::ivec3& val) {
	glUniform3iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr<glm::ivec3>(val));
}

inline void Shader::setUniform(const std::string& var, glm::ivec4& val) {
	glUniform4iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr<glm::ivec4>(val));
}


//Float matrix
inline void Shader::setUniform(const std::string& var, glm::mat2& val) {
	glUniformMatrix2fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, GL_FALSE, glm::value_ptr<glm::mat2>(val));
}

inline void Shader::setUniform(const std::string& var, glm::mat3& val) {
	glUniformMatrix3fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, GL_FALSE, glm::value_ptr<glm::mat3>(val));
}

inline void Shader::setUniform(const std::string& var, glm::mat4& val) {
	glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, GL_FALSE, glm::value_ptr<glm::mat4>(val));
}*/