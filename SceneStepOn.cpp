#include "SceneStepOn.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"
#include "SceneTitle.h"

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerStepOn.bmp";
	const char* const kEnemyGraphName = "data/enemyStepOn.bmp";
	//サウンドファイル名
	const char* const kPlayerSoundName = "sound/playerJump.mp3";
	const char* const kEnemySoundName = "sound/enemyDamage.mp3";
	const char* const kBgmSoundName = "sound/bgmStepOn.mp3";
	// 地面の高さ
	constexpr int kFieldY = Game::kScreenHeight - 64;
	//背景
	const char* const kBackgroundName = "data/backgroundStepOn.bmp";
}

SceneStepOn::SceneStepOn()
{
	m_hPlayerGraph = -1;
	m_hEnemyGraph = -1;

	m_hPlayerSound = -1;
	m_hEnemySound = -1;
	m_hBgmSound = -1;

	m_hBackground = -1;

	m_color = 0;
}
void SceneStepOn::init()
{
	//グラフィック
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	//サウンド
	m_hPlayerSound = LoadSoundMem(kPlayerSoundName);
	m_hEnemySound = LoadSoundMem(kEnemySoundName);
	m_hBgmSound = LoadSoundMem(kBgmSoundName);
	//背景
	m_hBackground = LoadGraph(kBackgroundName);
	//player
	m_player.setGraph(m_hPlayerGraph);
	m_player.setup(kFieldY);
	m_player.setJumpSe(m_hPlayerSound);
	//enemy
	m_enemy.setGraph(m_hEnemyGraph);
	m_enemy.setup(kFieldY);
	m_enemy.setDamageSe(m_hEnemySound);
	//待ち時間
	m_waitStart = kWaitStart;
	m_time = 3;
	//フェード
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	//色
	m_color = GetColor(255, 255, 255);//白
	//BGMを再生
	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}
void SceneStepOn::end()
{
	//サウンドを止める
	StopSoundMem(m_hPlayerSound);
	StopSoundMem(m_hEnemySound);
	StopSoundMem(m_hBgmSound);
	//グラフィック削除
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
	//サウンド削除
	DeleteSoundMem(m_hPlayerSound);
	DeleteSoundMem(m_hEnemySound);
	DeleteSoundMem(m_hBgmSound);
	//背景削除
	DeleteGraph(m_hBackground);
}

SceneBase* SceneStepOn::update()
{
	//画面のフェードイン
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	//ゲームが始まるまでの時間
	if (m_waitStart > 0)
	{
		m_waitStart--;
		m_time = count(m_waitStart);
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
	m_enemy.update();
	//当たり判定 playerがenemyを踏んだかどうか
	if (m_player.isCol(m_enemy))
	{
		m_enemy.setHit(true);
		m_isSuccess = true;
	}

	//クリアしたらボタンを押して画面を変更
	Pad::update();
	if (m_fadeSpeed == 0)
	{
		if (m_isSuccess)
		{
			if (Pad::isPress(PAD_INPUT_7))
			{
				m_fadeSpeed = -8;
			}
		}
	}
	

	return this;
}
void SceneStepOn::draw()
{
	//フェード
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	//背景
	DrawGraph(0, 0, m_hBackground, false);
	
	m_player.draw();
	m_enemy.draw();

	//始まるまでの時間中に表示する文字
	if (m_waitStart != 0)
	{
		DrawString(200, 220, "←・→キーで移動", m_color);
		//m_timeが0の時　スタートを表示
		if (m_time <= 0)
		{
			DrawString(200, 240,"スタート!!", m_color);
		}
		else
		{
			DrawFormatString(200, 240, m_color, "..%d", m_time);
		}
	}
	//クリアしたときに表示する文字
	if (m_isSuccess)
	{
		DrawString(200, 200, "成功！", m_color);
		DrawString(200, 220,"(BACK)Q  タイトルへ", m_color);
	}
}
//カウント
int SceneStepOn::count(int wait)
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