#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneStepOn.h"
#include "Pad.h"

#include "SceneKnockDown.h"

namespace
{
	const char* const kSelectionSoundName = "sound/selection.mp3";
}

void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	m_hSelectionSe = LoadSoundMem(kSelectionSoundName);
}

void SceneTitle::end()
{
	DeleteSoundMem(m_hSelectionSe);
}

SceneBase* SceneTitle::update()
{
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//フェードアウトしきったら次のシーンへ
		m_fadeBright = 0;
		//StepOnに切り替え
	//	return (new SceneStepOn);
		return (new SceneKnockDown);
	}

	Pad::update();
	if (m_fadeSpeed == 0)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			m_fadeSpeed = -8;
			PlaySoundMem(m_hSelectionSe, DX_PLAYTYPE_BACK, true);
		}
	}
	
	return this;
}
void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);//描画輝度をセット
	DrawString(200, 100, "タイトル画面", GetColor(255, 255, 255));
	DrawString(110, 300, " z(A)を押してスタート escを押して終了", GetColor(255, 255, 255));
}