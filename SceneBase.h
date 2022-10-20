#pragma once

class SceneBase
{
public:
	//始まるまでの時間
	int const kWaitStart = 60 * 3;
public:
	SceneBase();
	virtual ~SceneBase(){}

	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw(){}
protected:
	//移動開始までの待ち時間(フレーム数)
	int m_waitStart;
	//時間を表示
	int m_time;
	//成功したかどうか
	bool m_isSuccess;
	//失敗したかどうか
	bool m_isMis;
	//フェード処理
	int m_fadeBright;
	//フェード速度
	int m_fadeSpeed;
};