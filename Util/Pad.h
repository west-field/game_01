#pragma once

//�R���g���[���[�̓��͏�Ԃ��擾����
namespace Pad
{
	//�p�b�h�̓��͏�Ԏ擾
	void update();

	//�����グ����
	bool isPress(int button);
	//�g���K�[����
	bool isTrigger(int button);
	//����������
	bool isRelase(int button);
}