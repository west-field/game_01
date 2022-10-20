#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"
#include "SceneTitle.h"
#include <cassert>

namespace
{
	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphName = "data/playerKnockDown.bmp";//�v���C���[
	const char* const kEnemyGraphName = "data/enemyKnockDown.bmp";	//�G�l�~�[
	const char* const kShotGraphName = "data/shot.bmp";				//�V���b�g
	const char* const kBackgroundName = "data/backgroundKnockDown.bmp";//�w�i

	//�T�E���h�t�@�C����
	const char* const kShotSoundName = "sound/shot.mp3";			//�V���b�g
	const char* const kShotHitSoundName = "sound/shotHit.mp3";		//�q�b�g
	const char* const kBgmSoundName = "sound/bgmKnockDown.mp3";		//BGM
	const char* const kSuccessSoundName = "sound/success.mp3";		//����
	const char* const kMisSoundName = "sound/mis.mp3";				//���s
	const char* const kReflectionSoundName = "sound/reflection.mp3";//����

	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
}

SceneKnockDown::SceneKnockDown()
{
	for (auto& handle : m_hPlayerGraph)
	{
		handle = -1;
	}
	m_hEnemyGraph = -1;
	m_hShotGraph = -1;
	m_hBackground = -1;

	m_hShotSound = -1;
	m_hEnemySound = -1;
	m_hBgmSound = -1;
	m_hSuccessSound = -1;
	m_hMisSound = -1;
	m_hReflectionSound = -1;

	m_color = 0;

	m_count = 0;
}
void SceneKnockDown::init()
{
	//�O���t�B�b�N
	LoadDivGraph(kPlayerGraphName, PlayerKnockDown::kGraphicDivNum,
		PlayerKnockDown::kGraphicDivX, PlayerKnockDown::kGraphicDivY,
		PlayerKnockDown::kGraphicSizeX, PlayerKnockDown::kGraphicSizeY, m_hPlayerGraph);//�v���C���[�O���t�B�b�N
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);	//�G�l�~�[�O���t�B�b�N
	m_hShotGraph = LoadGraph(kShotGraphName);	//�V���b�g�O���t�B�b�N
	m_hBackground = LoadGraph(kBackgroundName);	//�w�i

	//�T�E���h
	m_hShotSound = LoadSoundMem(kShotSoundName);			//�V���b�g
	m_hEnemySound = LoadSoundMem(kShotHitSoundName);		//�G�l�~�[hit
	m_hBgmSound = LoadSoundMem(kBgmSoundName);				//BGM
	m_hSuccessSound = LoadSoundMem(kSuccessSoundName);		//����
	m_hMisSound = LoadSoundMem(kMisSoundName);				//���s
	m_hReflectionSound = LoadSoundMem(kReflectionSoundName);//����
	
	//�v���C���[
	for (int i = 0; i < PlayerKnockDown::kGraphicDivNum; i++)
	{
		m_player.setGraph(m_hPlayerGraph[i],i);
	}
	m_player.setup();
	m_player.setShotSe(m_hShotSound);
	m_player.setMain(this);
	
	//�G�l�~�[
	float posX = 0.0f;
	for (auto& enemy : m_enemy)
	{
		enemy.setGraph(m_hEnemyGraph);
		enemy.setup(posX);
		enemy.setDamageSe(m_hEnemySound);
		enemy.setReflectionSe(m_hReflectionSound);
		posX += 80.0f;
	}
	
	//�҂�����
	m_waitTime = kWaitTime;
	m_time = 3;
	
	//�t�F�[�h
	m_fadeBright = 0;
	m_fadeSpeed = 8;
	
	//�F
	m_color = GetColor(0, 0, 128);//�l�C�r�[
	
	//�J�E���g
	m_count = 0;
	
	//Bgm���Đ�
	PlaySoundMem(m_hBgmSound, DX_PLAYTYPE_LOOP, true);
}
void SceneKnockDown::end()
{
	//�T�E���h���~�߂�
	StopSoundMem(m_hShotSound);
	StopSoundMem(m_hSuccessSound);
	StopSoundMem(m_hMisSound);
	StopSoundMem(m_hReflectionSound);

	//�摜,���̃A�����[�h
	for (auto& handle : m_hPlayerGraph)
	{
		DeleteGraph(handle);
	}
	
	for (auto& enemy : m_enemy)
	{
		DeleteGraph(m_hEnemyGraph);
		DeleteSoundMem(m_hEnemySound);
		DeleteSoundMem(m_hReflectionSound);
	}

	DeleteGraph(m_hShotGraph);
	DeleteGraph(m_hBackground);

	DeleteSoundMem(m_hShotSound);
	DeleteSoundMem(m_hBgmSound);
	DeleteSoundMem(m_hSuccessSound);
	DeleteSoundMem(m_hMisSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;		//�m�ۂ���Ă�����delete
		pShot = nullptr;		//���g��nullptr��
	}
}

