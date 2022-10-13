#pragma once
#include "Vec2.h"
#include "enemy.h"

class PlayerBase
{
public:
	PlayerBase()
	{
		m_handle = -1;
		m_fieldY = 0;
		m_isDead = false;
		m_isRight = true;
	}
	virtual ~PlayerBase(){}

	// グラフィックデータの設定	内部でサイズも取得する
	virtual void setGraph(int handle);
	// 初期設定
	virtual void setup(float fieldY){}

	virtual void update(){}
	virtual void draw();

public:
	//グラフィックハンドル
	int m_handle;
	// グラフィックの幅と高さ
	Vec2 m_graphSize;
	// 当たり判定の幅と高さ
	Vec2 m_colSize;
	//位置
	Vec2 m_pos;
	//ベクトル
	Vec2 m_vec;
	//地面の高さ
	float m_fieldY;
	//当たったかどうか
	bool m_isDead;
	//右を向いているかどうか
	bool m_isRight;
};

class PlayerStepOn : public PlayerBase
{
public:
	PlayerStepOn()
	{
		m_hJumpSe = -1;
	}
	virtual ~PlayerStepOn(){}

	// 初期設定	地面の高さを与える
	virtual void setup(float fieldY) override;

	virtual void update() override;

	void setJumpSe(int jumpSe) { m_hJumpSe = jumpSe; }

	// playerとの衝突判定
	bool isCol(EnemyStepOn& enemy);

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getColSize() const { return m_colSize; }

	// 死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }

private:
	int m_hJumpSe;

};

class PlayerKnockDown : public PlayerBase
{
public:
	PlayerKnockDown(){}
	virtual ~PlayerKnockDown(){}

	// 初期設定	地面の高さを与える
	virtual void setup(float fieldY) override;

	virtual void update() override;
private:

};