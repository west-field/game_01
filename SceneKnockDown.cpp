#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"
#include "SceneTitle.h"
#include <cassert>

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerKnockDown.bmp";//プレイヤー
	const char* const kEnemyGraphName = "data/enemyKnockDown.bmp";	//エネミー
	const char* const kShotGraphName = "data/shot.bmp";				//ショット
	const char* const kBackgroundName = "data/backgroundKnockDown.bmp";//背景

	//サウンドファイル名
	const char* const kShotSoundName = "sound/shot.mp3";			//ショット
	const char* const kShotHitSoundName = "sound/shotHit.mp3";		//ヒット
	const char* const kBgmSoundName = "sound/bgmKnockDown.mp3";		//BGM
	const char* const kSuccessSoundName = "sound/success.mp3";		//成功
	const char* const kMisSoundName = "sound/mis.mp3";				//失敗
	const char* const kReflectionSoundName = "sound/reflection.mp3";//反射

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
	m_hBackground = -1;

	m_hShotSound = -1;
	m_hEnemySound = -1;
	m_hBgmSound = -1;
	m_hSuccessSound = -1;
	m_hMisSound = -1;
	m_hReflectionSound = -1;

	m_color = 0;

	m_count = 0;
}
void SceneKnockDown::init()
{
	//グラフィック
	LoadDivGraph(kPlayerGraphName, PlayerKnockDown::kGraphicDivNum,
		PlayerKnockDown::kGraphicDivX, PlayerKnockDown::kGraphicDivY,
		PlayerKnockDown::kGraphicSizeX, PlayerKnockDown::kGraphicSizeY, m_hPlayerGraph);//プレイヤーグラフィック
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);	//エネミーグラフィック
	m_hShotGraph = LoadGraph(kShotGraphName);	//ショットグラフィック
	m_hBackground = LoadGraph(kBackgroundName);	//背景

	//サウンド
	m_hShotSound = LoadSoundMem(kShotSoundName);			//ショット
	m_hEnemySound = LoadSoundMem(kShotHitSoundName);		//エネミーhit
	m_hBgmSound = LoadSoundMem(kBgmSoundName);				//BGM
	m_hSuccessSound = LoadSoundMem(kSuccessSoundName);		//成功
	m_hMisSound = LoadSoundMem(kMisSoundName);				//失敗
	m_hReflectionSound = LoadSoundMem(kReflectionSoundName);//反射
	
	//プレイヤー
	for (int i = 0; i < PlayerKnockDown::kGraphicDivNum; i++)
	{
		m_player.setGraph(m_hPlayerGraph[i],i);
	}
	m_player.setup();
	m_player.setShotSe(m_hShotSound);
	m_player.setMain(this);
	
	//エネミー
	float posX = 0.0f;
	for (auto& enemy : m_enemy)
	{
		enemy.setGraph(m_hEnemyGraph);
		enemy.setup(posX);
		enemy.setDamageSe(m_hEnemySound);
		enemy.setReflectionSe(m_hReflectionSound);
		posX += 80.0f;
	}
	
	//待ち時間
	m_waitTime = kWaitTime;
	m_time = 3;
	
	//フェード
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	
	//色
	m_color = GetColor(0, 0, 128);//ネイビー
	
	//カウント
	m_count = 0;
	
	//Bgmを再生
	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}
void SceneKnockDown::end()
{
	//サウンドを止める
	StopSoundMem(m_hShotSound);
	StopSoundMem(m_hSuccessSound);
	StopSoundMem(m_hMisSound);
	StopSoundMem(m_hReflectionSound);

	//画像,音のアンロード
	for (auto& handle : m_hPlayerGraph)
	{
		DeleteGraph(handle);
	}
	
	for (auto& enemy : m_enemy)
	{
		DeleteGraph(m_hEnemyGraph);
		DeleteSoundMem(m_hEnemySound);
		DeleteSoundMem(m_hReflectionSound);
	}

	DeleteGraph(m_hShotGraph);
	DeleteGraph(m_hBackground);

	DeleteSoundMem(m_hShotSound);
	DeleteSoundMem(m_hBgmSound);
	DeleteSoundMem(m_hSuccessSound);
	DeleteSoundMem(m_hMisSound);

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
	if (m_waitTime > 0)
	{
		m_waitTime--;
		
		m_time = m_waitTime / 60;

		return this;
	}

	//フェードアウト
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//フェードアウトしきったら次のシーンへ
		m_fadeBright = 0;
		return (new SceneTitle);
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
		if (m_enemy[i].isDead() || m_player.isDead())	continue;
		Vec2 dist = m_enemy[i].getCenter() - m_player.getCenter();
		float radiusAdd = m_enemy[i].getRadius() + m_player.getRadius();
		//当たった場合
		if (dist.length() < radiusAdd)
		{
			m_player.setDead(true);
			//ミス
			m_isMis = true;
			StopSoundMem(m_hBgmSound);
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
			StopSoundMem(m_hBgmSound);
		}
	}

	//音を一回だけ鳴らす
	if (m_count == 0)
	{
		if (m_isSuccess)//成功時
		{
			PlaySoundMem(m_hSuccessSound, DX_PLAYTYPE_BACK, true);
			m_count++;
		}
		else if (m_isMis)//失敗時
		{
			PlaySoundMem(m_hMisSound, DX_PLAYTYPE_BACK, true);
			m_count++;
		}
	}

	//クリア、ミスしたらボタンを押して画面を変更
	Pad::update();
	if (m_fadeSpeed == 0)
	{
		if (m_isSuccess || m_isMis)
		{
			if (Pad::isPress(PAD_INPUT_7))
			{
				m_fadeSpeed = -8;
			}
		}
	}
	return this;
}
void SceneKnockDown::draw()
{
	//フェード
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	//背景を表示
	DrawGraph(0, 0, m_hBackground, false);
	
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
	if (m_waitTime != 0)
	{
		DrawString(200, 220, "←・→キーで移動 x(B)でショット", m_color);
		//m_timeが0の時　スタートを表示
		if (m_time <= 0)
		{
			DrawString(200, 240,"スタート!!", m_color);
		}
		else
		{
			DrawFormatString(200, 240, m_color, "始まるまで..%d", m_time);
		}
	}
	//クリアの時
	if (m_isSuccess)
	{
		DrawString(300, 200, "駆逐完了！", m_color);
		DrawString(300, 220, "(BACK)Q  タイトルへ", m_color);
	}
	//ミスの時
	else if(m_isMis)
	{
		DrawString(300, 200, "駆逐失敗", m_color);
		DrawString(300, 220, "(BACK)Q  タイトルへ", m_color);
	}
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