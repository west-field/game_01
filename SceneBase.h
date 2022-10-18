#pragma once

class SceneBase
{
public:
	//�萔
	//�n�܂�E�I���܂ł̎���
	int const kWaitStart = 60 * 3;
	int const kWaitEnd = 60 * 4;
public:
	SceneBase();
	virtual ~SceneBase(){}

	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw(){}
protected:
	//�ړ��J�n�܂ł̑҂�����(�t���[����)
	int m_waitStart;
	int m_waitEnd;
	//���Ԃ�\��
	int m_time;
	//�����������ǂ���
	bool m_isSuccess;
	bool m_isMis;
	//�t�F�[�h����
	int m_fadeBright;
	//�t�F�[�h���x
	int m_fadeSpeed;
};