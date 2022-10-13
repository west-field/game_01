#include "enemy.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	//速度
	constexpr float kSpeed = -5.0f;
}

// グラフィックデータの設定	内部でサイズも取得する
void EnemyStepOn::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}

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
}
// 描画
void EnemyStepOn::draw()
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
bool EnemyStepOn::isCol(PlayerStepOn& player)
{
	if (m_isDead)	return false;

	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + m_colSize.x;
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + m_colSize.y;

	float playerLeft = player.getPos().x;
	float playerRight = player.getPos().x + player.getColSize().x;
	float playerTop = player.getPos().y;
	float playerBottom = player.getPos().y + player.getColSize().y;

	if (enemyLeft > playerRight)	return false;//赤
	if (enemyRight < playerLeft)	return false;//黄色
	if (enemyTop > playerBottom)	return false;//緑
	if (enemyBottom < playerTop)	return false;//青

	PlaySoundMem(m_hDamageSe, DX_PLAYTYPE_BACK, true);
	return true;
}