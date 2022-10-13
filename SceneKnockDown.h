#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneKnockDown : public SceneBase
{
public:
	SceneKnockDown();
	virtual ~SceneKnockDown(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;
private:
	PlayerKnockDown m_player;
	EnemyKnockDown m_enemy;
	//�O���t�B�b�N�n���h��
	int m_hPlayerGraph;
	int m_hEnemyGraph;
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