#pragma once
#include "Vec2.h"

class EnemyBase
{
public:
	EnemyBase()
	{
		m_handle = -1;
		m_hDamageSe = -1;
		m_isHit = false;
		m_isDead = false;
		m_isRight = false;
	}
	virtual ~EnemyBase(){}

	virtual void setGraph(int handle){}
	virtual void setup() {}
	virtual void update(){}
	virtual void draw(){}

	//ダメージ音を取得
	virtual void setDamageSe(int damageSe) { m_hDamageSe = damageSe; }
	// 当たったかどうか
	virtual void setHit(bool isHit) { m_isHit = isHit; }
	//生死の取得
	bool isDead() { return m_isDead;}
	// 位置の取得
	virtual Vec2 getPos() const { return m_pos; }
	// サイズの取得
	virtual Vec2 getColSize() const { return m_graphSize; }

protected:
	// グラフィックハンドル
	int m_handle;
	//ダメージ音
	int m_hDamageSe;
	// グラフィックの幅と高さ
	Vec2 m_graphSize;
	// 当たり判定の幅と高さ
	Vec2 m_colSize;
	// 位置
	Vec2 m_pos;
	// ベクトル
	Vec2 m_vec;
	//当たったかどうか
	int m_isHit;
	//生死
	bool m_isDead;
	//右を向いているかどうか
	bool m_isRight;
};


//-----------------------------------------------★
//EnemyStepOn
//------------------------------------------------
class EnemyStepOn : public EnemyBase
{
public:
	EnemyStepOn()
	{
		m_fieldY = 0;
	}
	virtual ~EnemyStepOn(){}
	
	// グラフィックデータの設定	内部でサイズも取得する
	virtual void setGraph(int handle)override;
	// 初期設定
	virtual void setup(float fieldY);
	// 更新
	virtual void update()override;
	//表示
	virtual void draw()override;

private:
	// 地面の高さ
	float m_fieldY;
};


//-----------------------------------------------★
//EnemyKnockDown
//------------------------------------------------
class EnemyKnockDown : public EnemyBase
{
public:
	EnemyKnockDown(){}
	virtual ~EnemyKnockDown(){}

	// グラフィックデータの設定	内部でサイズも取得する
	virtual void setGraph(int handle)override;
	// 初期設定
	virtual void setup(float posX);
	// 更新
	virtual void update()override;
	//表示
	virtual void draw()override;
	
public:
	//当たり判定の半径取得
	float getRadius() const;
	//当たり判定の中心位置取得
	Vec2 getCenter() const;
	//ほかの敵に当たった場合の反射処理
	void bound(Vec2 targetPos);
private:
};