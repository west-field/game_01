#pragma once
#include "SceneBase.h"

class SceneMain : public SceneBase
{
public:
	SceneMain() {}
	virtual ~SceneMain(){}

	virtual void init()override;
	virtual void end()override{}

	virtual SceneBase* update()override;
	virtual void draw()override;
private:
	
};