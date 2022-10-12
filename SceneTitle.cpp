#include "SceneTitle.h"
#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"
#include "SceneStepOn.h"

SceneBase* SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		//StepOn�ɐ؂�ւ�
		return (new SceneStepOn);
	}
	return this;
}
void SceneTitle::draw()
{
	DrawString(200, 100, "�^�C�g�����", GetColor(255, 255, 255));
	DrawString(110, 300, " z�L�[�������ăX�^�[�g esc�L�[�������ďI��", GetColor(255, 255, 255));
}