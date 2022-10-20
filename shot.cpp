#include "shot.h"
#include "game.h"
#include "DxLib.h"

Shot::Shot()
{
	m_handle = -1;

	m_pos.x = 0.0f;
	m_pos.y = 0.0f;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_isExist = false;
}
void Shot::setHandle(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
}
void Shot::start(Vec2 pos, Vec2 vec)
{
	m_isExist = true;		//������悤��

	//�����ʒu
	m_pos = pos;
	
	//�ړ����x
	m_vec = vec * 2;
}

void Shot::update()
{
	if (!m_isExist)	return;
	m_pos += m_vec;
	
	//��ʂ̒[�܂ōs�����瑶�݂�����
	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
	if (m_pos.x < 0 - (getCenter().x + getRadius()))
	{
		m_isExist = false;
	}
	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}
	if (m_pos.y < 0 - (getCenter().y + getRadius()))
	{
		m_isExist = false;
	}
}

void Shot::draw()
{
	if (!m_isExist)	return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

float Shot::getRadius() const
{
	//�摜�̔��a
	return m_graphSize.x / 4;
}

Vec2 Shot::getCenter() const
{
	//�����蔻��̒��S�ʒu
	Vec2 result = m_pos;
	result.x += m_graphSize.x / 2;
	result.y += m_graphSize.y / 2;

	return result;
}