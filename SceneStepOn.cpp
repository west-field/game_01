#include "SceneStepOn.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerStepOn.bmp";
	const char* const kEnemyGraphName = "data/enemyStepOn.bmp";
	//サウンドファイル名
	const char* const kPlayerSoundName = "sound/player_jump.mp3";
	const char* const kEnemySoundName = "sound/enemy_damage.mp3";
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
	m_waitEnd = kWaitEnd;
	m_time = 3;
	//フェード
	m_fadeBright = 0;
	m_fadeSpeed = 8;

	m_color = GetColor(255, 255, 255);//白

	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}
void SceneStepOn::end()
{
	StopSoundMem(m_hPlayerSound);
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

	m_player.update();
	m_enemy.update();
	//当たり判定 playerがenemyを踏んだかどうか
	if (m_player.isCol(m_enemy))
	{
		m_enemy.setHit(true);
		m_isSuccess = true;
	}

	//クリアしたら画面を変更できる
	if (m_isSuccess)
	{
		//次に行くまでの待ち時間
		if (m_waitEnd > 0)
		{
			m_waitEnd--;
			m_time = count(m_waitEnd);
			return this;
		}
		else
		{
			//タイトル画面に行く
			return (new SceneTitle);
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
		DrawString(340, 200, "踏みつけろ", m_color);
		DrawString(300, 220, "←・→キーで移動", m_color);
		//m_timeが0の時　スタートを表示
		if (m_time <= 0)
		{
			DrawString(300, 240,"スタート!!", m_color);
		}
		else
		{
			DrawFormatString(300, 240, m_color, "..%d", m_time);
		}
	}
	//クリアしたときに表示する文字
	if (m_isSuccess)
	{
		DrawString(300, 200, "成功！", m_color);
		DrawFormatString(300, 220, m_color,"タイトルへ..%d", m_time);
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