#include "SceneBase.h"

SceneBase::SceneBase()
{
	//�ړ��J�n�܂ł̑҂�����(�t���[����)
	m_waitStart = 0;
	m_waitEnd = 0;
	//���Ԃ�\��
	m_time = 0;
	//�����������ǂ���
	m_isSuccess = false;
	m_isMis = false;
	//�t�F�[�h����
	m_fadeBright = 0;
	//�t�F�[�h���x
	m_fadeSpeed = 0;
}