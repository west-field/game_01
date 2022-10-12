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
		//StepOnに切り替え
		return (new SceneStepOn);
	}
	return this;
}
void SceneTitle::draw()
{
	DrawString(200, 100, "タイトル画面", GetColor(255, 255, 255));
	DrawString(110, 300, " zキーを押してスタート escキーを押して終了", GetColor(255, 255, 255));
}