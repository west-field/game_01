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
	//�X�V
	virtual void update(){}
	//�\��
	virtual void draw();

	// �ʒu�̎擾
	virtual Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	virtual Vec2 getColSize() const { return m_colSize; }

protected:
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
	//�X�V
	virtual void update() override;

	// �ʒu�̎擾
	virtual Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	virtual Vec2 getColSize() const { return m_colSize; }
public:
	//�W�����v�����Ƃ��̉����擾
	void setJumpSe(int jumpSe) { m_hJumpSe = jumpSe; }
	// enemy�Ƃ̏Փ˔���
	bool isCol(EnemyStepOn& enemy);
	

private:
	int m_hJumpSe;

};

class SceneKnockDown;

class PlayerKnockDown : public PlayerBase
{
public:
	PlayerKnockDown()
	{
		m_pScene = nullptr;
		m_shotInterval = 0;
	}
	virtual ~PlayerKnockDown(){}

	// �����ݒ�	�n�ʂ̍�����^����
	virtual void setup(float fieldY) override;
	//�X�V
	virtual void update() override;
	virtual void draw()override;

	// �ʒu�̎擾
	virtual Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	virtual Vec2 getColSize() const { return m_colSize; }

public:
	void setScene(SceneKnockDown* pScene) { m_pScene = pScene; }
	// enemy�Ƃ̏Փ˔���
	bool isCol(EnemyKnockDown& enemy);
	// ���S�ݒ�
	void setDead(bool isDead) { m_isDead = isDead; }
private:
	//�|�C���^
	SceneKnockDown* m_pScene;
	//�V���b�g���e�̈ʒu���甭��
	Vec2 m_startPos;
	//�V���b�g�̔��ˊԊu
	int m_shotInterval;
};