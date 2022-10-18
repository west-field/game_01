#pragma once
#include "Vec2.h"
#include "enemy.h"

class PlayerBase
{
public:
	PlayerBase()
	{
		m_fieldY = 0;
		m_isDead = false;
	}
	virtual ~PlayerBase(){}

	virtual void setGraph() {}
	virtual void setup(){}
	virtual void update(){}
	virtual void draw() {}

	// 位置の取得
	virtual Vec2 getPos() const { return m_pos; }
	// サイズの取得
	virtual Vec2 getColSize() const { return m_colSize; }
	// 死亡設定
	virtual void setDead(bool isDead) { m_isDead = isDead; }

protected:
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
};

//-----------------------------------------------★
//PlayerStepOn
//------------------------------------------------
class PlayerStepOn : public PlayerBase
{
public:
	PlayerStepOn()
	{
		m_hJumpSe = -1;
		m_handle = -1;
		m_isRight = true;
	}
	virtual ~PlayerStepOn(){}


	// グラフィックデータの設定
	virtual void setGraph(int handle);
	// 初期設定	地面の高さを与える
	virtual void setup(float fieldY);
	//更新
	virtual void update() override;
	//表示
	virtual void draw()override;
public:
	//ジャンプしたときの音を取得
	void setJumpSe(int jumpSe) { m_hJumpSe = jumpSe; }
	// enemyとの衝突判定
	bool isCol(EnemyStepOn& enemy);
private:
	//サウンド
	int m_hJumpSe;
	//グラフィック
	int m_handle;
	//右を向いているかどうか
	bool m_isRight;
};


//-----------------------------------------------★
//PlayerKnockDown
//------------------------------------------------
#include "shot.h"
class SceneKnockDown;

class PlayerKnockDown : public PlayerBase
{
public:
	//定数定義

	//プレイヤーグラフィック分割数
	static constexpr int kGraphicDivX = 2;//static　プログラム開始時に作成される　プログラムが終了するまで確保される
	static constexpr int kGraphicDivY = 2;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//プレイヤーグラフィックサイズ
	static constexpr int kGraphicSizeX = 32;
	static constexpr int kGraphicSizeY = 32;
public:
	PlayerKnockDown();
	virtual ~PlayerKnockDown(){}

	virtual void setGraph(int handle,int index);

	// 初期設定
	virtual void setup();
	//更新
	virtual void update() override;
	virtual void draw()override;

public:
	//shot音を取得
	void setShotSe(int shotSe) { m_hShotSe = shotSe; }
	//SceneMainクラスのポインタ
	void setMain(SceneKnockDown* pMain) { m_pMain = pMain; }
	//当たり判定の半径取得
	float getRadius() const;
	//当たり判定の中心位置取得
	Vec2 getCenter() const;

private:
	//グラフィックハンドル
	int m_handle[kGraphicDivNum];
	//表示する番号
	int m_animeNo;
	//音
	int m_hShotSe;
	//ショットが銃の位置から発射
	Vec2 m_startPos;
	//ショットの発射間隔
	int m_shotInterval;

	Vec2 m_upDown;
	Vec2 m_rightLeft;

	Shot m_shot;
	Vec2 m_shotVec;

	SceneKnockDown* m_pMain;
};