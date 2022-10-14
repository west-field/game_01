#include "SceneStepOn.h"
#include "DxLib.h"
#include "game.h"
#include "SceneKnockDown.h"

namespace
{
	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphName = "data/playerStepOn.bmp";
	const char* const kEnemyGraphName = "data/enemyStepOn.bmp";
	//���t�@�C����
	const char* const kPlayerSoundName = "sound/player_jump.mp3";
	const char* const kEnemySoundName = "sound/enemy_damage.mp3";
	// �n�ʂ̍���
	constexpr int kFieldY = Game::kScreenHeight - 64;
	constexpr int kWaitTime = 60 * 4;
	constexpr int kWaitFrame = 60 * 2;
}

SceneStepOn::SceneStepOn()
{
	m_hPlayerGraph = -1;
	m_hEnemyGraph = -1;
	m_hPlayerSound = -1;
	m_hEnemySound = -1;
	m_waitFrame = 0;
	m_waitTime = 0;
	m_num = 0;
	m_isSuccess = false;
	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
void SceneStepOn::init()
{
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);

	m_hPlayerSound = LoadSoundMem(kPlayerSoundName);
	m_hEnemySound = LoadSoundMem(kEnemySoundName);

	m_player.setGraph(m_hPlayerGraph);
	m_player.setup(kFieldY);
	m_player.setJumpSe(m_hPlayerSound);

	m_enemy.setGraph(m_hEnemyGraph);
	m_enemy.setup(kFieldY);
	m_enemy.setDamageSe(m_hEnemySound);

	m_waitFrame = kWaitFrame;
	m_waitTime = kWaitTime;
	m_num = 3;

	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
void SceneStepOn::end()
{
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
	DeleteSoundMem(m_hPlayerSound);
	DeleteSoundMem(m_hEnemySound);
}

SceneBase* SceneStepOn::update()
{
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return this;
	}

	m_player.update();
	m_enemy.update();

	if (m_player.isCol(m_enemy))
	{
		m_enemy.setHit(true);
		m_isSuccess = true;
	}

	//�N���A�������ʂ�ύX�ł���
	if (m_isSuccess)
	{
		if (m_waitTime > 0)
		{
			m_waitTime--;

			if (m_waitTime <= 60)
			{
				m_num = 0;
			}
			else if (m_waitTime <= 120)
			{
				m_num = 1;
			}
			else if (m_waitTime <= 180)
			{
				m_num = 2;
			}
			else if (m_waitTime <= 240)
			{
				m_num = 3;
			}

			return this;
		}
		else
		{
			return (new SceneKnockDown);
		}
	}

	return this;
}
void SceneStepOn::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	// �n�ʂ̕`��
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_enemy.draw();

	if (m_waitFrame != 0)
	{
		DrawString(340, 200, "�ӂ�", GetColor(255, 255, 255));
		DrawString(300, 220, "���E���L�[�ňړ�", GetColor(255, 255, 255));
	}
	if (m_isSuccess)
	{
		DrawString(300, 200, "�����I", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255),"����..%d",m_num );
	}
}