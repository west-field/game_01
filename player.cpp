#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "Pad.h"

namespace
{
	//ジャンプ力
	constexpr float kJumpAcc = -18.0f;
	//重力
	constexpr float kGravity = 0.5f;
}

//------------------------------------------------
//PlayerBase
//------------------------------------------------

// グラフィックデータの設定	内部でサイズも取得する
void PlayerBase::setGraph(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}
void PlayerBase::draw()
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
//PlayerStepOn
//------------------------------------------------

// 初期設定	地面の高さを与える
void PlayerStepOn::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

void PlayerStepOn::update()
{
	if (m_isDead)	return;

	m_pos += m_vec;

	//地面との当たり判定
	bool isField = false;
	if (m_pos.y >= m_fieldY - m_graphSize.y)
	{
		m_pos.y = m_fieldY - m_graphSize.y;
		isField = true;
	}
	//プレイヤーの動き　地面についたらジャンプする
	if (isField)
	{
		m_vec.y = kJumpAcc;//ジャンプ開始
		PlaySoundMem(m_hJumpSe, DX_PLAYTYPE_BACK, true);
	}

	// キー入力処理 左右に移動
	Pad::update();
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_isRight = true;
		if (m_pos.x > Game::kScreenWidth - 32.0f)
		{
			m_pos.x = Game::kScreenWidth - 32.0f;
		}
		m_pos.x += 3.0f;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_isRight = false;
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
		m_pos.x -= 3.0f;
	}
	m_vec.y += kGravity;

}

bool PlayerStepOn::isCol(EnemyStepOn& enemy)
{
	if (m_isDead)	return false;

	float playerLeft = getPos().x;
	float playerRight = getPos().x + m_colSize.x;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + m_colSize.y;

	float enemyLeft = enemy.getPos().x;
	float enemyRight = enemy.getPos().x + enemy.getColSize().x;
	float enemyTop = enemy.getPos().y;
	float enemyBottom = enemy.getPos().y + enemy.getColSize().y;

	if (playerLeft > enemyRight)	return false;//赤
	if (playerRight < enemyLeft)	return false;//黄色
	if (playerTop > enemyBottom)	return false;//緑
	if (playerBottom < enemyTop)	return false;//青

	return true;
}

//------------------------------------------------
//PlayerKnockDown
//------------------------------------------------

// 初期設定	地面の高さを与える
void PlayerKnockDown::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

void PlayerKnockDown::update()
{

}