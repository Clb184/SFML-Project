#include "Enemy.h"
#include "Commons.h"
#include <cmath>

inline bool hitCheckNRBNRB(const Enemy& enm1, const Enemy& enm2) {
	/*const float ew = enm1.m_HitWidth * 0.5f,
				eh = enm1.m_HitHeight * 0.5f,
				enm_x_now = std::abs(enm2.m_x - enm1.m_x) - enm2.m_HitWidth * 0.5f,
				enm_y_now = std::abs(enm2.m_y - enm1.m_y) - enm2.m_HitHeight * 0.5f;
				*/
	/*
	|		 ______
	|		|	  |
	|		|_____|
 h/2|_____
	|	  |
	______|____________________
	w/2
	*/
	//return (enm_x_now < ew&& enm_y_now < eh);
	return fabsf(enm1.m_x - enm2.m_x) * 2.0f < enm1.m_HitWidth + enm2.m_HitWidth &&
	fabsf(enm1.m_y - enm2.m_y) * 2.0f < enm1.m_HitHeight + enm2.m_HitHeight;
}
									//NRB          //RB
inline bool hitCheckNRBRB(const Enemy& enm1, const Enemy& enm2) {
	
	float enm_new_x = enm2.m_x - enm1.m_x, enm_new_y = enm2.m_y - enm1.m_y, ang = enm2.m_RectRot;
	float width, height, awidth;

	float cang = std::cosf(ang);
	float sang = std::sinf(ang);
	if (std::fabsf(cang) == 1.0f)
		return hitCheckNRBNRB(enm1, enm2);
	else if (std::fabsf(sang) == 1.0f) {
		Enemy temp;
		temp.m_x = enm2.m_x;
		temp.m_y = enm2.m_y;
		temp.m_HitWidth = enm2.m_HitHeight;
		temp.m_HitHeight = enm2.m_HitWidth;
		return hitCheckNRBNRB(enm1, temp);
	}


	if (enm_new_y < 0.0f) {
		ang = -ang;
		enm_new_y = -enm_new_y; 
		sang = -sang;
	}

	if (sang * cang < 0.0f) {
		width = enm2.m_HitHeight;
		height = enm2.m_HitWidth;
	} else {
		width = enm2.m_HitWidth;
		height = enm2.m_HitHeight;
	}

	enm_new_y -= enm1.m_HitHeight * 0.5;

	float N, S, E, W;
	N = fabsf(sang);
	S = -fabsf(sang);
	W = -fabsf(cang);
	E = fabsf(cang);

	//Left vectors and slope
	float vx, vy, slope, vx2, vy2, tx, ty;
	//For right arist
	float vex, vey, vex2, vey2, tex, tey;

	//X obtained after casting ray
	float ray_x;
	ang = atan2(S, E);
	slope = S / E;
	tx = (cosf(ang) * (-width * 0.5)) + (cosf(ang - RAD(90)) * (height * 0.5));
	ty = (sinf(ang) * (-width * 0.5)) + (sinf(ang - RAD(90)) * (height * 0.5));
	tex = (cosf(ang) * (-width * 0.5)) + (cosf(ang + RAD(90)) * (height * 0.5));
	tey = (sinf(ang) * (-width * 0.5)) + (sinf(ang + RAD(90)) * (height * 0.5));
	vx = enm_new_x + tx;
	vx2 = vx + E * width;
	vy = enm_new_y + ty;
	vy2 = vy + S * width;
	ray_x = -vy * slope;
	//drawLine(0.0f, enm2.m_y, 850.0f, enm2.m_y, 1.0f, 0.0f, 1.0f);
	//drawLine(enm2.m_x, 0.0, enm2.m_x, 480.0f, 1.0f, 0.0f, 1.0f);
	return false;
	//Taken from CEnemySLaser.cpp from pbghogehoge/kog/Source/
	/* Adapted from PBG's Kioh Gyoku source
	length = cosf(ang) * enm_new_x + sinf(ang) * enm_new_y;
	width = abs((-sinf(ang) * enm_new_x) + cosf(ang) * enm_new_y);
	awidth = fabsf(width);
	return length <= enm2.m_HitWidth && length > 0.0 && width < enm2.m_HitWidth;
	*/
	/*
	float new_width, new_height;
	float E;
	float W;
	float N;
	float S;
	float temp_ang;
	if (cang * sang > 0.0f || enm_new_x * enm_new_y < 0.0f) {
		new_width = enm2.m_HitHeight;
		new_height =  enm2.m_HitWidth;
		float temp = cang;
	}
	else {
		new_width = enm2.m_HitWidth;
		new_height = enm2.m_HitHeight;
		cang = cos(-enm2.m_RectRot);
		sang = sin(-enm2.m_RectRot);
	}
	if () {
		float hoge = new_width;
		new_width = new_height;
		new_height = hoge;
	}

	enm_new_x = fabsf(enm_new_x);
	enm_new_y = fabsf(enm_new_y);
	E =  fabsf(cang);
	W = -E;
	N =  fabsf(sang);
	S = -N;

	float final_ang = std::atan2(S, E);
	float deg_ang = final_ang / PI * 180.0f;
	float v0 = enm_new_x + (W * (new_width * 0.5) + cos(final_ang - RAD(90)) * (new_height * 0.5));
	float v1 = enm_new_y + (N * (new_width * 0.5) + sin(final_ang - RAD(90)) * (new_height * 0.5));
	//Get slope, find the y position when x = 0, cast rays from a limit to another to contain x
	float slope = S / E;
	float FixY = (v1 + N * (v0 / E));
	//float ray_y = v1 + sin(final_ang) * (new_width);
	float ray_x = v0 + cos(final_ang) * (new_width);
	float expected_x = slope * (enm1.m_HitHeight * 0.5f - FixY) ;
	return expected_x <= enm1.m_HitWidth * 0.5f && expected_x <= ray_x && expected_x >= v0;*/





}

inline bool hitCheckCC(const Enemy& enm1, const Enemy& enm2) {
	return std::hypot(enm2.m_x - enm1.m_x, enm2.m_y - enm1.m_y) <= enm2.m_Radius + enm1.m_Radius;
}
