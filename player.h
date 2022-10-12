#pragma once

#include "Vec2.h"

class Player
{
public:
	Player()
	{
		m_handle = -1;
		m_fieldY = 0.0f;
		m_isRight = true;
	}
	virtual ~Player(){}

	// グラフィックデータの設定	内部でサイズも取得する
	void setGraphic(int handle);
	// 初期設定	地面の高さを与える
	void setup(float fieldY);

	void update();
	void draw();

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getColSize() const { return m_colSize; }

private:
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
	//右を向いているかどうか
	bool m_isRight;
};