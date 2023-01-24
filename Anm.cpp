#include "Anm.h"
#include "Entity.h"

void CAnimation::setSpeed(const uint32_t& spd) {
	m_Speed = spd;
}

bool CAnimation::updateAnime(sf::RenderWindow* target, Entity* p_Entity) {
	if (p_Entity->m_Deleted)
		return false;

	if (m_Speed != 0 && !(m_Time % m_Speed)) {
		if (++m_CurFrame >= m_Frames) {
			m_CurFrame = 0;
		}
	}
	else
		m_CurFrame = 0;

	if (p_Entity->m_Flag & EFLAG_DRAW) {

		switch (p_Entity->m_BlendMode) {
		case 0:
			m_RStates.blendMode = sf::BlendNone;
			break;
		case 1:
			m_RStates.blendMode = sf::BlendAdd;
			break;
		case 2:
			m_RStates.blendMode = sf::BlendMultiply;
			break;
		case 3:
			m_RStates.blendMode = sf::BlendAlpha;
			break;
		}

		m_Sprites[m_CurFrame].m_Sprite.setScale(sf::Vector2f(p_Entity->m_sx, p_Entity->m_sy));
		m_Sprites[m_CurFrame].m_Sprite.setOrigin(sf::Vector2f(m_Sprites[m_CurFrame].m_ox + p_Entity->m_ox, m_Sprites[m_CurFrame].m_oy + p_Entity->m_oy));
		m_Sprites[m_CurFrame].m_Sprite.setColor(p_Entity->m_Color);
		m_Sprites[m_CurFrame].m_Sprite.setRotation(p_Entity->m_SprDir);
		m_Sprites[m_CurFrame].m_Sprite.setPosition(p_Entity->m_x, p_Entity->m_y);
		target->draw(m_Sprites[m_CurFrame].m_Sprite, m_RStates);
	}

	m_Time++;
	return true;
}
