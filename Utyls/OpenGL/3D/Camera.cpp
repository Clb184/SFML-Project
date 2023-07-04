#include "Camera.h"

void Camera::move(glm::vec3 pos) {
	this->m_Position = pos;
	this->m_View = glm::lookAt(this->m_Position, this->m_Position + this->m_Orientation, this->m_Up);
	this->m_Proj = glm::perspective(glm::radians(90.0f), this->m_Ratio, 0.1f, 2500.0f);

	this->m_CamMat = this->m_Proj * this->m_View;
}

glm::mat4 Camera::getCamMat() {
	return this->m_CamMat;
}

void Camera::setRatio(float rat) {
	this->m_Ratio = rat;
}

float Camera::getRatio() {
	return this->m_Ratio;
}