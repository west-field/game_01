#include "Pad.h"
#include "DxLib.h"

namespace
{
	constexpr int kLogNum = 16;
	//入力ログ 0が最新
	int padLog[kLogNum];
}

namespace Pad
{
	//パッドの入力状態取得
	void update()
	{
		//現在のパッドの状況を取得
		int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		//ログの更新
		for (int i = kLogNum - 1; i >= 1; i--)
		{
			padLog[i] = padLog[i - 1];
		}
		//最新の状態を入れる
		padLog[0] = padState;
	}

	//押し上げ判定
	bool isPress(int button)
	{
		return  (padLog[0] & button);
	}

	//トリガー判定
	bool isTrigger(int button)
	{
		bool isNow = (padLog[0] & button);//現在の状態
		bool isLast = (padLog[1] & button);//1フレーム前の状態
		return (isNow && !isLast);//現在押されていて前のフレームで押されていなかった
	}

	//離した判定
	bool isRelase(int button)
	{
		bool isNow = (padLog[0] & button);//現在の状態
		bool isLast = (padLog[1] & button);//1フレーム前の状態
		return (!isNow && isLast);//現在押されてなくて前のフレームは押されていた
	}
}