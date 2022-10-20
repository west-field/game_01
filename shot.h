#pragma once

#include "Vec2.h"

class Shot
{
public:
	Shot();
	virtual ~Shot(){}

	//�O���t�B�b�N�f�[�^�̐ݒ�
	void setHandle(int handle);
	//�V���b�g�J�n�ʒu���擾
	virtual void start(Vec2 pos, Vec2 vec);
	// �X�V
	virtual void update();
	// �\��
	virtual void draw();

	//���݂��邩
	bool isExist() const { return m_isExist; }
	//���݂��邩�ǂ����̎擾
	void setExist(bool isExist) { m_isExist = isExist; }
	//�����蔻��̔��a�擾
	float getRadius() const;
	//�����蔻��̒��S�ʒu�擾
	Vec2 getCenter() const;
protected:
	// �O���t�B�b�N�n���h��
	int m_handle;
	//�O���t�B�b�N�̕��ƍ���
	Vec2 m_graphSize;
	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;

	//���݂��邩
	bool m_isExist;
};