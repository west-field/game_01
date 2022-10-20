#include "SceneStepOn.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"
#include "SceneTitle.h"

namespace
{
	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphName = "data/playerStepOn.bmp";	//�v���C���[�O���t�B�b�N
	const char* const kEnemyGraphName = "data/enemyStepOn.bmp";		//�G�l�~�[�O���t�B�b�N
	//�T�E���h�t�@�C����
	const char* const kPlayerSoundName = "sound/playerJump.mp3";	//�v���C���[
	const char* const kEnemySoundName = "sound/enemyDamage.mp3";	//�G�l�~�[
	const char* const kBgmSoundName = "sound/bgmStepOn.mp3";		//BGM
	// �n�ʂ̍���
	constexpr int kFieldY = Game::kScreenHeight - 64;
	//�w�i
	const char* const kBackgroundName = "data/backgroundStepOn.bmp";
}

SceneStepOn::SceneStepOn()
{
	m_hPlayerGraph = -1;
	m_hEnemyGraph = -1;
	m_hBackground = -1;

	m_hPlayerSound = -1;
	m_hEnemySound = -1;
	m_hBgmSound = -1;

	m_color = 0;
}
void SceneStepOn::init()
{
	//�O���t�B�b�N
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	m_hBackground = LoadGraph(kBackgroundName);

	//�T�E���h
	m_hPlayerSound = LoadSoundMem(kPlayerSoundName);
	m_hEnemySound = LoadSoundMem(kEnemySoundName);
	m_hBgmSound = LoadSoundMem(kBgmSoundName);
	
	//player
	m_player.setGraph(m_hPlayerGraph);
	m_player.setup(kFieldY);
	m_player.setJumpSe(m_hPlayerSound);
	
	//enemy
	m_enemy.setGraph(m_hEnemyGraph);
	m_enemy.setup(kFieldY);
	m_enemy.setDamageSe(m_hEnemySound);
	
	//�҂�����
	m_waitTime = kWaitTime;
	m_time = 3;
	
	//�t�F�[�h
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	
	//�F
	m_color = GetColor(255, 255, 255);//��
	
	//BGM���Đ�
	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}
void SceneStepOn::end()
{
	//�T�E���h���~�߂�
	StopSoundMem(m_hPlayerSound);
	StopSoundMem(m_hEnemySound);
	StopSoundMem(m_hBgmSound);

	//�O���t�B�b�N�폜
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
	DeleteGraph(m_hBackground);

	//�T�E���h�폜
	DeleteSoundMem(m_hPlayerSound);
	DeleteSoundMem(m_hEnemySound);
	DeleteSoundMem(m_hBgmSound);
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
	if (m_waitTime > 0)
	{
		m_waitTime--;
		
		m_time = m_waitTime / 60;
		
		return this;
	}

	//�t�F�[�h�A�E�g
	if ((m_fadeBright <= 0) && (m_fadeSpeed < 0))
	{
		//�t�F�[�h�A�E�g���������玟�̃V�[����
		m_fadeBright = 0;
		return (new SceneTitle);
	}

	m_player.update();
	m_enemy.update();
	//�����蔻�� player��enemy�𓥂񂾂��ǂ���
	if (m_player.isCol(m_enemy))
	{
		m_enemy.setHit(true);
		m_isSuccess = true;
	}

	//�N���A������{�^���������ĉ�ʂ�ύX
	Pad::update();
	if (m_fadeSpeed == 0)
	{
		if (m_isSuccess)
		{
			if (Pad::isPress(PAD_INPUT_7))
			{
				m_fadeSpeed = -8;
			}
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
	if (m_waitTime != 0)
	{
		DrawString(200, 220, "���E���L�[�ňړ�", m_color);
		//m_time��0�̎��@�X�^�[�g��\��
		if (m_time <= 0)
		{
			DrawString(200, 240,"�X�^�[�g!!", m_color);
		}
		else
		{
			DrawFormatString(200, 240, m_color, "..%d", m_time);
		}
	}
	//�N���A�����Ƃ��ɕ\�����镶��
	if (m_isSuccess)
	{
		DrawString(200, 200, "�����I", m_color);
		DrawString(200, 220,"(BACK)Q  �^�C�g����", m_color);
	}
}