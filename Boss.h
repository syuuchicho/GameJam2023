#pragma once
class Boss
{
public:

	void Initialize();

	void Update();

	void Draw();

	int GetPosX() { return posX; }
	int GetPosY() { return posY; }
	int GetPosR() { return radius; }
private:

	void Meteor();

private:

	//座標
	int posX = 1200;
	int posY = 360;
	int radius = 70;

	int hp = 0;

	int attackflag = 0;

	//攻撃処理
	int bossMove = 0; //攻撃ムーブ

	int bossCount = 0; //攻撃前の予兆
	int pattern = 0; //メテオモーション :パターン 1∼3
	int attack_rand = 0; //パターンのランダム変数

	//メテオが落ちる座標
	int meteorX = 0, meteorY = 0;
	int meteorX1 = 0, meteorY1 = 0;
};

