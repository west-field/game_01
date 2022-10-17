#pragma once

#include "Vec2.h"

class Shot
{
public:
	Shot();
	virtual ~Shot(){}

	void setHandle(int handle) { m_handle = handle; }

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update(Vec2 kShotSpeed);
	// �\��
	virtual void draw();

	//���݂��邩
	bool isExist() const { return m_isExist; }

protected:
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;

	//���݂��邩
	bool m_isExist;
};