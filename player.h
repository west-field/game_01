#pragma once
#include "Vec2.h"
#include "enemy.h"

class PlayerBase
{
public:
	PlayerBase()
	{
		m_fieldY = 0;
		m_isDead = false;
	}
	virtual ~PlayerBase(){}

	virtual void setGraph() {}
	virtual void setup(){}
	virtual void update(){}
	virtual void draw() {}

	// �ʒu�̎擾
	virtual Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	virtual Vec2 getColSize() const { return m_colSize; }
	// ���S�ݒ�
	virtual void setDead(bool isDead) { m_isDead = isDead; }

protected:
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
};

//-----------------------------------------------��
//PlayerStepOn
//------------------------------------------------
class PlayerStepOn : public PlayerBase
{
public:
	PlayerStepOn()
	{
		m_hJumpSe = -1;
		m_handle = -1;
		m_isRight = true;
	}
	virtual ~PlayerStepOn(){}


	// �O���t�B�b�N�f�[�^�̐ݒ�
	virtual void setGraph(int handle);
	// �����ݒ�	�n�ʂ̍�����^����
	virtual void setup(float fieldY);
	//�X�V
	virtual void update() override;
	//�\��
	virtual void draw()override;
public:
	//�W�����v�����Ƃ��̉����擾
	void setJumpSe(int jumpSe) { m_hJumpSe = jumpSe; }
	// enemy�Ƃ̏Փ˔���
	bool isCol(EnemyStepOn& enemy);
private:
	//�T�E���h
	int m_hJumpSe;
	//�O���t�B�b�N
	int m_handle;
	//�E�������Ă��邩�ǂ���
	bool m_isRight;
};


//-----------------------------------------------��
//PlayerKnockDown
//------------------------------------------------
#include "shot.h"
class SceneKnockDown;

class PlayerKnockDown : public PlayerBase
{
public:
	//�萔��`

	//�v���C���[�O���t�B�b�N������
	static constexpr int kGraphicDivX = 2;//static�@�v���O�����J�n���ɍ쐬�����@�v���O�������I������܂Ŋm�ۂ����
	static constexpr int kGraphicDivY = 2;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//�v���C���[�O���t�B�b�N�T�C�Y
	static constexpr int kGraphicSizeX = 32;
	static constexpr int kGraphicSizeY = 32;
public:
	PlayerKnockDown();
	virtual ~PlayerKnockDown(){}

	virtual void setGraph(int handle,int index);

	// �����ݒ�
	virtual void setup();
	//�X�V
	virtual void update() override;
	virtual void draw()override;

public:
	//shot�����擾
	void setShotSe(int shotSe) { m_hShotSe = shotSe; }
	//SceneMain�N���X�̃|�C���^
	void setMain(SceneKnockDown* pMain) { m_pMain = pMain; }
	//�����蔻��̔��a�擾
	float getRadius() const;
	//�����蔻��̒��S�ʒu�擾
	Vec2 getCenter() const;

private:
	//�O���t�B�b�N�n���h��
	int m_handle[kGraphicDivNum];
	//�\������ԍ�
	int m_animeNo;
	//��
	int m_hShotSe;
	//�V���b�g���e�̈ʒu���甭��
	Vec2 m_startPos;
	//�V���b�g�̔��ˊԊu
	int m_shotInterval;

	Vec2 m_upDown;
	Vec2 m_rightLeft;

	Shot m_shot;
	Vec2 m_shotVec;

	SceneKnockDown* m_pMain;
};