#include "player.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"

namespace
{
	//ジャンプ力
	constexpr float kJumpAcc = -15.0f;
	//重力
	constexpr float kGravity = 0.5f;
	//移動速度
	constexpr float kSpeed = 3.0f;
}

//-----------------------------------------------★
//PlayerStepOn
//------------------------------------------------

// グラフィックデータの設定	内部でサイズも取得する
void PlayerStepOn::setGraph(int handle)
{
	m_handle = handle;
	//サイズ取得
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}
// 初期設定	地面の高さを与える
void PlayerStepOn::setup(float fieldY)
{
	//地面
	m_fieldY = fieldY;
	
	//初期位置
	m_pos.x = 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	//移動
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
	//プレイヤーの動き　地面についていたらジャンプする
	if (isField)
	{
		//ジャンプ開始
		m_vec.y = kJumpAcc;
		//ジャンプ音を鳴らす
		PlaySoundMem(m_hJumpSe, DX_PLAYTYPE_BACK, true);
	}

	// キー入力処理 左右に移動
	Pad::update();
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_isRight = true;//右を向いている
		//壁に当たったら止める
		if (m_pos.x > Game::kScreenWidth - m_colSize.x)
		{
			m_pos.x = Game::kScreenWidth - m_colSize.x;
		}
		m_pos.x += kSpeed;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_isRight = false;//右を向いていない

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
	//右を向いているときは右を向いた絵を表示する
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

//衝突判定
bool PlayerStepOn::isCol(EnemyStepOn& enemy)
{
	if (m_isDead)	return false;

	//プレイヤーの当たり判定 左、右、上、下
	float playerLeft = getPos().x;
	float playerRight = getPos().x + m_colSize.x;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + m_colSize.y;

	//エネミーの当たり判定
	float enemyLeft = enemy.getPos().x + 5.0f;
	float enemyRight = enemy.getPos().x + enemy.getColSize().x + 5.0f;
	float enemyTop = enemy.getPos().y; + 2.0f;
	float enemyBottom = enemy.getPos().y + enemy.getColSize().y;

	//当たっていない
	if (playerLeft > enemyRight)	return false;//赤
	if (playerRight < enemyLeft)	return false;//黄色
	if (playerTop > enemyBottom)	return false;//緑
	if (playerBottom < enemyTop)	return false;//青

	//当たった
	return true;
}

//-----------------------------------------------★
//PlayerKnockDown
//------------------------------------------------
#include "SceneKnockDown.h"
namespace
{
	//ショットの発射間隔
	constexpr int kShotInterval = 20;
}

PlayerKnockDown::PlayerKnockDown()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}

	m_animeNo = 0;

	m_hShotSe = -1;

	m_shotInterval = 0;

	m_pMain = nullptr;
}

void PlayerKnockDown::setGraph(int handle, int index)
{
	m_handle[index] = handle;
}
// 初期設定
void PlayerKnockDown::setup()
{
	//初期位置
	m_pos.x = Game::kScreenWidth / 2 - kGraphicSizeX / 2;
	m_pos.y = Game::kScreenHeight / 2 + kGraphicSizeY;

	//移動
	m_vec.x = kSpeed;
	m_vec.y = kSpeed;
	
	//ショットの発射位置
	m_startPos = m_pos;

	//ショット方向
	m_shotVec.x = 0.0f;
	m_shotVec.y = -kSpeed;

	//ショット発射間隔
	m_shotInterval = 0;
}

void PlayerKnockDown::update()
{
	if (m_isDead)	return;

	Pad::update();

	//x(B)でショット
	m_shotInterval--;
	if (m_shotInterval < 0)	m_shotInterval = 0;

	//ショットの発射間隔が0になったときもう一度発射できる
	if (m_shotInterval <= 0)
	{
		if (Pad::isPress(PAD_INPUT_2))
		{
			//弾を生成する
			if (m_pMain->createShot(m_startPos, m_shotVec))
			{
				m_shotInterval = kShotInterval;
			}
			//ショット音を再生
			PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
	}
	
	//移動 上下左右
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_pos.x += m_vec.x;
		m_shotVec.x = m_vec.x;
		m_shotVec.y = 0.0f;
		if (m_pos.x > Game::kScreenWidth - getRadius() * 2)
		{
			m_pos.x = Game::kScreenWidth - getRadius() * 2;
		}
		m_animeNo = 3;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_pos.x -= m_vec.x;
		m_shotVec.x = -m_vec.x;
		m_shotVec.y = 0.0f;
		if (m_pos.x < 0.0f)
		{
			m_pos.x = 0.0f;
		}
		m_animeNo = 2;
	}
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos.y -= m_vec.y;
		m_shotVec.x = 0.0f;
		m_shotVec.y = -m_vec.y;
		if (m_pos.y < 0.0f)
		{
			m_pos.y = 0.0f;
		}
		m_animeNo = 0;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos.y += m_vec.y;
		m_shotVec.x = 0.0f;
		m_shotVec.y = m_vec.y;
		if (m_pos.y > Game::kScreenHeight - getRadius() * 2)
		{
			m_pos.y = Game::kScreenHeight - getRadius() * 2;
		}
		m_animeNo = 1;
	}

	m_startPos = m_pos;
}

void PlayerKnockDown::draw()
{
	if (m_isDead)	return;
	//方向に応じた絵を表示
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}

float PlayerKnockDown::getRadius() const
{
	//画像の半径
	return kGraphicSizeX / 2;
}

Vec2 PlayerKnockDown::getCenter() const
{
	//当たり判定の中心位置
	Vec2 result = m_pos;
	result.x += kGraphicSizeX / 2;
	result.y += kGraphicSizeY / 2;

	return result;
}