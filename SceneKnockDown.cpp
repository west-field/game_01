#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerStepOn.bmp";
	const char* const kEnemyGraphName = "data/enemyStepOn.bmp";

	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
	constexpr int kWaitTime = 60 * 4;
	constexpr int kWaitFrame = 60 * 2;
}

SceneKnockDown::SceneKnockDown()
{
	m_hPlayerGraph = -1;
	m_hEnemyGraph = -1;
	m_waitFrame = 0;
	m_waitTime = 0;
	m_num = 0;
	m_isSuccess = false;
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
void SceneKnockDown::init()
{
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);

	m_player.setGraph(m_hPlayerGraph);
	m_player.setup(kFieldY);

	m_enemy.setGraph(m_hEnemyGraph);
	m_enemy.setup(kFieldY);

	m_waitFrame = kWaitFrame;
	m_waitTime = kWaitTime;
	m_num = 3;

	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
void SceneKnockDown::end()
{
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
}

SceneBase* SceneKnockDown::update()
{
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return this;
	}

	m_player.update();
	m_enemy.update();
	m_isSuccess = true;
/*	if (m_enemy.isCol(m_player))
	{
		m_enemy.setDead(true);
		m_isSuccess = true;
	}
*/
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
void SceneKnockDown::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	m_player.draw();
	m_enemy.draw();

	DrawFormatString(230, 220, GetColor(255, 255, 255), "タイトルへ..%d", m_num);
}