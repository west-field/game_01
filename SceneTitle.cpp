#include "SceneTitle.h"
#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"
#include "SceneStepOn.h"

void SceneTitle::init()
{
	m_fadeBright = 0;
	m_fadeSpeed = 8;
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
		//�t�F�[�h�A�E�g���������玟�̃V�[����
		m_fadeBright = 0;
		//StepOn�ɐ؂�ւ�
		return (new SceneStepOn);
	}

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (m_fadeSpeed == 0)
	{
		if (padState & PAD_INPUT_1)
		{
			m_fadeSpeed = -8;
		}
	}
	
	return this;
}
void SceneTitle::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);//�`��P�x���Z�b�g
	DrawString(200, 100, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(110, 300, " z�L�[�������ăX�^�[�g esc�L�[�������ďI��", GetColor(255, 255, 255));
}