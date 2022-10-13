#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle()
	{
		m_fadeBright = 0;
		m_fadeSpeed = 0;
		m_hSelectionSe = -1;
	}
	virtual ~SceneTitle(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw()override;
private:
	//�t�F�[�h����
	int m_fadeBright;
	//�t�F�[�h���x
	int m_fadeSpeed;
	int m_hSelectionSe;
};