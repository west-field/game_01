#pragma once

#include "Vec2.h"

class PlayerBase
{
public:
	PlayerBase()
	{
		m_handle = -1;
		m_fieldY = 0;
	}
	virtual ~PlayerBase(){}

	// グラフィックデータの設定	内部でサイズも取得する
	virtual void setGraphic(int handle){}
	// 初期設定
	virtual void setup(float fieldY){}

	virtual void update(){}
	virtual void draw() {}

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
};

class PlayerStepOn : public PlayerBase
{
public:
	PlayerStepOn()
	{
		m_hJumpSe = -1;
		m_isRight = true;
	}
	virtual ~PlayerStepOn(){}

	// グラフィックデータの設定	内部でサイズも取得する
	virtual void setGraphic(int handle) override;
	// 初期設定	地面の高さを与える
	virtual void setup(float fieldY) override;

	virtual void update() override;
	virtual void draw() override;

	void setJumpSe(int jumpSe) { m_hJumpSe = jumpSe; }

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getColSize() const { return m_colSize; }

private:
	int m_hJumpSe;
	//右を向いているかどうか
	bool m_isRight;
};