#pragma once
#include "Vec2.h"

class EnemyBase
{
public:
	EnemyBase()
	{
		m_handle = -1;
		m_fieldY = 0;

		m_isDead = false;
		m_isRight = false;
	}
	virtual ~EnemyBase(){}

	// グラフィックデータの設定	内部でサイズも取得する
	virtual void setGraph(int handle);
	// 初期設定
	virtual void setup(float fieldY) {}

	virtual void update(){}
	virtual void draw();

public:
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

class EnemyStepOn : public EnemyBase
{
public:
	EnemyStepOn()
	{
		m_hDamageSe = -1;
	}
	virtual ~EnemyStepOn(){}
	
	// 初期設定
	virtual void setup(float fieldY)override;

	// 更新
	virtual void update()override;

	void setDamageSe(int damageSe) { m_hDamageSe = damageSe; }

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getColSize() const { return m_graphSize; }

	// 死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }

private:
	int m_hDamageSe;

};

class EnemyKnockDown : public EnemyBase
{
public:

	// 初期設定
	virtual void setup(float fieldY)override;

	// 更新
	virtual void update()override;
private:
};