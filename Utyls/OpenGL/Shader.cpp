#include "Shader.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>

Shader::Shader() {

}

Shader::~Shader() {
	if (this->m_ShaderProg) {
		glDeleteProgram(this->m_ShaderProg);
	}
}

bool Shader::loadFromFile(const std::string& vert, const std::string& frag) {
	TextFile srcVert, srcFrag;
	if (srcVert.loadFile(vert) && srcFrag.loadFile(frag)) {
		GLuint vertex, fragment;
		GLuint errv, errf;
		std::cout << "Vertex Shader: " << vert << "\n";
		errv = this->createShader(srcVert, vertex, GL_VERTEX_SHADER);
		std::cout << "Fragment Shader: " << frag << "\n";
		errf = this->createShader(srcFrag, fragment, GL_FRAGMENT_SHADER);
		char errLog[1024];
		if (!errv) {
			glGetShaderInfoLog(vertex, sizeof(errLog), NULL, errLog);
			std::cout << "Error while compiling Vertex Shader:\n" 
				<< errLog;
		}
		if (!errf) {
			glGetShaderInfoLog(fragment, sizeof(errLog), NULL, errLog);
			std::cout << "Error while compiling Fragment Shader:\n"
				<< errLog;
		}
		this->m_ShaderProg = glCreateProgram();
		glAttachShader(this->m_ShaderProg, vertex);
		glAttachShader(this->m_ShaderProg, fragment);
		glLinkProgram(this->m_ShaderProg);

		GLint progErr;
		glGetProgramiv(this->m_ShaderProg, GL_LINK_STATUS, &progErr);
		if (!progErr) {
			glGetProgramInfoLog(this->m_ShaderProg, sizeof(errLog), NULL, errLog);
			std::cout << "Error while compiling Fragment Shader:\n"
				<< errLog;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return progErr;
	}
	return false;
}

GLuint Shader::createShader(const TextFile& src, GLuint& ID, GLenum kind) {
	GLint errRet;

	ID = glCreateShader(kind);

	const char* strSrc = src.m_DataStr.c_str();
#ifdef _DEBUG
	std::cout
		<< "****************\n"
		<< src.m_DataStr 
		<< "\n****************\n";
#endif
	glShaderSource(ID, 1, &strSrc, NULL);
	glCompileShader(ID);
	glGetShaderiv(ID, GL_COMPILE_STATUS, &errRet);
	return errRet;
}

void Shader::useProgram() {
	glUseProgram(this->m_ShaderProg);
}


//Int and floats

void Shader::setUniform(const std::string& var, int val) {
	glUniform1i(glGetUniformLocation(this->m_ShaderProg, var.c_str()), val);
}

void Shader::setUniform(const std::string& var, float val) {
	GLuint id = glGetUniformLocation(this->m_ShaderProg, var.c_str());
	glUniform1f(glGetUniformLocation(this->m_ShaderProg, var.c_str()), val);
}


//Float vectors
void Shader::setUniform(const std::string& var, glm::vec2& val) {
	GLuint id = glGetUniformLocation(this->m_ShaderProg, var.c_str());
	glUniform2fv(id, 1, glm::value_ptr(val));
}
//inline void Shader::setUniform(const std::string& var, glm::vec2&& val) {
//	glUniform2fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr(val));
//}

void Shader::setUniform(const std::string& var, glm::vec3& val) {
	glUniform3fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr(val));
}

void Shader::setUniform(const std::string& var, glm::vec4& val) {
	glUniform4fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr(val));
}

//Integer vectors
void Shader::setUniform(const std::string& var, glm::ivec2& val) {
	glUniform2iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr(val));
}

void Shader::setUniform(const std::string& var, glm::ivec3& val) {
	glUniform3iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr(val));
}

void Shader::setUniform(const std::string& var, glm::ivec4& val) {
	glUniform4iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, glm::value_ptr(val));
}


//Float matrix
void Shader::setUniform(const std::string& var, glm::mat2& val) {
	glUniformMatrix2fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setUniform(const std::string& var, glm::mat3& val) {
	GLuint id = glGetUniformLocation(this->m_ShaderProg, var.c_str());
	glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setUniform(const std::string& var, glm::mat4& val) {
	GLuint id = glGetUniformLocation(this->m_ShaderProg, var.c_str());
	glUniformMatrix4fv( id, 1, GL_FALSE, glm::value_ptr(val));
}

/*
void Shader::setUniform(const std::string& var, const GLvoid* ptr, Clb::GLSL_types kind) {
	switch (kind) {
	case Clb::VEC2:
		glUniform2fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, (GLfloat*)ptr);
		break;
	case Clb::VEC3:
		glUniform3fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, (GLfloat*)ptr);
		break;
	case Clb::VEC4:
		glUniform4fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, (GLfloat*)ptr);
		break;


	case Clb::IVEC2:
		glUniform2iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, (GLint*)ptr);
		break;
	case Clb::IVEC3:
		glUniform3iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, (GLint*)ptr);
		break;
	case Clb::IVEC4:
		glUniform4iv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, (GLint*)ptr);
		break;


	case Clb::MAT2:
		glUniformMatrix2fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, GL_FALSE, (GLfloat*)ptr);
		break;
	case Clb::MAT3:
		glUniformMatrix3fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, GL_FALSE, (GLfloat*)ptr);
		break;
	case Clb::MAT4:
		glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderProg, var.c_str()), 1, GL_FALSE, (GLfloat*)ptr);
		break;
	}
}
*/