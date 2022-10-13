#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneStepOn : public SceneBase
{
public:
	SceneStepOn()
	{
		m_hPlayerGraph = -1;
		m_hEnemyGraph = -1;
		m_hPlayerSound = -1;
		m_hEnemySound = -1;
		m_waitFrame = 0;
		m_waitTime = 0;
		m_num = 0;
		m_isSuccess = false;
		m_fadeBright = 0;
		m_fadeSpeed = 0;
	}
	virtual ~SceneStepOn(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	//グラフィックハンドル
	int m_hPlayerGraph;
	int m_hEnemyGraph;
	//音
	int m_hPlayerSound;
	int m_hEnemySound;
	//プレイヤー
	PlayerStepOn m_player;
	//エネミー
	EnemyStepOn m_enemy;
	//移動開始までの待ち時間(フレーム数)
	int m_waitFrame;
	int m_waitTime;
	int m_num;

	//成功したかどうか
	bool m_isSuccess;
	//フェード処理
	int m_fadeBright;
	//フェード速度
	int m_fadeSpeed;
};