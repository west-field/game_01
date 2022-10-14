#pragma once

#include "ShotBase.h"

class ShotBound : public ShotBase
{
public:
	ShotBound() { m_boundCount = 0; }
	virtual ~ShotBound() {}

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();	//update() = 0;	完全仮想関数にするのもok

private:
	//跳ね返った回数
	int m_boundCount;
};