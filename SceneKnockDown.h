#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"
#include "ShotBase.h"
#include <vector>

class SceneKnockDown : public SceneBase
{
public:
	SceneKnockDown();
	virtual ~SceneKnockDown(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	//�e�̐���
	bool createShotNormal(Vec2 pos);
	bool createShotBound(Vec2 pos);
	bool createShotSin(Vec2 pos);
private:
	//�v���C���[
	PlayerKnockDown m_player;
	//�G�l�~�[
	EnemyKnockDown m_enemy;
	//�V���b�g
	std::vector<ShotBase*> m_pShotVt;
	//�O���t�B�b�N�n���h��
	int m_hPlayerGraph;
	int m_hEnemyGraph;
	int m_hShotGraph;
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