SceneBase* SceneKnockDown::update()
{
	//��ʂ̃t�F�[�h�C��
	m_fadeBright += m_fadeSpeed;

	if (m_fadeBright >= 255)
	{
		m_fadeBright = 255;
		m_fadeSpeed = 0;
	}
	//�Q�[�����n�߂�܂ł̎���
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
	for (auto& enemy : m_enemy)
	{
		enemy.update();
	}

	//enemy�ǂ����̓����蔻��
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (m_enemy[i].isDead())	continue;
		for (int j = i + 1; j < kEnemyNum; j++)
		{
			if (m_enemy[j].isDead())	continue;
			Vec2 dist = m_enemy[i].getCenter() - m_enemy[j].getCenter();
			float radiusAdd = m_enemy[i].getRadius() + m_enemy[j].getRadius();
			//���������ꍇ
			if (dist.length() < radiusAdd)
			{
				m_enemy[i].bound(m_enemy[j].getCenter());
				m_enemy[j].bound(m_enemy[i].getCenter());
			}
		}
	}

	//player��enemy�����������ǂ���
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (m_enemy[i].isDead() || m_player.isDead())	continue;
		Vec2 dist = m_enemy[i].getCenter() - m_player.getCenter();
		float radiusAdd = m_enemy[i].getRadius() + m_player.getRadius();
		//���������ꍇ
		if (dist.length() < radiusAdd)
		{
			m_player.setDead(true);
			//�~�X
			m_isMis = true;
			StopSoundMem(m_hBgmSound);
		}
	}

	//shot��enemy�����������ǂ���
	for (auto& pShot : m_pShotVt)
	{
		if (pShot != nullptr)
		{
			for (int i = 0; i < kEnemyNum; i++)
			{
				if (m_enemy[i].isDead())	continue;
				Vec2 dist = m_enemy[i].getCenter() - pShot->getCenter();
				float radiusAdd = m_enemy[i].getRadius() + pShot->getRadius();
				//���������ꍇ
				if (dist.length() < radiusAdd)
				{
					m_enemy[i].setHit(true);
					pShot->setExist(false);
				}
			}
		}
		
	}

	//�V���b�g����
	std::vector<Shot*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

		if (!pShot)
		{
			it++;
			continue;//���g�����邩�ǂ����@nullptr�̎�continue
		}
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�v�f�̍폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}

	//�G�l�~�[�����ׂē|���ƃN���A
	int num = 0;
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (!m_enemy[i].isDead())	continue;
		num++;
		if (num == kEnemyNum)
		{
			m_isSuccess = true;
			StopSoundMem(m_hBgmSound);
		}
	}

	//������񂾂��炷
	if (m_count == 0)
	{
		if (m_isSuccess)//������
		{
			PlaySoundMem(m_hSuccessSound, DX_PLAYTYPE_BACK, true);
			m_count++;
		}
		else if (m_isMis)//���s��
		{
			PlaySoundMem(m_hMisSound, DX_PLAYTYPE_BACK, true);
			m_count++;
		}
	}

	//�N���A�A�~�X������{�^���������ĉ�ʂ�ύX
	Pad::update();
	if (m_fadeSpeed == 0)
	{
		if (m_isSuccess || m_isMis)
		{
			if (Pad::isPress(PAD_INPUT_7))
			{
				m_fadeSpeed = -8;
			}
		}
	}
	return this;
}
void SceneKnockDown::draw()
{
	//�t�F�[�h
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);

	//�w�i��\��
	DrawGraph(0, 0, m_hBackground, false);
	
	m_player.draw();
	for (auto& enemy : m_enemy)
	{
		enemy.draw();
	}
	
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot)	continue;
		pShot->draw();
	}
	
	//�X�^�[�g�܂ł̎��Ԓ��ɕ\��
	if (m_waitTime != 0)
	{
		DrawString(200, 220, "���E���L�[�ňړ� x(B)�ŃV���b�g", m_color);
		//m_time��0�̎��@�X�^�[�g��\��
		if (m_time <= 0)
		{
			DrawString(200, 240,"�X�^�[�g!!", m_color);
		}
		else
		{
			DrawFormatString(200, 240, m_color, "�n�܂�܂�..%d", m_time);
		}
	}
	//�N���A�̎�
	if (m_isSuccess)
	{
		DrawString(300, 200, "�쒀�����I", m_color);
		DrawString(300, 220, "(BACK)Q  �^�C�g����", m_color);
	}
	//�~�X�̎�
	else if(m_isMis)
	{
		DrawString(300, 200, "�쒀���s", m_color);
		DrawString(300, 220, "(BACK)Q  �^�C�g����", m_color);
	}
}

//�e�̐���
bool SceneKnockDown::createShot(Vec2 pos,Vec2 vec)
{
	Shot* pShot = new Shot;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos,vec);
	m_pShotVt.push_back(pShot);

	return true;
}