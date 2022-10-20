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
public:
	//カウント
	int count(int wait);
	//弾の生成
	bool createShot(Vec2 pos,Vec2 vec);
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
	//サウンドハンドル
	int m_hShotSound;	//ショット
	int m_hEnemySound;	//エネミー
	int m_hBgmSound;	//BGM
	int m_hSuccessSound;//成功
	int m_hMisSound;	//失敗
	//背景
	int m_hBackground;
	//色
	int m_color;
};