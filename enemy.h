#pragma once
#include "Vec2.h"
#include "player.h"

class Enemy
{
public:
	Enemy()
	{
		m_handle = -1;
		m_fieldY = 0.0f;
		m_isDead = false;
		m_isRight = false;
	}
	virtual ~Enemy(){}

	// グラフィックデータの設定	内部でサイズも取得する
	void setGraphic(int handle);

	// 初期設定	地面の高さを与える
	void setup(float fieldY);

	// 更新
	void update();
	// 描画
	void draw();

	// enemyとの衝突判定
	bool isCol(Player& player);

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getSize() const { return m_graphSize; }

	// 死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }

private:
	// グラフィックハンドル
	int m_handle;
	// グラフィックの幅と高さ
	Vec2 m_graphSize;
	// 当たり判定の幅と高さ
	Vec2 m_colSize;

	// 位置
	Vec2 m_pos;
	// ベクトル
	Vec2 m_vec;
	// 地面の高さ
	float m_fieldY;
	//当たったかどうか
	bool m_isDead;
	//右を向いているかどうか
	bool m_isRight;
};