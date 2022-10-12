#include "SceneStepOn.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
	constexpr int kWaitTime = 60 * 4;
	constexpr int kWaitFrame = 60 * 2;
}

void SceneStepOn::init()
{
	m_hPlayer = LoadGraph("data/player.bmp");
	m_hEnemy = LoadGraph("data/enemy.bmp");

	m_player.setGraphic(m_hPlayer);
	m_player.setup(kFieldY);

	m_enemy.setGraphic(m_hEnemy);
	m_enemy.setup(kFieldY);

	m_waitFrame = kWaitFrame;
	m_waitTime = kWaitTime;
	m_num = m_waitTime / 60;
	m_transparent = 255;
}
void SceneStepOn::end()
{
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hEnemy);
}

SceneBase* SceneStepOn::update()
{
	m_transparent -= 2;
	if (m_transparent <= 0)	m_transparent = 0;

	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return this;
	}

	m_player.update();
	m_enemy.update();

	if (m_enemy.isCol(m_player))
	{
		m_enemy.setDead(true);
		m_isSuccess = true;
	}

	//クリアしたら画面を変更できる
	if (m_isSuccess)
	{
		if (m_waitTime > 0)
		{
			m_waitTime--;

			if (m_waitTime <= 60)
			{
				m_num = 0;
			}
			else if (m_waitTime <= 120)
			{
				m_num = 1;
			}
			else if (m_waitTime <= 180)
			{
				m_num = 2;
			}
			else if (m_waitTime <= 240)
			{
				m_num = 3;
			}

			return this;
		}
		else
		{
			return (new SceneTitle);
		}
	}

	return this;
}
void SceneStepOn::draw()
{
	// 地面の描画
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_enemy.draw();

	if (m_waitFrame != 0)
	{
		DrawString(300, 200, "ふめ", GetColor(255, 255, 255));
	}
	if (m_isSuccess)
	{
		DrawString(300, 200, "成功！", GetColor(255, 255, 255));
		DrawFormatString(230, 220, GetColor(255, 255, 255),"タイトルに戻る..%d",m_num );
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_transparent);//◇半透明にする　0透明 ～ 255透明じゃない
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//◇元に戻す
}