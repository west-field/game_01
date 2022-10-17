#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "Pad.h"

namespace
{
	//ジャンプ力
	constexpr float kJumpAcc = -15.0f;
	//重力
	constexpr float kGravity = 0.5f;
	//速度
	constexpr float kSpeed = 3.0f;
}

//------------------------------------------------
//PlayerStepOn
//------------------------------------------------

// グラフィックデータの設定	内部でサイズも取得する
void PlayerStepOn::setGraph(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}
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
		if (m_pos.x > Game::kScreenWidth - m_graphSize.x)
		{
			m_pos.x = Game::kScreenWidth - m_graphSize.x;
		}
		m_pos.x += kSpeed;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_isRight = false;
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
		m_pos.x -= kSpeed;
	}
	m_vec.y += kGravity;

}


void PlayerStepOn::draw()
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
#include "SceneKnockDown.h"
namespace
{
	// X方向、Y方向の最大速度
	constexpr float kSpeedMax = 8.0f;
	constexpr float kAcc = 0.4f;

	//ショットの発射間隔
	constexpr int kShotInterval = 16;
}

PlayerKnockDown::PlayerKnockDown()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_shotInterval = 0;
}

void PlayerKnockDown::setGraph(int handle, int index)
{
	m_handle[index] = handle;
}
// 初期設定
void PlayerKnockDown::setup()
{
	m_pos.x = Game::kScreenWidth / 2 - kGraphicSizeX / 2;
	m_pos.y = Game::kScreenHeight - kGraphicSizeY;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_shotVec.x = 0.0f;
	m_shotVec.y = 0.0f;

	m_startPos = getCenter();

	m_shotInterval = 0;
}

void PlayerKnockDown::update()
{
	if (m_isDead)	return;

	m_pos += m_vec;

	// キー入力処理 左右に移動 ジャンプ
	Pad::update();

	/*
	//ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0)	m_shotInterval = 0;

	if (m_shotInterval <= 0 && m_isRight)
	{
		if (Pad::isPress(PAD_INPUT_2))
		{
			if (m_pScene->createShotNormal(m_startPos))
			{
				m_shotInterval = kShotInterval;
			}
			//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
		if (Pad::isPress(PAD_INPUT_3))
		{
			if (m_pScene->createShotBound(m_startPos))
			{
				m_shotInterval = kShotInterval;
			}
			//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
		if (Pad::isPress(PAD_INPUT_4))
		{
			if (m_pScene->createShotSin(m_startPos))
			{
				m_shotInterval = kShotInterval;
			}
			//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
	}
	*/
	
	//xでショット
	m_shotInterval--;
	if (m_shotInterval < 0)	m_shotInterval = 0;
	if (m_shotInterval <= 0)
	{
		if (Pad::isPress(PAD_INPUT_2))
		{
			if (m_pMain->createShot(getStartPos()))
			{
				m_shotInterval = kShotInterval;
			}
			//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
	}
	
	//移動
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_shotVec.x = kSpeed;
		m_shotVec.y = 0.0f;
		if (m_pos.x > Game::kScreenWidth - getRadius() * 2)
		{
			m_pos.x = Game::kScreenWidth - getRadius() * 2;
		}
		m_animeNo = 3;
		m_pos.x += kSpeed;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_shotVec.x = kSpeed;
		m_shotVec.y = 0.0f;
		if (m_pos.x < 0.0f)
		{
			m_pos.x = 0.0f;
		}
		m_animeNo = 2;
		m_pos.x -= kSpeed;
	}
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_shotVec.x = 0.0f;
		m_shotVec.y = kSpeed;
		if (m_pos.y < 0.0f)
		{
			m_pos.y = 0.0f;
		}
		m_animeNo = 0;
		m_pos.y -= kSpeed;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_shotVec.x = 0.0f;
		m_shotVec.y = kSpeed;
		if (m_pos.y > Game::kScreenHeight - getRadius() * 2)
		{
			m_pos.y = Game::kScreenHeight - getRadius() * 2;
		}
		m_animeNo = 1;
		m_pos.y += kSpeed;
	}
}
void PlayerKnockDown::draw()
{
	if (m_isDead)	return;
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);

	DrawFormatString(0, 20, GetColor(255, 255, 255), "player.x%3f y%3f", m_pos.x, m_pos.y);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "player.strt.x%3f y%3f", m_startPos.x,m_startPos.y);

	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y),
		static_cast<int>(getRadius()), GetColor(255, 255, 255), false);
}

//当たり判定の半径取得
float PlayerKnockDown::getRadius() const
{
	//画像の半径
	return kGraphicSizeX / 2;
}
//当たり判定の中心位置取得
Vec2 PlayerKnockDown::getCenter() const
{
	//当たり判定の中心位置
	Vec2 result = m_pos;
	result.x += kGraphicSizeX / 2;
	result.y += kGraphicSizeY / 2;

	return result;
}