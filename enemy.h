#pragma once
#include "Vec2.h"

class EnemyBase
{
public:
	EnemyBase()
	{
		m_handle = -1;
		m_fieldY = 0;
		m_isHit = false;
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

	// 当たったかどうか
	virtual void setHit(bool isHit) { m_isHit = isHit; }

	// 位置の取得
	virtual Vec2 getPos() const { return m_pos; }
	// サイズの取得
	virtual Vec2 getColSize() const { return m_graphSize; }

protected:
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
	int m_isHit;
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

public:
	//ダメージ音を取得
	void setDamageSe(int damageSe) { m_hDamageSe = damageSe; }

private:
	int m_hDamageSe;
};

class EnemyKnockDown : public EnemyBase
{
public:
	EnemyKnockDown(){}
	virtual ~EnemyKnockDown(){}
	// 初期設定
	virtual void setup(float fieldY)override;
	// 更新
	virtual void update()override;

	// 位置の取得
	virtual Vec2 getPos() const { return m_pos; }
	// サイズの取得
	virtual Vec2 getColSize() const { return m_graphSize; }
public:
#if false
	// shotとの衝突判定
	bool isCol(Shot& shot);
#endif
private:
};