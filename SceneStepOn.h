#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneStepOn : public SceneBase
{
public:
	SceneStepOn()
	{
		m_hPlayer = -1;
		m_hEnemy = -1;
		m_waitFrame = 0;
		m_waitTime = 0;
		m_num = 0;
		m_transparent = 0;
		m_isSuccess = false;
	}
	virtual ~SceneStepOn(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	//グラフィックハンドル
	int m_hPlayer;
	int m_hEnemy;
	//プレイヤー
	Player m_player;
	//エネミー
	Enemy m_enemy;
	//移動開始までの待ち時間(フレーム数)
	int m_waitFrame;
	int m_waitTime;
	int m_num;
	//透明にする
	int m_transparent;
	//成功したかどうか
	bool m_isSuccess;
};