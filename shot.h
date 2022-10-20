#pragma once

#include "Vec2.h"

class Shot
{
public:
	Shot();
	virtual ~Shot(){}

	//グラフィックデータの設定
	void setHandle(int handle);
	//ショット開始位置を取得
	virtual void start(Vec2 pos, Vec2 vec);
	// 更新
	virtual void update();
	// 表示
	virtual void draw();

	//存在するか
	bool isExist() const { return m_isExist; }
	//存在するかどうかの取得
	void setExist(bool isExist) { m_isExist = isExist; }
	//当たり判定の半径取得
	float getRadius() const;
	//当たり判定の中心位置取得
	Vec2 getCenter() const;
protected:
	// グラフィックハンドル
	int m_handle;
	//グラフィックの幅と高さ
	Vec2 m_graphSize;
	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

	//存在するか
	bool m_isExist;
};