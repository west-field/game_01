#pragma once
#include "Vec2.h"
#include "enemy.h"

class PlayerBase
{
public:
	PlayerBase()
	{
		m_handle = -1;
		m_fieldY = 0;
		m_isDead = false;
		m_isRight = true;
	}
	virtual ~PlayerBase(){}

	// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
	virtual void setGraph(int handle);
	// �����ݒ�
	virtual void setup(float fieldY){}

	virtual void update(){}
	virtual void draw();

public:
	//�O���t�B�b�N�n���h��
	int m_handle;
	// �O���t�B�b�N�̕��ƍ���
	Vec2 m_graphSize;
	// �����蔻��̕��ƍ���
	Vec2 m_colSize;
	//�ʒu
	Vec2 m_pos;
	//�x�N�g��
	Vec2 m_vec;
	//�n�ʂ̍���
	float m_fieldY;
	//�����������ǂ���
	bool m_isDead;
	//�E�������Ă��邩�ǂ���
	bool m_isRight;
};

class PlayerStepOn : public PlayerBase
{
public:
	PlayerStepOn()
	{
		m_hJumpSe = -1;
	}
	virtual ~PlayerStepOn(){}

	// �����ݒ�	�n�ʂ̍�����^����
	virtual void setup(float fieldY) override;

	virtual void update() override;

	void setJumpSe(int jumpSe) { m_hJumpSe = jumpSe; }

	// player�Ƃ̏Փ˔���
	bool isCol(EnemyStepOn& enemy);

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getColSize() const { return m_colSize; }

	// ���S�ݒ�
	void setDead(bool isDead) { m_isDead = isDead; }

private:
	int m_hJumpSe;

};

class PlayerKnockDown : public PlayerBase
{
public:
	PlayerKnockDown(){}
	virtual ~PlayerKnockDown(){}

	// �����ݒ�	�n�ʂ̍�����^����
	virtual void setup(float fieldY) override;

	virtual void update() override;
private:

};