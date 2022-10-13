#pragma once
#include "Vec2.h"

class EnemyBase
{
public:
	EnemyBase()
	{
		m_handle = -1;
		m_fieldY = 0;

		m_isDead = false;
		m_isRight = false;
	}
	virtual ~EnemyBase(){}

	// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
	virtual void setGraph(int handle);
	// �����ݒ�
	virtual void setup(float fieldY) {}

	virtual void update(){}
	virtual void draw();

public:
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �O���t�B�b�N�̕��ƍ���
	Vec2 m_graphSize;
	// �����蔻��̕��ƍ���
	Vec2 m_colSize;
	// �ʒu
	Vec2 m_pos;
	// �x�N�g��
	Vec2 m_vec;
	// �n�ʂ̍���
	float m_fieldY;
	//�����������ǂ���
	bool m_isDead;
	//�E�������Ă��邩�ǂ���
	bool m_isRight;
};

class EnemyStepOn : public EnemyBase
{
public:
	EnemyStepOn()
	{
		m_hDamageSe = -1;
	}
	virtual ~EnemyStepOn(){}
	
	// �����ݒ�
	virtual void setup(float fieldY)override;

	// �X�V
	virtual void update()override;

	void setDamageSe(int damageSe) { m_hDamageSe = damageSe; }

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getColSize() const { return m_graphSize; }

	// ���S�ݒ�
	void setDead(bool isDead) { m_isDead = isDead; }

private:
	int m_hDamageSe;

};

class EnemyKnockDown : public EnemyBase
{
public:

	// �����ݒ�
	virtual void setup(float fieldY)override;

	// �X�V
	virtual void update()override;
private:
};