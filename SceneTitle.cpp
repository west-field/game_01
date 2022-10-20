#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneStepOn.h"
#include "SceneKnockDown.h"
#include "Pad.h"

namespace
{
	const char* const kSelectionSoundName = "sound/selection.mp3";
	const char* const kBgmSoundName = "sound/bgmTitle.mp3";
}

void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	//サウンド取得
	m_hSelectionSe = LoadSoundMem(kSelectionSoundName);
	m_hBgmSound = LoadSoundMem(kBgmSoundName);
	m_selection = 0;

	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}

void SceneTitle::end()
{
	StopSoundMem(m_hSelectionSe);
	StopSoundMem(m_hBgmSound);
	//削除
	DeleteSoundMem(m_hSelectionSe);
	DeleteSoundMem(m_hBgmSound);
}

SceneBase* SceneTitle::update()
{
	m_fadeBright += m_fadeSpeed;
	//フェードイン
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	//フェードアウト
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//フェードアウトしきったら次のシーンへ
		m_fadeBright = 0;
		switch (m_selection)
		{
			case 0:return (new SceneStepOn);//StepOnに切り替え
			case 1:return (new SceneKnockDown);//SceneKnockDownに切り替え
		}

	}

	Pad::update();
	//フェードインし終わったとき
	if (m_fadeSpeed == 0)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			//フェードアウトするために取得
			m_fadeSpeed = -8;
			m_selection = 0;
			//選択肢を選んだら音を鳴らす
			PlaySoundMem(m_hSelectionSe, DX_PLAYTYPE_BACK, true);
		}
		else if (Pad::isPress(PAD_INPUT_2))
		{
			//フェードアウトするために取得
			m_fadeSpeed = -8;
			m_selection = 1;
			//選択肢を選んだら音を鳴らす
			PlaySoundMem(m_hSelectionSe, DX_PLAYTYPE_BACK, true);
		}
	}
	
	return this;
}
void SceneTitle::draw()
{
	//フェード
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);//描画輝度をセット
	//文字表示
	DrawString(200, 100, "タイトル画面", GetColor(255, 255, 255));
	DrawString(110, 300, " z(A) 踏みつけろ", GetColor(255, 255, 255));
	DrawString(110, 340, " x(B) ホコリを駆逐せよ！！", GetColor(255, 255, 255));
	DrawString(110, 380, " Q(BACK) 終了", GetColor(255, 255, 255));
}