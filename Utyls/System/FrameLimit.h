/********************
	FrameLimit.h
*********************
* The code within these two files was taken from
* https://github.com/pbghogehoge/kog/blob/master/Source/CFpsCtrl.h
* https://github.com/pbghogehoge/kog/blob/master/Source/CFpsCtrl.cpp
* So, credits to pbghogehoge (https://github.com/pbghogehoge).
* It has been slightly modified to use doubles instead of ints
*/

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <GLFW/glfw3.h>

class CFrameLimiter {
public:
	CFrameLimiter();
	~CFrameLimiter();

	void setFPSLimit(uint32_t);
	double getFPS() const;

	bool onUpdate();
private:
	double m_begin;
	double m_MoveCnt;
	double m_FPS;
	uint32_t m_Count;
	double m_realFPS;

	double m_Samples[2];
};
