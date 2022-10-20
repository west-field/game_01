#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneStepOn : public SceneBase
{
public:
	SceneStepOn();
	virtual ~SceneStepOn(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	int count(int wait);
private:
	//グラフィックハンドル
	int m_hPlayerGraph;
	int m_hEnemyGraph;
	//サウンド
	int m_hPlayerSound;
	int m_hEnemySound;
	int m_hBgmSound;
	//背景
	int m_hBackground;
	//カラー
	int m_color;
	//プレイヤー
	PlayerStepOn m_player;
	//エネミー
	EnemyStepOn m_enemy;

};