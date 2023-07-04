#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define CLB_GL_2D false
#define CLB_GL_3D true

class OpenGLObj {
public:
	OpenGLObj();
	~OpenGLObj();
	void configureArray(GLfloat*, GLsizei, bool);
	void configureIndex(GLuint*, GLsizei);
	void bind();
	void bindEx();
	void unbind();
	void unbindEx();

	void setEBO(GLuint);
	GLuint getEBO() const;
private:
	void __config2D();
	void __config3D();
private:
	GLuint m_VBO = 0;
	GLuint m_VAO = 0;
	GLuint m_EBO = 0;

	GLuint* m_pIndices;

};