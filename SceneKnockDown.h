#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"
#include "ShotBase.h"
#include <vector>

class SceneKnockDown : public SceneBase
{
public:
	SceneKnockDown();
	virtual ~SceneKnockDown(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	//弾の生成
	bool createShotNormal(Vec2 pos);
	bool createShotBound(Vec2 pos);
	bool createShotSin(Vec2 pos);
private:
	//プレイヤー
	PlayerKnockDown m_player;
	//エネミー
	EnemyKnockDown m_enemy;
	//ショット
	std::vector<ShotBase*> m_pShotVt;
	//グラフィックハンドル
	int m_hPlayerGraph;
	int m_hEnemyGraph;
	int m_hShotGraph;
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