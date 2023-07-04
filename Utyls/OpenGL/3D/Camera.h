#pragma once
#include <glm/glm/matrix.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class Camera {
public:
	void move(glm::vec3);
	void setRatio(float);
	float getRatio();
	glm::mat4 getCamMat();

private:
	float m_Ratio;
	float speed = 0.7f;
	glm::mat4 m_CamMat;
	glm::mat4 m_View;
	glm::mat4 m_Proj;
	glm::vec3 m_Orientation = glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 m_Up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 m_Position = glm::vec3(0.0, 0.0, 0.0);
};
