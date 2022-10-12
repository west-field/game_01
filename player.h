#pragma once

#include "Vec2.h"

class Player
{
public:
	Player()
	{
		m_handle = -1;
		m_fieldY = 0.0f;
		m_isRight = true;
	}
	virtual ~Player(){}

	// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
	void setGraphic(int handle);
	// �����ݒ�	�n�ʂ̍�����^����
	void setup(float fieldY);

	void update();
	void draw();

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getColSize() const { return m_colSize; }

private:
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
	//�E�������Ă��邩�ǂ���
	bool m_isRight;
};