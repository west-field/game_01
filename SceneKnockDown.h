#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneKnockDown : public SceneBase
{
public:
	SceneKnockDown();
	virtual ~SceneKnockDown(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;
private:
	PlayerKnockDown m_player;
	EnemyKnockDown m_enemy;
	//グラフィックハンドル
	int m_hPlayerGraph;
	int m_hEnemyGraph;
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