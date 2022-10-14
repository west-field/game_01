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

//------------------------------------------------
//PlayerBase
//------------------------------------------------

// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
void PlayerBase::setGraph(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}
void PlayerBase::draw()
{
	if (m_isDead)	return;
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
//------------------------------------------------
//PlayerStepOn
//------------------------------------------------

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
		m_vec.y = kJumpAcc;//�W�����v�J�n
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

	if (playerLeft > enemyRight)	return false;//��
	if (playerRight < enemyLeft)	return false;//���F
	if (playerTop > enemyBottom)	return false;//��
	if (playerBottom < enemyTop)	return false;//��

	return true;
}

//------------------------------------------------
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

// �����ݒ�	�n�ʂ̍�����^����
void PlayerKnockDown::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	m_startPos.x = m_pos.x + m_graphSize.x;
	m_startPos.y = m_pos.y + 16.0f;

	m_shotInterval = 0;
}

void PlayerKnockDown::update()
{
	if (m_isDead)	return;

	m_pos += m_vec;
	m_startPos += m_vec;

	//�n�ʂƂ̓����蔻��
	bool isField = false;
	if (m_pos.y >= m_fieldY - m_graphSize.y)
	{
		m_pos.y = m_fieldY - m_graphSize.y;
		isField = true;
	}

	// �L�[���͏��� ���E�Ɉړ� �W�����v
	Pad::update();

	//�V���b�g��������
	m_shotInterval--;
	if (m_shotInterval < 0)	m_shotInterval = 0;

	if (m_shotInterval <= 0 && m_isRight)
	{
		if (Pad::isPress(PAD_INPUT_2))
		{
			if (m_pScene->createShotNormal(m_startPos))
			{
				m_shotInterval = kShotInterval;
			}
			//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
		if (Pad::isPress(PAD_INPUT_3))
		{
			if (m_pScene->createShotBound(m_startPos))
			{
				m_shotInterval = kShotInterval;
			}
			//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
		if (Pad::isPress(PAD_INPUT_4))
		{
			if (m_pScene->createShotSin(m_startPos))
			{
				m_shotInterval = kShotInterval;
			}
			//PlaySoundMem(m_hShotSe, DX_PLAYTYPE_BACK, true);
		}
	}

	//�n�ʂɂ��Ă�����W�����v�ł���
	if (isField)
	{
		if (Pad::isPress(PAD_INPUT_1))//Z..(A)
		{
			m_vec.y = kJumpAcc;//�W�����v�J�n
		}
	}
	//���E�Ɉړ�
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_isRight = true;
		if (m_pos.x > Game::kScreenWidth - m_graphSize.x)
		{
			m_pos.x = Game::kScreenWidth - m_graphSize.x;
		}
		m_pos.x += 3.0f;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_isRight = false;
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
		}
		m_pos.x -= 3.0f;
	}

	m_vec.y += kGravity;
}
void PlayerKnockDown::draw()
{
	PlayerBase::draw();

	DrawFormatString(0, 20, GetColor(255, 255, 255), "x%3f y%3f", m_pos.x, m_pos.y);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "x%3f y%3f", m_startPos.x,m_startPos.y);
}
bool PlayerKnockDown::isCol(EnemyKnockDown& enemy)
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

	if (playerLeft > enemyRight)	return false;//��
	if (playerRight < enemyLeft)	return false;//���F
	if (playerTop > enemyBottom)	return false;//��
	if (playerBottom < enemyTop)	return false;//��

	return true;
}