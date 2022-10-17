#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include <vector>

namespace
{
	constexpr int kEnemyNum = 6;
}

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
	bool createShot(Vec2 pos);
private:
	//プレイヤー
	PlayerKnockDown m_player;
	//エネミー
	EnemyKnockDown m_enemy [kEnemyNum] ;
	//ショット
	std::vector<Shot*> m_pShotVt;
	//グラフィックハンドル
	int m_hPlayerGraph[PlayerKnockDown::kGraphicDivNum];
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