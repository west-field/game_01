#include "shot.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	//プレイヤーグラフィックサイズ
	static constexpr int kGraphicSizeX = 32;
	static constexpr int kGraphicSizeY = 32;
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
void Shot::start(Vec2 pos, Vec2 vec)
{
	m_isExist = true;		//見えるように
	m_pos = pos;

	m_pos = pos;
	m_vec = vec * 2;
}

void Shot::update()
{
	if (!m_isExist)	return;
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
// 表示
void Shot::draw()
{
	if (!m_isExist)	return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y),
		static_cast<int>(getRadius()), GetColor(255, 255, 255), false);
}
//当たり判定の半径取得
float Shot::getRadius() const
{
	//画像の半径
	return kGraphicSizeX / 4;
}
//当たり判定の中心位置取得
Vec2 Shot::getCenter() const
{
	//当たり判定の中心位置
	Vec2 result = m_pos;
	result.x += kGraphicSizeX / 2;
	result.y += kGraphicSizeY / 2;

	return result;
}