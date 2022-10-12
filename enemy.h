#pragma once
#include "Vec2.h"
#include "player.h"

class Enemy
{
public:
	Enemy()
	{
		m_handle = -1;
		m_fieldY = 0.0f;
		m_isDead = false;
		m_isRight = false;
	}
	virtual ~Enemy(){}

	// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
	void setGraphic(int handle);

	// �����ݒ�	�n�ʂ̍�����^����
	void setup(float fieldY);

	// �X�V
	void update();
	// �`��
	void draw();

	// enemy�Ƃ̏Փ˔���
	bool isCol(Player& player);

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getSize() const { return m_graphSize; }

	// ���S�ݒ�
	void setDead(bool isDead) { m_isDead = isDead; }

private:
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