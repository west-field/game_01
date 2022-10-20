#pragma once
#include "SceneBase.h"
#include "player.h"
#include "enemy.h"

class SceneStepOn : public SceneBase
{
public:
	SceneStepOn();
	virtual ~SceneStepOn(){}

	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

	int count(int wait);
private:
	//�O���t�B�b�N�n���h��
	int m_hPlayerGraph;
	int m_hEnemyGraph;
	//�T�E���h
	int m_hPlayerSound;
	int m_hEnemySound;
	int m_hBgmSound;
	//�w�i
	int m_hBackground;
	//�J���[
	int m_color;
	//�v���C���[
	PlayerStepOn m_player;
	//�G�l�~�[
	EnemyStepOn m_enemy;

};