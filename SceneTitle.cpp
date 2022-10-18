#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneStepOn.h"
#include "Pad.h"

namespace
{
	const char* const kSelectionSoundName = "sound/selection.mp3";
}

void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	//�T�E���h�擾
	m_hSelectionSe = LoadSoundMem(kSelectionSoundName);
}

void SceneTitle::end()
{
	//�폜
	DeleteSoundMem(m_hSelectionSe);
}

SceneBase* SceneTitle::update()
{
	m_fadeBright += m_fadeSpeed;
	//�t�F�[�h�C��
	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	//�t�F�[�h�A�E�g
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//�t�F�[�h�A�E�g���������玟�̃V�[����
		m_fadeBright = 0;
		//StepOn�ɐ؂�ւ�
		return (new SceneStepOn);
	}

	Pad::update();
	//�t�F�[�h�C�����I������Ƃ�
	if (m_fadeSpeed == 0)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			//�t�F�[�h�A�E�g���邽�߂Ɏ擾
			m_fadeSpeed = -8;
			//�I������I�񂾂特��炷
			PlaySoundMem(m_hSelectionSe, DX_PLAYTYPE_BACK, true);
		}
	}
	
	return this;
}
void SceneTitle::draw()
{
	//�t�F�[�h
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);//�`��P�x���Z�b�g
	//�����\��
	DrawString(200, 100, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(110, 300, " z(A)�������ăX�^�[�g esc�������ďI��", GetColor(255, 255, 255));
}