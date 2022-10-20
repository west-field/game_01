#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include <vector>

namespace
{
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
public:
	//�J�E���g
	int count(int wait);
	//�e�̐���
	bool createShot(Vec2 pos,Vec2 vec);
private:
	//�v���C���[
	PlayerKnockDown m_player;
	//�G�l�~�[
	EnemyKnockDown m_enemy [kEnemyNum] ;
	//�V���b�g
	std::vector<Shot*> m_pShotVt;
	//�O���t�B�b�N�n���h��
	int m_hPlayerGraph[PlayerKnockDown::kGraphicDivNum];
	int m_hEnemyGraph;
	int m_hShotGraph;
	//�T�E���h�n���h��
	int m_hShotSound;
	int m_hEnemySound;
	//�w�i
	int m_hBackground;
	//�F
	int m_color;
};