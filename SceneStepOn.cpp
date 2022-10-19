#include "SceneStepOn.h"
#include "DxLib.h"
#include "game.h"
#include "SceneKnockDown.h"

namespace
{
	//グラフィックファイル名
	const char* const kPlayerGraphName = "data/playerStepOn.bmp";
	const char* const kEnemyGraphName = "data/enemyStepOn.bmp";
	//サウンドファイル名
	const char* const kPlayerSoundName = "sound/player_jump.mp3";
	const char* const kEnemySoundName = "sound/enemy_damage.mp3";
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

	m_hBackground = -1;
}
void SceneStepOn::init()
{
	//グラフィック
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	//サウンド
	m_hPlayerSound = LoadSoundMem(kPlayerSoundName);
	m_hEnemySound = LoadSoundMem(kEnemySoundName);
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
}
void SceneStepOn::end()
{
	//グラフィック削除
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
	//サウンド削除
	DeleteSoundMem(m_hPlayerSound);
	DeleteSoundMem(m_hEnemySound);
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
	//当たり判定 playerがenemyに上から当たったかどうか
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
			//次の画面に行く
			return (new SceneKnockDown);
		}
	}

	return this;
}
void SceneStepOn::draw()
{
	//フェード
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// 地面の描画
	DrawGraph(0, 0, m_hBackground, false);
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_enemy.draw();

	//始まるまでの時間中に表示する文字
	if (m_waitStart != 0)
	{
		DrawString(340, 200, "ふめ", GetColor(255, 255, 255));
		DrawString(300, 220, "←・→キーで移動", GetColor(255, 255, 255));
		//m_timeが0の時　スタートを表示
		if (m_time <= 0)
		{
			DrawString(Game::kScreenWidth - 100, Game::kScreenHeight - 50,
				"スタート!!", GetColor(255, 255, 255));
		}
		else
		{
			DrawFormatString(Game::kScreenWidth - 100, Game::kScreenHeight - 50,
				GetColor(255, 255, 255), "..%d", m_time);
		}
	}
	//クリアしたときに表示する文字
	if (m_isSuccess)
	{
		DrawString(300, 200, "成功！", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255),"次へ..%d", m_time);
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