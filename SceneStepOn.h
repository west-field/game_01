#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneStepOn : public SceneBase
{
public:
	SceneStepOn()
	{
		m_hPlayerGraph = -1;
		m_hEnemyGraph = -1;
		m_hPlayerSound = -1;
		m_hEnemySound = -1;
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
	int m_hPlayerGraph;
	int m_hEnemyGraph;
	//��
	int m_hPlayerSound;
	int m_hEnemySound;
	//�v���C���[
	PlayerStepOn m_player;
	//�G�l�~�[
	EnemyStepOn m_enemy;
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