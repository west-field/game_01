#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include <cassert>

#include "shot.h"

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerKnockDown.bmp";
	const char* const kEnemyGraphName = "data/enemyKnockDown.bmp";
	const char* const kShotGraphName = "data/shot.bmp";

	//サウンドファイル名
//	const char* const kEnemySoundName = "";
//	const char* const kShotSoundName = "";
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

	m_hShotSound = -1;
	m_hEnemySound = -1;
}
void SceneKnockDown::init()
{
	//グラフィック
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	m_hShotGraph = LoadGraph(kShotGraphName);
	LoadDivGraph(kPlayerGraphName, PlayerKnockDown::kGraphicDivNum,
		PlayerKnockDown::kGraphicDivX, PlayerKnockDown::kGraphicDivY,
		PlayerKnockDown::kGraphicSizeX, PlayerKnockDown::kGraphicSizeY, m_hPlayerGraph);
	//サウンド
//	m_hEnemySound = LoadSoundMem(kEnemySoundName);
//	m_hShotSound = LoadSoundMem(kShotSoundName);
	//プレイヤー
	for (int i = 0; i < PlayerKnockDown::kGraphicDivNum; i++)
	{
		m_player.setGraph(m_hPlayerGraph[i],i);
	}
	m_player.setup();
//	m_player.setShotSe(m_hShotSound);
	m_player.setMain(this);
	//エネミー
	float posX = 0.0f;
	for (auto& enemy : m_enemy)
	{
		enemy.setGraph(m_hEnemyGraph);
		enemy.setup(posX);
//		enemy.setDamageSe(m_hEnemySound);
		posX += 80.0f;
	}
	//待ち時間
	m_waitStart = kWaitStart;
	m_waitEnd = kWaitEnd;
	m_time = 3;
	//フェード
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
void SceneKnockDown::end()
{
	//画像,音のアンロード
	for (auto& handle : m_hPlayerGraph)
	{
		DeleteGraph(handle);
	}
//		DeleteSoundMem(m_hEnemySound);
	
	for (auto& enemy : m_enemy)
	{
		DeleteGraph(m_hEnemyGraph);
//		DeleteSoundMem(m_hShotSound);
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
	//画面のフェードイン
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	//ゲームが始めるまでの時間
	if (m_waitStart > 0)
	{
		m_waitStart--;
		m_time = count(m_waitStart);
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
		if (m_enemy[i].isDead())	continue;
		for (int j = i + 1; j < kEnemyNum; j++)
		{
			if (m_enemy[j].isDead())	continue;
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
	//playerとenemy当たったかどうか
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (m_enemy[i].isDead())	continue;
		Vec2 dist = m_enemy[i].getCenter() - m_player.getCenter();
		float radiusAdd = m_enemy[i].getRadius() + m_player.getRadius();
		//当たった場合
		if (dist.length() < radiusAdd)
		{
			m_player.setDead(true);
			//ミス
			m_isMis = true;
		}
	}
	//shotとenemy当たったかどうか
	for (auto& pShot : m_pShotVt)
	{
		if (pShot != nullptr)
		{
			for (int i = 0; i < kEnemyNum; i++)
			{
				if (m_enemy[i].isDead())	continue;
				Vec2 dist = m_enemy[i].getCenter() - pShot->getCenter();
				float radiusAdd = m_enemy[i].getRadius() + pShot->getRadius();
				//当たった場合
				if (dist.length() < radiusAdd)
				{
					m_enemy[i].setHit(true);
					pShot->setExist(false);
				}
			}
		}
		
	}

	//ショット生成
	std::vector<Shot*>::iterator it = m_pShotVt.begin();
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

	//エネミーをすべて倒すとクリア
	int num = 0;
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (!m_enemy[i].isDead())	continue;
		num++;
		if (num == kEnemyNum)
		{
			m_isSuccess = true;
		}
	}
	//クリア、ミスしたとき
	if (m_isSuccess || m_isMis)
	{
		//終わるまでの時間
		if (m_waitEnd > 0)
		{
			m_waitEnd--;
			m_time = count(m_waitEnd);
			return this;
		}
		else
		{
			//タイトルに戻る
			return (new SceneTitle);
		}
	}

	return this;
}
void SceneKnockDown::draw()
{
	//フェード
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
	
	//スタートまでの時間中に表示
	if (m_waitStart != 0)
	{
		DrawString(300, 200, "ホコリを駆逐せよ！！", GetColor(255, 255, 255));
		DrawString(200, 220, "←・→キーで移動 x(B)でショット", GetColor(255, 255, 255));
		//m_timeが0の時　スタートを表示
		if (m_time <= 0)
		{
			DrawString(Game::kScreenWidth - 100, Game::kScreenHeight - 50,
				"スタート!!", GetColor(255, 255, 255));
		}
		else
		{
			DrawFormatString(Game::kScreenWidth - 150, Game::kScreenHeight - 50,
				GetColor(255, 255, 255), "始まるまで..%d", m_time);
		}
	}
	//クリアの時
	if (m_isSuccess)
	{
		DrawString(300, 200, "クリア！", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255), "タイトルへ戻る..%d", m_time);
	}
	//ミスの時
	else if(m_isMis)
	{
		DrawString(300, 200, "失敗", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255), "タイトルへ戻る..%d", m_time);
	}
}
//カウント
int SceneKnockDown::count(int wait)
{
	if (wait <= 60)
	{
		return 0;
	}
	else if (wait <= 120)
	{
		return 1;
	}
	else if (wait <= 180)
	{
		return 2;
	}
	else if (wait <= 240)
	{
		return 3;
	}
	return -1;
}

//弾の生成
bool SceneKnockDown::createShot(Vec2 pos,Vec2 vec)
{
	Shot* pShot = new Shot;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos,vec);
	m_pShotVt.push_back(pShot);

	return true;
}