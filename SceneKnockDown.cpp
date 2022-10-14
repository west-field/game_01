#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include <cassert>

#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotSin.h"

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerKnockDown.bmp";
	const char* const kEnemyGraphName = "data/enemyKnockDown.bmp";
	const char* const kShotGraphName = "data/shot.bmp";
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
	constexpr int kWaitTime = 60 * 4;
	constexpr int kWaitFrame = 60 * 2;

	//ショットの発射間隔
	constexpr int kShotInterval = 16;
}

SceneKnockDown::SceneKnockDown()
{
	m_hPlayerGraph = -1;
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
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	m_hShotGraph = LoadGraph(kShotGraphName);

	m_player.setGraph(m_hPlayerGraph);
	m_player.setup(kFieldY);
	m_player.setScene(this);

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
	//画像のアンロード
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
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
	m_enemy.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

		if (!pShot)
		{
			it++;
			continue;//中身があるかどうか　nullptrの時continue
		}
		pShot->update();
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
#if false
	if (m_player.isCol(m_enemy))
	{
		m_player.setDead(true);
		m_isSuccess = true;
	}

	if (m_enemy.isCol(m_shot))
	{
		m_enemy.setHit(true);
		m_shot.setHit(true);
	}

#endif
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
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_enemy.draw();

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
		DrawString(200, 220, "←・→キーで移動 z(A)でジャンプ x(B)でショット", GetColor(255, 255, 255));
	}
	if (m_isSuccess)
	{
		DrawString(300, 200, "成功！", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255), "タイトルへ..%d", m_num);
	}
}

//弾の生成
bool SceneKnockDown::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}
bool SceneKnockDown::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}
bool SceneKnockDown::createShotSin(Vec2 pos)
{
	ShotSin* pShot = new ShotSin;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}