#include "enemy.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	//���x
	constexpr float kSpeed = -5.0f;
}

// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
void EnemyStepOn::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_colSize.x = m_graphSize.x / 2;
	m_colSize.y = m_graphSize.y;
}

// �����ݒ�	�n�ʂ̍�����^����
void EnemyStepOn::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth - 32.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}

// �X�V
void EnemyStepOn::update()
{
	if (m_isDead)	return;
	m_pos += m_vec;

	if (m_pos.x < 0)
	{
		m_vec.x *= -1.0f;
		m_isRight = true;
	}
	if (m_pos.x > Game::kScreenWidth - 32.0f)
	{
		m_vec.x *= -1.0f;
		m_isRight = false;
	}
}
// �`��
void EnemyStepOn::draw()
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
bool EnemyStepOn::isCol(PlayerStepOn& player)
{
	if (m_isDead)	return false;

	float enemyLeft = getPos().x;
	float enemyRight = getPos().x + m_colSize.x;
	float enemyTop = getPos().y;
	float enemyBottom = getPos().y + m_colSize.y;

	float playerLeft = player.getPos().x;
	float playerRight = player.getPos().x + player.getColSize().x;
	float playerTop = player.getPos().y;
	float playerBottom = player.getPos().y + player.getColSize().y;

	if (enemyLeft > playerRight)	return false;//��
	if (enemyRight < playerLeft)	return false;//���F
	if (enemyTop > playerBottom)	return false;//��
	if (enemyBottom < playerTop)	return false;//��

	PlaySoundMem(m_hDamageSe, DX_PLAYTYPE_BACK, true);
	return true;
}