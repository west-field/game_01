#include "DxLib.h"
#include "game.h"
#include "Pad.h"
#include "SceneManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	//ウィンドウ名設定
	SetMainWindowText(Game::kTitleText);
	//画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ●ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//★ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// 最初のシーンの初期化
	SceneManager scene;
	scene.init();

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		//画面のクリア
		ClearDrawScreen();

		scene.update();
		scene.draw();

		//★裏画面を表画面と入れ替える
		ScreenFlip();
		// S(LB)を押したら終了する
		Pad::update();
		if (Pad::isPress(PAD_INPUT_5))	break;
		//fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)	{}
	}

	scene.end();

	DxLib_End();				// ●ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}