#include "enemy.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	//移動速度
	constexpr float kSpeed = -4.0f;
}

//-----------------------------------------------★
//EnemyStepOn
//------------------------------------------------

void EnemyStepOn::setGraph(int handle)
{
	//グラフィックデータ取得
	m_handle = handle;
	//サイズの取得
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}

void EnemyStepOn::setup(float fieldY)
{
	//地面
	m_fieldY = fieldY;

	//初期位置
	m_pos.x = Game::kScreenWidth - 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	//移動
	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}

void EnemyStepOn::update()
{
	if (m_isDead)	return;
	m_pos += m_vec;

	//壁に当たったら向きを変える
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

	//当たったとき
	if (m_isHit)
	{
		//音を鳴らして
		PlaySoundMem(m_hDamageSe, DX_PLAYTYPE_BACK, true);
		//死亡判定にする
		m_isDead = true;
	}
}

void EnemyStepOn::draw()
{
	if (m_isDead)	return;
	//右を向いているときに右の絵を表示
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

//-----------------------------------------------★
//EnemyKnockDown
//------------------------------------------------

void EnemyKnockDown::setGraph(int handle)
{
	m_handle = handle;
	//サイズ取得
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
}

void EnemyKnockDown::setup(float posX)
{
	//初期位置
	m_pos.x = m_colSize.x + posX;
	m_pos.y = m_colSize.y;
	
	//移動
	m_vec.x = -kSpeed;
	m_vec.y = kSpeed;
}

void EnemyKnockDown::update()
{
	if (m_isDead)	return;
	m_pos += m_vec;

	//壁に当たったら向きを反対にして反射音を再生する
	if (m_pos.x < 0)
	{
		m_vec.x *= -1.0f;
		sound();
	}
	if (m_pos.x > Game::kScreenWidth - getRadius() * 2)
	{
		m_vec.x *= -1.0f;
		sound();
	}
	if (m_pos.y < 0)
	{
		m_vec.y *= -1.0f;
		sound();
	}
	if (m_pos.y > Game::kScreenHeight - getRadius() * 2)
	{
		m_vec.y *= -1.0f;
		sound();
	}

	//弾に当たったときダメージ音を再生して生死判定をtrueに
	if (m_isHit)
	{
		PlaySoundMem(m_hDamageSe, DX_PLAYTYPE_BACK, true);
		m_isDead = true;
	}
}

void EnemyKnockDown::draw()
{
	if (m_isDead)	return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

void EnemyKnockDown::sound()
{
	PlaySoundMem(m_hReflectionSe, DX_PLAYTYPE_BACK, true);
}

float EnemyKnockDown::getRadius() const
{
	//画像の半径
	return m_graphSize.x / 2;
}

Vec2 EnemyKnockDown::getCenter() const
{
	//当たり判定の中心位置
	Vec2 result = m_pos;
	result.x += m_graphSize.x / 2;
	result.y += m_graphSize.y / 2;

	return result;
}

void EnemyKnockDown::bound(Vec2 targetPos)
{
	//反射方向
	Vec2 boundDir = m_pos - targetPos;
	//現在と同じ速度にする
	float speed = m_vec.length();

	//反射方向に現在の速度で移動する
	m_vec = boundDir.normalize() * speed;
	//反射音再生
	sound();
}