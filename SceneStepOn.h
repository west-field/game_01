#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneStepOn : public SceneBase
{
public:
	SceneStepOn()
	{
		m_hPlayer = -1;
		m_hEnemy = -1;
		m_waitFrame = 0;
		m_waitTime = 0;
		m_num = 0;
		m_isSuccess = false;
		m_fadeBright = 0;
		m_fadeSpeed = 0;
	}
	virtual ~SceneStepOn(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	//�O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hEnemy;
	//�v���C���[
	Player m_player;
	//�G�l�~�[
	Enemy m_enemy;
	//�ړ��J�n�܂ł̑҂�����(�t���[����)
	int m_waitFrame;
	int m_waitTime;
	int m_num;

	//�����������ǂ���
	bool m_isSuccess;
	//�t�F�[�h����
	int m_fadeBright;
	//�t�F�[�h���x
	int m_fadeSpeed;
};