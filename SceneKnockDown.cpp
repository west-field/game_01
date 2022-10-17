#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include <cassert>

#include "shot.h"

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerKnockDown_02.bmp";
	const char* const kEnemyGraphName = "data/enemyKnockDown_01.bmp";
	const char* const kShotGraphName = "data/shot.bmp";

	constexpr int kWaitTime = 60 * 4;
	constexpr int kWaitFrame = 60 * 2;

	//ショットの発射間隔
	constexpr int kShotInterval = 16;
}

SceneKnockDown::SceneKnockDown()
{
	for (auto& handle : m_hPlayerGraph)
	{
		handle = -1;
	}
	m_hEnemyGraph = -1;
	m_hShotGraph = -1;

	m_waitFrame = 0;
	m_waitTime = 0;
	m_num = 0;

	m_isSuccess = false;

	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
void SceneKnockDown::init()
{
	//グラフィック
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	m_hShotGraph = LoadGraph(kShotGraphName);
	LoadDivGraph(kPlayerGraphName, PlayerKnockDown::kGraphicDivNum,
		PlayerKnockDown::kGraphicDivX, PlayerKnockDown::kGraphicDivY,
		PlayerKnockDown::kGraphicSizeX, PlayerKnockDown::kGraphicSizeY, m_hPlayerGraph);
	//プレイヤー
	for (int i = 0; i < PlayerKnockDown::kGraphicDivNum; i++)
	{
		m_player.setGraph(m_hPlayerGraph[i],i);
	}
	m_player.setup();
	//エネミー
	float posX = 0.0f;
	for (auto& enemy : m_enemy)
	{
		enemy.setGraph(m_hEnemyGraph);
		enemy.setup(posX);
		posX += 80.0f;
	}
	//待ち時間
	m_waitFrame = kWaitFrame;
	m_waitTime = kWaitTime;
	m_num = 3;
	//フェード
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
void SceneKnockDown::end()
{
	//画像のアンロード
	for (auto& handle : m_hPlayerGraph)
	{
		DeleteGraph(handle);
	}

	for (auto& enemy : m_enemy)
	{
		DeleteGraph(m_hEnemyGraph);
	}
	DeleteGraph(m_hShotGraph);
	
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;		//確保されていたらdelete
		pShot = nullptr;		//中身をnullptrに
	}
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
	for (auto& enemy : m_enemy)
	{
		enemy.update();
	}

	//enemyどうしの当たり判定
	for (int i = 0; i < kEnemyNum; i++)
	{
		for (int j = i + 1; j < kEnemyNum; j++)
		{
			Vec2 dist = m_enemy[i].getCenter() - m_enemy[j].getCenter();
			float radiusAdd = m_enemy[i].getRadius() + m_enemy[j].getRadius();
			//当たった場合
			if (dist.length() < radiusAdd)
			{
				m_enemy[i].bound(m_enemy[j].getCenter());
				m_enemy[j].bound(m_enemy[i].getCenter());
			}
		}
	}

	//playerに当たったかどうか
	for (int i = 0; i < kEnemyNum; i++)
	{
		Vec2 dist = m_enemy[i].getCenter() - m_player.getCenter();
		float radiusAdd = m_enemy[i].getRadius() + m_player.getRadius();
		//当たった場合
		if (dist.length() < radiusAdd)
		{
			m_player.setDead(true);
		}
	}
	std::vector<Shot*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

		if (!pShot)
		{
			it++;
			continue;//中身があるかどうか　nullptrの時continue
		}
		pShot->update(m_player.getStartVec());
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector要素の削除
			it = m_pShotVt.erase(it);
			continue;
		}

		it++;
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
void SceneKnockDown::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	m_player.draw();
	for (auto& enemy : m_enemy)
	{
		enemy.draw();
	}
	
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot)	continue;
		pShot->draw();
	}
	//現在存在している弾の数を表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "弾の数:%d", m_pShotVt.size());
	
	if (m_waitFrame != 0)
	{
		DrawString(340, 200, "すべて倒せ", GetColor(255, 255, 255));
		DrawString(200, 220, "←・→キーで移動 x(B)でショット", GetColor(255, 255, 255));
	}
	if (m_isSuccess)
	{
		DrawString(300, 200, "成功！", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255), "タイトルへ..%d", m_num);
	}
}
//弾の生成
bool SceneKnockDown::createShot(Vec2 pos)
{
	Shot* pShot = new Shot;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}