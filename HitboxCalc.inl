#include "Enemy.h"

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
	//Get slope
	float enm_new_x = enm2.m_x - enm1.m_x, enm_new_y = enm2.m_y - enm1.m_y;
	float cang = (enm_new_x < 0.0f ) ? -std::cos(enm2.m_RectRot) : std::cos(enm2.m_RectRot);
	if (!cang) {
		Enemy temp;
		temp.m_x = enm2.m_x;
		temp.m_y = enm2.m_y;
		temp.m_HitWidth = enm2.m_HitHeight;
		temp.m_HitHeight = enm2.m_HitWidth;
		return hitCheckNRBNRB(enm1, enm2);
	}
	float sang = (enm_new_y < 0.0f) ? -std::sin(enm2.m_RectRot) : std::sin(enm2.m_RectRot);
	float final_ang = std::atan2(sang, cang);
	float v0 = enm_new_x - std::cos(final_ang) * enm2.m_HitWidth + std::sin(final_ang) * enm2.m_HitHeight;
	float v1 = enm_new_y + std::sin(final_ang) * enm2.m_HitWidth - std::cos(final_ang) * enm2.m_HitHeight;
	float slope = sang / cang;
	float expected_x = (enm1.m_y - enm_new_y + v1) * slope;
	return expected_x <= enm1.m_HitWidth * 0.5;
}

inline bool hitCheckCC(const Enemy& enm1, const Enemy& enm2) {
	return std::hypot(enm2.m_x - enm1.m_x, enm2.m_y - enm1.m_y) <= enm2.m_Radius + enm1.m_Radius;
}
