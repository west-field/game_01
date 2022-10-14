#include "DxLib.h"
#include "game.h"
#include "ShotBound.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;

	//跳ね返り回数
	constexpr int kBoundMax = 3;

	//グラフィックデータのサイズ
	constexpr int kSizeX = 16;
	constexpr int kSizeY = 16;
}

//ショット開始
void ShotBound::start(Vec2 pos)
{
	ShotBase::start(pos);

	float randAngle = static_cast<float>(GetRand(359));
	float rad = static_cast<float>(randAngle * 3.14159f / 180.0);//ラジアンに変換

	m_vec.x = cosf(rad) * kShotSpeed;
	m_vec.y = sinf(rad) * kShotSpeed;
//	m_vec *= kShotSpeed;//Vec2の掛け算を利用

	m_boundCount = 0;
}
// 更新
void ShotBound::update()
{
	if (!m_isExist)	return;
	m_pos += m_vec;

	if (m_boundCount < kBoundMax)
	{
		//画面端での反射
		if (m_pos.x < 0.0f)
		{
			m_pos.x = 0.0f;
			m_vec.x *= -1.0f;
			m_boundCount++;
		}
		if (m_pos.y < 0.0f)
		{
			m_pos.y = 0.0f;
			m_vec.y *= -1.0f;
			m_boundCount++;
		}
		if (m_pos.x > Game::kScreenWidth - kSizeX)
		{
			m_pos.x = Game::kScreenWidth - kSizeX;
			m_vec.x *= -1.0f;
			m_boundCount++;
		}
		if (m_pos.y > Game::kScreenHeight - kSizeY)
		{
			m_pos.y = Game::kScreenHeight - kSizeY;
			m_vec.y *= -1.0f;
			m_boundCount++;
		}
	}
	else
	{
		if (m_pos.x <( 0 - kSizeX))
		{
			m_isExist = false;
		}
		if (m_pos.y < (0 - kSizeY))
		{
			m_isExist = false;
		}
		if (m_pos.x > Game::kScreenWidth)
		{
			m_isExist = false;
		}
		if (m_pos.y > Game::kScreenHeight)
		{
			m_isExist = false;
		}
	}
}