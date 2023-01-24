#include "Player.h"
#include "Commons.h"

tagPlayer::tagPlayer(float x, float y, float rad, sf::RenderWindow* win) : m_pWin(win) {
	this->m_x = x;
	this->m_y = y;
	this->m_hitRad = rad;
}

void tagPlayer::PlayerUpdateLogic() {
	updateMove();
}

void tagPlayer::PlayerUpdateDraw() {
	drawHitbox();
}

void tagPlayer::drawHitbox() {
	if(!this->m_isHit)
		drawCircle(this->m_x, this->m_y, this->m_hitRad, {255, 0, 0, 255}, this->m_pWin);
	else
		drawCircle(this->m_x, this->m_y, this->m_hitRad, {1, 255, 0, 0}, this->m_pWin);
}
//
//void tagPlayer::checkHit(const CTamaManager& TamaMgr) {
//	bool del = false;
//	for (int i = 0; i < TamaMgr.m_tamaCnt; i++) {
//		if (!(TamaMgr.p_Tama[i].m_Deleted)) {
//			del  |= hitCheck(TamaMgr.p_Tama[i].m_x - this->m_x,
//				TamaMgr.p_Tama[i].m_y - this->m_y,
//				TamaMgr.p_Tama[i].m_Rad + this->m_hitRad);
//		}
//		else
//			continue;
//	}
//	if (del)
//		;//	_asm { nop };
//	this->m_isHit = del;
//}

void tagPlayer::updateMove() {
	float ang = RAD(0);

	sf::Keyboard kbd;

	if (kbd.isKeyPressed(sf::Keyboard::Up) || kbd.isKeyPressed(sf::Keyboard::Down) ||
		kbd.isKeyPressed(sf::Keyboard::Left) || kbd.isKeyPressed(sf::Keyboard::Right)) {
		if (kbd.isKeyPressed(sf::Keyboard::Up)) {
			ang = RAD(-90);
		} else if (kbd.isKeyPressed(sf::Keyboard::Down)) {
			ang = RAD(90);
		}
		else if (kbd.isKeyPressed(sf::Keyboard::Left)) {
			ang = RAD(180);
		}
		else if (kbd.isKeyPressed(sf::Keyboard::Right)) {
			ang = RAD(0);
		}
		this->m_x += cos(ang) * this->m_Speed;
		this->m_y += sin(ang) * this->m_Speed;
	}
}