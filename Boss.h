﻿#pragma once
#include "solider.h"

class Boss
{
public:

	void Initialize();

	void Update();

	void Draw();

	void Reset();

	int GetPosX() { return posX; }
	int GetPosY() { return posY; }
	int GetPosR() { return radius; }

	int GetMeteorX() { return meteorX; }
	int GetMeteorY() { return meteorY; }
	int GetMeteorR() { return meteorR; }
	int GetMeteorX1() { return meteorX1; }
	int GetMeteorY1() { return meteorY1; }
	int GetMeteorR1() { return meteorR1; }

	int GetHp() { return hp; }
	int SetHp(int& bossHp) { return hp = bossHp; }

	int SetIsHit(bool& bossIsHit) { return IsHit = bossIsHit; }

	int attackflag = 0; //予兆と攻撃のフラグ

private:

	//ボスの攻撃関数
	void Meteor();

private:

	int hp = 100; //HP

	int atk = 1; //攻撃力

	//初期座標------
	int posX = 1130;
	int posY = 400;
	int radius = 140;

	int BossGH[3] = {};
	int BossHitGH[3] = {};
	int meteorGH[3] = {};

	int HPGaugeX = 0;
	int HPGaugeGH = 0;
	
	int magicNumX = 160,
		magicNumY = 160;

	int magicPosX = 160;

	//攻撃処理-----
	int bossMove = 0; //攻撃ムーブ

	int patternA = 0; //メテオモーション :パターン 1∼4
	int bossCount = 0; //攻撃前の予兆

	int attack_randA = 0; //パターンのランダム変数A
	int attack_randB = 0; //パターンのランダム変数B

	int patternB = 0; //ビームモーション :パターン1∼3
	int beamFlag = 0;

	int meteorX = 0, meteorY = 0, meteorR = 110;//メテオが落ちる座標(1個目)
	int meteorX1 = 0, meteorY1 = 0, meteorR1 = 120;;//メテオが落ちる座標(2個目)

	int timer = 0;
	int flagTimer = 0;

	bool IsHit = false;
};