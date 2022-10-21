#include "Pad.h"
#include "DxLib.h"

namespace
{
	constexpr int kLogNum = 16;
	//���̓��O 0���ŐV
	int padLog[kLogNum];
}

namespace Pad
{
	//�p�b�h�̓��͏�Ԏ擾
	void update()
	{
		//���݂̃p�b�h�̏󋵂��擾
		int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		//���O�̍X�V
		for (int i = kLogNum - 1; i >= 1; i--)
		{
			padLog[i] = padLog[i - 1];
		}
		//�ŐV�̏�Ԃ�����
		padLog[0] = padState;
	}

	//�����グ����
	bool isPress(int button)
	{
		return  (padLog[0] & button);
	}

	//�g���K�[����
	bool isTrigger(int button)
	{
		bool isNow = (padLog[0] & button);//���݂̏��
		bool isLast = (padLog[1] & button);//1�t���[���O�̏��
		return (isNow && !isLast);//���݉�����Ă��đO�̃t���[���ŉ�����Ă��Ȃ�����
	}

	//����������
	bool isRelase(int button)
	{
		bool isNow = (padLog[0] & button);//���݂̏��
		bool isLast = (padLog[1] & button);//1�t���[���O�̏��
		return (!isNow && isLast);//���݉�����ĂȂ��đO�̃t���[���͉�����Ă���
	}
}