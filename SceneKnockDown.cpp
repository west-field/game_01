#include "SceneKnockDown.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include <cassert>

#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotSin.h"

namespace
{
	//�O���t�B�b�N�t�@�C����
	const char* const kPlayerGraphName = "data/playerKnockDown.bmp";
	const char* const kEnemyGraphName = "data/enemyKnockDown.bmp";
	const char* const kShotGraphName = "data/shot.bmp";
	// �n�ʂ̍���
	constexpr int kFieldY = Game::kScreenHeight - 64;
	constexpr int kWaitTime = 60 * 4;
	constexpr int kWaitFrame = 60 * 2;

	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
}

SceneKnockDown::SceneKnockDown()
{
	m_hPlayerGraph = -1;
	m_hEnemyGraph = -1;
	m_hShotGraph = -1;

	m_waitFrame = 0;
	m_waitTime = 0;
	m_num = 0;

	m_isSuccess = false;

	m_fadeBright = 0;
	m_fadeSpeed = 0;
}
void SceneKnockDown::init()
{
	m_hPlayerGraph = LoadGraph(kPlayerGraphName);
	m_hEnemyGraph = LoadGraph(kEnemyGraphName);
	m_hShotGraph = LoadGraph(kShotGraphName);

	m_player.setGraph(m_hPlayerGraph);
	m_player.setup(kFieldY);
	m_player.setScene(this);

	m_enemy.setGraph(m_hEnemyGraph);
	m_enemy.setup(kFieldY);

	m_waitFrame = kWaitFrame;
	m_waitTime = kWaitTime;
	m_num = 3;

	m_fadeBright = 0;
	m_fadeSpeed = 8;
}
void SceneKnockDown::end()
{
	//�摜�̃A�����[�h
	DeleteGraph(m_hPlayerGraph);
	DeleteGraph(m_hEnemyGraph);
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
	m_enemy.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
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
#if false
	if (m_player.isCol(m_enemy))
	{
		m_player.setDead(true);
		m_isSuccess = true;
	}

	if (m_enemy.isCol(m_shot))
	{
		m_enemy.setHit(true);
		m_shot.setHit(true);
	}

#endif
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
			return (new SceneTitle);
		}
	}

	return this;
}
void SceneKnockDown::draw()
{
	SetDrawBright(m_fadeBright, m_fadeBright, m_fadeBright);
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_enemy.draw();

	for (auto& pShot : m_pShotVt)
	{
		if (!pShot)	continue;
		pShot->draw();
	}

	//���ݑ��݂��Ă���e�̐���\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());

	if (m_waitFrame != 0)
	{
		DrawString(340, 200, "���ׂē|��", GetColor(255, 255, 255));
		DrawString(200, 220, "���E���L�[�ňړ� z(A)�ŃW�����v x(B)�ŃV���b�g", GetColor(255, 255, 255));
	}
	if (m_isSuccess)
	{
		DrawString(300, 200, "�����I", GetColor(255, 255, 255));
		DrawFormatString(300, 220, GetColor(255, 255, 255), "�^�C�g����..%d", m_num);
	}
}

//�e�̐���
bool SceneKnockDown::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}
bool SceneKnockDown::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}
bool SceneKnockDown::createShotSin(Vec2 pos)
{
	ShotSin* pShot = new ShotSin;
	pShot->setHandle(m_hShotGraph);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}