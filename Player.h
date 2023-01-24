#pragma once
#define RAD(x) x * 3.14159 / 180.0f

#include <SFML/Graphics.hpp>

class tagTama;
class CTamaManager;

typedef class tagPlayer {
public:
	void PlayerUpdateLogic(const CTamaManager& TamaMgr);
	void PlayerUpdateLogic();
	void PlayerUpdateDraw();
	void updateMove();

	float getX() const { return this->m_x; }
	float getY() const { return this->m_y; }
	float gethitRad() const { return this->m_hitRad; }
	tagPlayer(float x, float y, float rad, sf::RenderWindow* target);

	friend class tagTama;
private:
	bool m_isHit = false;

	float m_x;
	float m_y;
	float m_hitRad;
	float m_Speed = 5.5f;
	void drawHitbox();
	void checkHit(const CTamaManager& TamaMgr);

	sf::RenderWindow* m_pWin = nullptr;
} Player;