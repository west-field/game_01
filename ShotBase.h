#pragma once

#include "Vec2.h"

class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	void setHandle(int handle) { m_handle = handle; }

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();	//update() = 0;	完全仮想関数にするのもok
	// 表示
	virtual void draw();

	//存在するか
	bool isExist() const { return m_isExist; }

protected:
	// グラフィックハンドル
	int m_handle;
	// 表示位置
	Vec2	m_pos;
	// 移動
	Vec2	m_vec;

	//存在するか
	bool m_isExist;
};