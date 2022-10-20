#include "SceneBase.h"

SceneBase::SceneBase()
{
	//移動開始までの待ち時間(フレーム数)
	m_waitStart = 0;
	//時間を表示
	m_time = 0;
	//成功したかどうか
	m_isSuccess = false;
	//失敗したかどうか
	m_isMis = false;
	//フェード処理
	m_fadeBright = 0;
	//フェード速度
	m_fadeSpeed = 0;
}