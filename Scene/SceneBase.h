#pragma once

class SceneBase
{
public:
	//�n�܂�܂ł̎���
	int const kWaitTime = 60 * 4;
public:
	SceneBase();
	virtual ~SceneBase(){}

	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw(){}
protected:
	//�ړ��J�n�܂ł̑҂�����(�t���[����)
	int m_waitTime;
	//���Ԃ�\��
	int m_time;
	//�����������ǂ���
	bool m_isSuccess;
	//���s�������ǂ���
	bool m_isMis;
	//�t�F�[�h����
	int m_fadeBright;
	//�t�F�[�h���x
	int m_fadeSpeed;
};