#include "SceneTitle.h"
#include "DxLib.h"
#include "game.h"
#include "SceneStepOn.h"
#include "SceneKnockDown.h"
#include "Pad.h"

namespace
{
	//�T�E���h
	const char* const kSelectionSoundName = "sound/selection.mp3";	//�I��
	const char* const kBgmSoundName = "sound/bgmTitle.mp3";			//BGM
}

void SceneTitle::init()
{
	//�t�F�[�h
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	//�T�E���h�擾
	m_hSelectionSe = LoadSoundMem(kSelectionSoundName);
	m_hBgmSound = LoadSoundMem(kBgmSoundName);

	m_selection = 0;
	
	//BGM�Đ�
	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}

void SceneTitle::end()
{
	//�T�E���h���~�߂�
	StopSoundMem(m_hSelectionSe);
	StopSoundMem(m_hBgmSound);
	//�폜
	DeleteSoundMem(m_hSelectionSe);
	DeleteSoundMem(m_hBgmSound);
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
		switch (m_selection)
		{
			case 0:return (new SceneStepOn);//StepOn�ɐ؂�ւ�
			case 1:return (new SceneKnockDown);//SceneKnockDown�ɐ؂�ւ�
		}

	}

	Pad::update();
	//�t�F�[�h�C�����I������Ƃ�
	if (m_fadeSpeed == 0)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			//�t�F�[�h�A�E�g���邽�߂Ɏ擾
			m_fadeSpeed = -8;
			m_selection = 0;
			//�I������I�񂾂特��炷
			PlaySoundMem(m_hSelectionSe, DX_PLAYTYPE_BACK, true);
		}
		else if (Pad::isPress(PAD_INPUT_2))
		{
			//�t�F�[�h�A�E�g���邽�߂Ɏ擾
			m_fadeSpeed = -8;
			m_selection = 1;
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
	DrawString(110, 100, " (A)z  ���݂���", GetColor(255, 255, 255));
	DrawString(110, 200, " (B)x  �z�R�����쒀����I�I", GetColor(255, 255, 255));
	DrawString(110, 300, " (LB)s  �I��", GetColor(255, 255, 255));
}