#pragma once

#include "ShotBase.h"

class ShotSin : public ShotBase
{
public:
	ShotSin()
	{
		m_sinRate = 0.0f;
		m_moveHeight = 0.0f;
	}
	virtual ~ShotSin()
	{
	}

	// ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
private:

	Vec2	m_basePos;
	float	m_sinRate;
	float	m_moveHeight;
};