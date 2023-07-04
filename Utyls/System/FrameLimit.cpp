#include "FrameLimit.h"
#include <timeapi.h>
#include <iostream>
#include <cmath>

CFrameLimiter::CFrameLimiter()
	: m_begin(0), m_MoveCnt(0), m_FPS(60), m_Count(0) {

}

CFrameLimiter::~CFrameLimiter() {

}

void CFrameLimiter::setFPSLimit(uint32_t fps) {
	this->m_FPS = fps;
}

double CFrameLimiter::getFPS() const {
	return this->m_realFPS;
}

bool CFrameLimiter::onUpdate() {
	double fps = this->m_FPS;
	double end = timeGetTime();
	double delta = end - this->m_begin;
	this->m_begin = end;
	this->m_MoveCnt += delta;

	if (this->m_MoveCnt > 1000.0 / fps) {
		this->m_MoveCnt = std::fmod(this->m_MoveCnt, 1000.0 / fps);
		this->m_realFPS = 1.0 / glfwGetTime();
		glfwSetTime(0);
		/*
		this->m_Samples[this->m_Count % 2] = end;
		double current, prev;
		current = end;
		prev = this->m_Samples[(this->m_Count + 1) % 2];
		delta = prev - current;
		this->m_realFPS = (2000) / delta;*/
		//std::cout << "Fps: " << this->m_MoveCnt << ".\n";
		return true;
	}

	this->m_Count++;
	return false;
}
