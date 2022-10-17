#include "shot.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
}

Shot::Shot()
{
	m_handle = -1;
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}
void Shot::start(Vec2 pos)
{
	m_isExist = true;		//Œ©‚¦‚é‚æ‚¤‚É
	m_pos = pos;
	
}

void Shot::update(Vec2 kShotSpeed)
{
	if (!m_isExist)	return;
	m_vec = kShotSpeed;
	m_pos += m_vec;
	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
	if (m_pos.x < 0)
	{
		m_isExist = false;
	}
	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}
	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}
// •\Ž¦
void Shot::draw()
{
	if (!m_isExist)	return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}