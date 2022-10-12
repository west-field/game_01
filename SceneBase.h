#pragma once

class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase(){}

	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw(){}
private:
};