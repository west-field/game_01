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
	int m_hPlayerGraph;	//プレイヤーグラフィック
	int m_hEnemyGraph;	//エネミーグラフィック
	//サウンド
	int m_hPlayerSound;	//playerに渡す
	int m_hEnemySound;	//enemyに渡す
	int m_hBgmSound;	//BGM
	//背景
	int m_hBackground;
	//カラー
	int m_color;
	//プレイヤー
	PlayerStepOn m_player;
	//エネミー
	EnemyStepOn m_enemy;

};