#pragma once
#include "Vec2.h"

class EnemyBase
{
public:
	EnemyBase()
	{
		m_handle = -1;
		m_fieldY = 0;
		m_isHit = false;
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

	// �����������ǂ���
	virtual void setHit(bool isHit) { m_isHit = isHit; }

	// �ʒu�̎擾
	virtual Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	virtual Vec2 getColSize() const { return m_graphSize; }

protected:
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
	int m_isHit;
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

public:
	//�_���[�W�����擾
	void setDamageSe(int damageSe) { m_hDamageSe = damageSe; }

private:
	int m_hDamageSe;
};

class EnemyKnockDown : public EnemyBase
{
public:
	EnemyKnockDown(){}
	virtual ~EnemyKnockDown(){}
	// �����ݒ�
	virtual void setup(float fieldY)override;
	// �X�V
	virtual void update()override;

	// �ʒu�̎擾
	virtual Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	virtual Vec2 getColSize() const { return m_graphSize; }
public:
#if false
	// shot�Ƃ̏Փ˔���
	bool isCol(Shot& shot);
#endif
private:
};