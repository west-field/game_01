#include "SceneStepOn.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"

namespace
{
	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphName = "data/playerStepOn.bmp";
	const char* const kEnemyGraphName = "data/enemyStepOn.bmp";
	//�T�E���h�t�@�C����
	const char* const kPlayerSoundName = "sound/player_jump.mp3";
	const char* const kEnemySoundName = "sound/enemy_damage.mp3";
	const char* const kBgmSoundName = "sound/bgmStepOn.mp3";
	// �n�ʂ̍���
	constexpr int kFieldY = Game::kScreenHeight - 64;
	//�w�i
	const char* const kBackgroundName = "data/backgroundStepOn.bmp";
}

SceneStepOn::SceneStepOn()
{
	m_hPlayerGraph = -1;
	m_hEnemyGraph = -1;

	m_hPlayerSound = -1;
	m_hEnemySound = -1;
	m_hBgmSound = -1;

	m_hBackground = -1;

	m_color = 0;
}
void SceneStepOn::init()
{
	//�O���t�B�b�N
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	//�T�E���h
	m_hPlayerSound = LoadSoundMem(kPlayerSoundName);
	m_hEnemySound = LoadSoundMem(kEnemySoundName);
	m_hBgmSound = LoadSoundMem(kBgmSoundName);
	//�w�i
	m_hBackground = LoadGraph(kBackgroundName);
	//player
	m_player.setGraph(m_hPlayerGraph);
	m_player.setup(kFieldY);
	m_player.setJumpSe(m_hPlayerSound);
	//enemy
	m_enemy.setGraph(m_hEnemyGraph);
	m_enemy.setup(kFieldY);
	m_enemy.setDamageSe(m_hEnemySound);
	//�҂�����
	m_waitStart = kWaitStart;
	m_waitEnd = kWaitEnd;
	m_time = 3;
	//�t�F�[�h
	m_fadeBright = 0;
	m_fadeSpeed = 8;

	m_color = GetColor(255, 255, 255);//��

	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}
void SceneStepOn::end()
{
	StopSoundMem(m_hPlayerSound);
	StopSoundMem(m_hBgmSound);
	//�O���t�B�b�N�폜
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
	//�T�E���h�폜
	DeleteSoundMem(m_hPlayerSound);
	DeleteSoundMem(m_hEnemySound);
	DeleteSoundMem(m_hBgmSound);
	//�w�i�폜
	DeleteGraph(m_hBackground);
}

SceneBase* SceneStepOn::update()
{
	//��ʂ̃t�F�[�h�C��
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	//�Q�[�����n�܂�܂ł̎���
	if (m_waitStart > 0)
	{
		m_waitStart--;
		m_time = count(m_waitStart);
		return this;
	}

	m_player.update();
	m_enemy.update();
	//�����蔻�� player��enemy�𓥂񂾂��ǂ���
	if (m_player.isCol(m_enemy))
	{
		m_enemy.setHit(true);
		m_isSuccess = true;
	}

	//�N���A�������ʂ�ύX�ł���
	if (m_isSuccess)
	{
		//���ɍs���܂ł̑҂�����
		if (m_waitEnd > 0)
		{
			m_waitEnd--;
			m_time = count(m_waitEnd);
			return this;
		}
		else
		{
			//�^�C�g����ʂɍs��
			return (new SceneTitle);
		}
	}

	return this;
}
void SceneStepOn::draw()
{
	//�t�F�[�h
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	//�w�i
	DrawGraph(0, 0, m_hBackground, false);
	
	m_player.draw();
	m_enemy.draw();

	//�n�܂�܂ł̎��Ԓ��ɕ\�����镶��
	if (m_waitStart != 0)
	{
		DrawString(340, 200, "���݂���", m_color);
		DrawString(300, 220, "���E���L�[�ňړ�", m_color);
		//m_time��0�̎��@�X�^�[�g��\��
		if (m_time <= 0)
		{
			DrawString(300, 240,"�X�^�[�g!!", m_color);
		}
		else
		{
			DrawFormatString(300, 240, m_color, "..%d", m_time);
		}
	}
	//�N���A�����Ƃ��ɕ\�����镶��
	if (m_isSuccess)
	{
		DrawString(300, 200, "�����I", m_color);
		DrawFormatString(300, 220, m_color,"�^�C�g����..%d", m_time);
	}
}
//�J�E���g
int SceneStepOn::count(int wait)
{
	if (wait <= 60)
	{
		return 0;
	}
	else if (wait <= 120)
	{
		return 1;
	}
	else if (wait <= 180)
	{
		return 2;
	}
	else if (wait <= 240)
	{
		return 3;
	}
	return -1;
}