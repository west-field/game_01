#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include <vector>

namespace
{
	//�G�̐�
	constexpr int kEnemyNum = 6;
}

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
	bool createShot(Vec2 pos,Vec2 vec);
private:
	//�O���t�B�b�N�n���h��
	int m_hPlayerGraph[PlayerKnockDown::kGraphicDivNum];//�v���C���[
	int m_hEnemyGraph;		//�G�l�~�[�O���t�B�b�N
	int m_hShotGraph;		//�V���b�g�O���t�B�b�N
	int m_hBackground;		//�w�i

	//�T�E���h�n���h��
	int m_hShotSound;		//�V���b�g
	int m_hEnemySound;		//�G�l�~�[
	int m_hBgmSound;		//BGM
	int m_hSuccessSound;	//����
	int m_hMisSound;		//���s
	int m_hReflectionSound;	//����

	//�F
	int m_color;
	//�J�E���g
	int m_count;

	//�v���C���[
	PlayerKnockDown m_player;
	//�G�l�~�[
	EnemyKnockDown m_enemy[kEnemyNum];
	//�V���b�g
	std::vector<Shot*> m_pShotVt;
};