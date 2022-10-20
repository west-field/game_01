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
		m_hBgmSound = -1;
		m_selection = -1;
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
	//�I�����̃T�E���h
	int m_hSelectionSe;
	//�T�E���h
	int m_hBgmSound;
	//��ʂ̑I��
	int m_selection;
};