#include "ShotSin.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
}

void ShotSin::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_basePos = pos;
	m_sinRate = 0.0f;
	m_moveHeight = 8.0f;

	m_vec.x = kShotSpeed;
	m_vec.y = 0.0f;
}

void ShotSin::update()
{
	if (!m_isExist)	return;
	m_basePos += m_vec;

	m_sinRate += 0.5f;
	m_moveHeight += 1.0f;

	m_pos = m_basePos;
	m_pos.y += sinf(m_sinRate) * m_moveHeight;
	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}
