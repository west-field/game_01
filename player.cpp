#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "Pad.h"

namespace
{
	//�W�����v��
	constexpr float kJumpAcc = -15.0f;
	//�d��
	constexpr float kGravity = 0.5f;
	//���x
	constexpr float kSpeed = 3.0f;
}

//-----------------------------------------------��
//PlayerStepOn
//------------------------------------------------

// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
void PlayerStepOn::setGraph(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}
// �����ݒ�	�n�ʂ̍�����^����
void PlayerStepOn::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

void PlayerStepOn::update()
{
	if (m_isDead)	return;

	m_pos += m_vec;

	//�n�ʂƂ̓����蔻��
	bool isField = false;
	if (m_pos.y >= m_fieldY - m_graphSize.y)
	{
		m_pos.y = m_fieldY - m_graphSize.y;
		isField = true;
	}
	//�v���C���[�̓����@�n�ʂɂ�����W�����v����
	if (isField)
	{
		//�W�����v�J�n
		m_vec.y = kJumpAcc;
		//�W�����v����炷
		PlaySoundMem(m_hJumpSe, DX_PLAYTYPE_BACK, true);
	}

	// �L�[���͏��� ���E�Ɉړ�
	Pad::update();
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_isRight = true;
		if (m_pos.x > Game::kScreenWidth - m_graphSize.x)
		{
			m_pos.x = Game::kScreenWidth - m_graphSize.x;
		}
		m_pos.x += kSpeed;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_isRight = false;
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
		m_pos.x -= kSpeed;
	}
	m_vec.y += kGravity;

}

void PlayerStepOn::draw()
{
	if (m_isDead)	return;
	//�E�������Ă���Ƃ��͉E���������G��\������
	if (m_isRight)
	{
		DrawRectGraphF(m_pos.x, m_pos.y, 0, 0,
			static_cast<int>(m_graphSize.x) / 2, static_cast<int>(m_graphSize.y),
			m_handle, true, false);

	}
	else
	{
		DrawRectGraphF(m_pos.x, m_pos.y, static_cast<int>(m_graphSize.x) / 2, 0,
			static_cast<int>(m_graphSize.x) / 2, static_cast<int>(m_graphSize.y),
			m_handle, true, false);

	}
}

//�Փ˔���
bool PlayerStepOn::isCol(EnemyStepOn& enemy)
{
	if (m_isDead)	return false;

	float playerLeft = getPos().x;
	float playerRight = getPos().x + m_colSize.x;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + m_colSize.y;

	float enemyLeft = enemy.getPos().x;
	float enemyRight = enemy.getPos().x + enemy.getColSize().x;
	float enemyTop = enemy.getPos().y;
	float enemyBottom = enemy.getPos().y + enemy.getColSize().y;

	//�������Ă��Ȃ�
	if (playerLeft > enemyRight)	return false;//��
	if (playerRight < enemyLeft)	return false;//���F
	if (playerTop > enemyBottom)	return false;//��
	if (playerBottom < enemyTop)	return false;//��

	//��������
	return true;
}

//-----------------------------------------------��
//PlayerKnockDown
//------------------------------------------------
#include "SceneKnockDown.h"
namespace
{
	// X�����AY�����̍ő呬�x
	constexpr float kSpeedMax = 8.0f;
	constexpr float kAcc = 0.4f;

	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
}

PlayerKnockDown::PlayerKnockDown()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_hShotSe = -1;
	m_shotInterval = 0;
	m_pMain = nullptr;
}

void PlayerKnockDown::setGraph(int handle, int index)
{
	m_handle[index] = handle;
}
// �����ݒ�
void PlayerKnockDown::setup()
{
	m_pos.x = Game::kScreenWidth / 2 - kGraphicSizeX / 2;
	m_pos.y = Game::kScreenHeight - kGraphicSizeY;

	m_vec.x = kSpeed;
	m_vec.y = kSpeed;
	
	m_startPos = m_pos;

	m_shotVec.x = 0.0f;
	m_shotVec.y = -kSpeed;

	m_shotInterval = 0;
}

void PlayerKnockDown::update()
{
	if (m_isDead)	return;

	// �L�[���͏��� ���E�Ɉړ� �W�����v
	Pad::update();

	//x(B)�ŃV���b�g
	m_shotInterval--;
	if (m_shotInterval < 0)	m_shotInterval = 0;
	if (m_shotInterval <= 0)
	{	
		if (m_pMain->createShot(m_startPos, m_shotVec))
		{
			m_shotInterval = kShotInterval;
		}
//		PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
	}
	
	//�ړ�
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_pos.x += m_vec.x;
		m_shotVec.x = m_vec.x;
		m_shotVec.y = 0.0f;
		if (m_pos.x > Game::kScreenWidth - getRadius() * 2)
		{
			m_pos.x = Game::kScreenWidth - getRadius() * 2;
		}
		m_animeNo = 3;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_pos.x -= m_vec.x;
		m_shotVec.x = -m_vec.x;
		m_shotVec.y = 0.0f;
		if (m_pos.x < 0.0f)
		{
			m_pos.x = 0.0f;
		}
		m_animeNo = 2;
	}
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos.y -= m_vec.y;
		m_shotVec.x = 0.0f;
		m_shotVec.y = -m_vec.y;
		if (m_pos.y < 0.0f)
		{
			m_pos.y = 0.0f;
		}
		m_animeNo = 0;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos.y += m_vec.y;
		m_shotVec.x = 0.0f;
		m_shotVec.y = m_vec.y;
		if (m_pos.y > Game::kScreenHeight - getRadius() * 2)
		{
			m_pos.y = Game::kScreenHeight - getRadius() * 2;
		}
		m_animeNo = 1;
	}

	m_startPos = m_pos;
}

void PlayerKnockDown::draw()
{
	if (m_isDead)	return;
	//�����ɉ������G��\��
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
}

float PlayerKnockDown::getRadius() const
{
	//�摜�̔��a
	return kGraphicSizeX / 2;
}

Vec2 PlayerKnockDown::getCenter() const
{
	//�����蔻��̒��S�ʒu
	Vec2 result = m_pos;
	result.x += kGraphicSizeX / 2;
	result.y += kGraphicSizeY / 2;

	return result;
}