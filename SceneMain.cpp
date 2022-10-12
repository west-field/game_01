#include "SceneMain.h"
#include "SceneTitle.h"
#include "DxLib.h"

void SceneMain::init()
{
	
}
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_2)//esc����������^�C�g����
	{
		return (new SceneTitle);
	}

	return this;
}
void SceneMain::draw()
{
	DrawString(0, 0, "���C�����", GetColor(255, 255, 255));
}