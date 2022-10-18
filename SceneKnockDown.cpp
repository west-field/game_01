#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include <cassert>

#include "shot.h"

namespace
{
	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphName = "data/playerKnockDown.bmp";
	const char* const kEnemyGraphName = "data/enemyKnockDown.bmp";
	const char* const kShotGraphName = "data/shot.bmp";

	constexpr int kWaitTime = 60 * 4;
	constexpr int kWaitFrame = 60 * 2;

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

	m_waitFrame = 0;
	m_waitTime = 0;
	m_num = 0;

	m_isSuccess = false;
	m_isMis = false;

	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
void SceneKnockDown::init()
{
	//�O���t�B�b�N
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	m_hShotGraph = LoadGraph(kShotGraphName);
	LoadDivGraph(kPlayerGraphName, PlayerKnockDown::kGraphicDivNum,
		PlayerKnockDown::kGraphicDivX, PlayerKnockDown::kGraphicDivY,
		PlayerKnockDown::kGraphicSizeX, PlayerKnockDown::kGraphicSizeY, m_hPlayerGraph);
	//�v���C���[
	for (int i = 0; i < PlayerKnockDown::kGraphicDivNum; i++)
	{
		m_player.setGraph(m_hPlayerGraph[i],i);
	}
	m_player.setup();
	m_player.setMain(this);
	//�G�l�~�[
	float posX = 0.0f;
	for (auto& enemy : m_enemy)
	{
		enemy.setGraph(m_hEnemyGraph);
		enemy.setup(posX);
		posX += 80.0f;
	}
	//�҂�����
	m_waitFrame = kWaitFrame;
	m_waitTime = kWaitTime;
	m_num = 3;
	//�t�F�[�h
	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
void SceneKnockDown::end()
{
	//�摜�̃A�����[�h
	for (auto& handle : m_hPlayerGraph)
	{
		DeleteGraph(handle);
	}

	for (auto& enemy : m_enemy)
	{
		DeleteGraph(m_hEnemyGraph);
	}

	DeleteGraph(m_hShotGraph);
	
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;		//�m�ۂ���Ă�����delete
		pShot = nullptr;		//���g��nullptr��
	}
}

SceneBase* SceneKnockDown::update()
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
		if (m_enemy[i].isDead())	continue;
		Vec2 dist = m_enemy[i].getCenter() - m_player.getCenter();
		float radiusAdd = m_enemy[i].getRadius() + m_player.getRadius();
		//���������ꍇ
		if (dist.length() < radiusAdd)
		{
			m_player.setDead(true);
			m_isMis = true;
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

//�N���A�������ʂ�ύX�ł���
	int num = 0;
	for (int i = 0; i < kEnemyNum; i++)
	{
		if (!m_enemy[i].isDead())	continue;
		num++;
		if (num == kEnemyNum)
		{
			m_isSuccess = true;
		}
	}
	if (m_isSuccess || m_isMis)
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
			return (new SceneTitle);
		}
	}

	return this;
}
void SceneKnockDown::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
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
	
	if (m_waitFrame != 0)
	{
		DrawString(340, 200, "���ׂē|��", GetColor(255, 255, 255));
		DrawString(200, 220, "���E���L�[�ňړ� x(B)�ŃV���b�g", GetColor(255, 255, 255));
	}
	if (m_isSuccess)
	{
		DrawString(300, 200, "�����I", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255), "�^�C�g����..%d", m_num);
	}
	else if(m_isMis)
	{
		DrawString(300, 200, "���s", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255), "�^�C�g����..%d", m_num);
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