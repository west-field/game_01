#pragma once
#include "Vec2.h"
#include "enemy.h"

class PlayerBase
{
public:
	PlayerBase()
	{
		m_handle = -1;
		m_fieldY = 0;
		m_isDead = false;
		m_isRight = true;
	}
	virtual ~PlayerBase(){}

	// グラフィックデータの設定	内部でサイズも取得する
	virtual void setGraph(int handle);
	// 初期設定
	virtual void setup(float fieldY){}
	//更新
	virtual void update(){}
	//表示
	virtual void draw();

	// 位置の取得
	virtual Vec2 getPos() const { return m_pos; }
	// サイズの取得
	virtual Vec2 getColSize() const { return m_colSize; }

protected:
	//グラフィックハンドル
	int m_handle;
	// グラフィックの幅と高さ
	Vec2 m_graphSize;
	// 当たり判定の幅と高さ
	Vec2 m_colSize;
	//位置
	Vec2 m_pos;
	//ベクトル
	Vec2 m_vec;
	//地面の高さ
	float m_fieldY;
	//当たったかどうか
	bool m_isDead;
	//右を向いているかどうか
	bool m_isRight;
};

class PlayerStepOn : public PlayerBase
{
public:
	PlayerStepOn()
	{
		m_hJumpSe = -1;
	}
	virtual ~PlayerStepOn(){}

	// 初期設定	地面の高さを与える
	virtual void setup(float fieldY) override;
	//更新
	virtual void update() override;

	// 位置の取得
	virtual Vec2 getPos() const { return m_pos; }
	// サイズの取得
	virtual Vec2 getColSize() const { return m_colSize; }
public:
	//ジャンプしたときの音を取得
	void setJumpSe(int jumpSe) { m_hJumpSe = jumpSe; }
	// enemyとの衝突判定
	bool isCol(EnemyStepOn& enemy);
	

private:
	int m_hJumpSe;

};

class SceneKnockDown;

class PlayerKnockDown : public PlayerBase
{
public:
	PlayerKnockDown()
	{
		m_pScene = nullptr;
		m_shotInterval = 0;
	}
	virtual ~PlayerKnockDown(){}

	// 初期設定	地面の高さを与える
	virtual void setup(float fieldY) override;
	//更新
	virtual void update() override;
	virtual void draw()override;

	// 位置の取得
	virtual Vec2 getPos() const { return m_pos; }
	// サイズの取得
	virtual Vec2 getColSize() const { return m_colSize; }

public:
	void setScene(SceneKnockDown* pScene) { m_pScene = pScene; }
	// enemyとの衝突判定
	bool isCol(EnemyKnockDown& enemy);
	// 死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }
private:
	//ポインタ
	SceneKnockDown* m_pScene;
	//ショットが銃の位置から発射
	Vec2 m_startPos;
	//ショットの発射間隔
	int m_shotInterval;
};