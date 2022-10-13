#include "enemy.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	//速度
	constexpr float kSpeed = -5.0f;
}

//------------------------------------------------
//EnemyBase
//------------------------------------------------

// グラフィックデータの設定	内部でサイズも取得する
void EnemyBase::setGraph(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}
// 描画
void EnemyBase::draw()
{
	if (m_isDead)	return;
	if (m_isRight)
	{
		DrawRectGraphF(m_pos.x, m_pos.y, 0, 0,
			static_cast<int>(m_graphSize.x) / 2, static_cast<int>(m_graphSize.y),
			m_handle, true, false);
	}
	else
	{
		DrawRectGraphF(m_pos.x, m_pos.y, static_cast<int>(m_graphSize.x) / 2, 0,
			static_cast<int>(m_graphSize.x) / 2, static_cast<int>(m_graphSize.y),
			m_handle, true, false);
	}
}
//------------------------------------------------
//EnemyStepOn
//------------------------------------------------

// 初期設定	地面の高さを与える
void EnemyStepOn::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth - 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}

// 更新
void EnemyStepOn::update()
{
	if (m_isDead)	return;
	m_pos += m_vec;

	if (m_pos.x < 0)
	{
		m_vec.x *= -1.0f;
		m_isRight = true;
	}
	if (m_pos.x > Game::kScreenWidth - 32.0f)
	{
		m_vec.x *= -1.0f;
		m_isRight = false;
	}

	PlaySoundMem(m_hDamageSe, DX_PLAYTYPE_BACK, true);
}

//------------------------------------------------
//EnemyKnockDown
//------------------------------------------------

// 初期設定	地面の高さを与える
void EnemyKnockDown::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth - 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

// 更新
void EnemyKnockDown::update()
{
	
}