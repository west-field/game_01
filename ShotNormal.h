#pragma once

#include "ShotBase.h"

class ShotNormal : public ShotBase
{
public:
	ShotNormal(){}
	virtual ~ShotNormal(){}

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

private:

};