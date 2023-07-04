#include "OpenGLObject.h"
//#include "Renderer2D.h"
#include <iostream>

OpenGLObj::OpenGLObj() :m_pIndices(nullptr) {

}

OpenGLObj::~OpenGLObj() {

}

void OpenGLObj::configureArray(GLfloat* float_arr, GLsizei size, bool is3D) {

	glGenVertexArrays(1, &this->m_VAO);
	glBindVertexArray(this->m_VAO);

	glGenBuffers(1, &this->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, size, float_arr, GL_DYNAMIC_DRAW);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	if (is3D)
		this->__config3D();
	else
		this->__config2D();
}

void OpenGLObj::__config2D() {

	//X Y
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)0);
	glEnableVertexAttribArray(0);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//U V
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(1);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//Translate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 4));
	glEnableVertexAttribArray(2);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//QuadWH
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(3);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//Scale & Dir
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 8));
	glEnableVertexAttribArray(4);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//Dir
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 10));
	glEnableVertexAttribArray(5);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//Layer
	glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 11));
	glEnableVertexAttribArray(6);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//Anchor
	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 12));
	glEnableVertexAttribArray(7);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//Color
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 18, (void*)(sizeof(GLfloat) * 14));
	glEnableVertexAttribArray(8);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
}

void OpenGLObj::__config3D() {

	//X Y Z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 12, (void*)0);
	glEnableVertexAttribArray(0);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//R G B A
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 12, (void*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//U V
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 12, (void*)(sizeof(GLfloat) * 7));
	glEnableVertexAttribArray(2);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
	//Normals
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 12, (void*)(sizeof(GLfloat) * 9));
	glEnableVertexAttribArray(3);
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line" << (__LINE__) << "\n";
	}
}
void OpenGLObj::configureIndex(GLuint* pIndices, GLsizei size) {
	//this->m_pIndices = pIndices;
	this->bind();
	glGenBuffers(1, &this->m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pIndices, GL_DYNAMIC_DRAW);
	this->unbindEx();
}

void OpenGLObj::bind() {
	glBindVertexArray(this->m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
}

void OpenGLObj::bindEx() {
	glBindVertexArray(this->m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO);
}

void OpenGLObj::unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLObj::unbindEx() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void OpenGLObj::setEBO(GLuint ebo) {
	this->m_EBO = ebo;
}

GLuint OpenGLObj::getEBO() const {
	return this->m_EBO;
}