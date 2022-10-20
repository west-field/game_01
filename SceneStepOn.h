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

private:
	//�O���t�B�b�N�n���h��
	int m_hPlayerGraph;	//�v���C���[�O���t�B�b�N
	int m_hEnemyGraph;	//�G�l�~�[�O���t�B�b�N
	int m_hBackground;	//�w�i

	//�T�E���h
	int m_hPlayerSound;	//player�ɓn��
	int m_hEnemySound;	//enemy�ɓn��
	int m_hBgmSound;	//BGM

	//�J���[
	int m_color;
	
	//�v���C���[
	PlayerStepOn m_player;
	//�G�l�~�[
	EnemyStepOn m_enemy;

};