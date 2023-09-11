#include "Boss.h"
#include "DxLib.h"
#include <time.h>

void Boss::Initialize() 
{

}

void Boss::Meteor()
{
	//乱数が0∼2だったらパターン1
	if (attack_rand == 0 || attack_rand == 1 || attack_rand == 2)
	{
		pattern = 0;
	}
	//乱数が3∼5だったらパターン2
	if (attack_rand == 3 || attack_rand == 4 || attack_rand == 5)
	{
		pattern = 1;
	}
	//乱数が6∼8だったらパターン3
	if (attack_rand == 6 || attack_rand == 7 || attack_rand == 8)
	{
		pattern = 2;
	}
	//乱数が9だったらパターン4
	if (attack_rand == 9)
	{
		pattern = 3;
	}

	srand(time(NULL));//乱数の種
	switch (pattern)
	{
	case 0: //パターン1

		bossCount++;
		//隕石の座標
		meteorX = 680, meteorY = 200;
		meteorX1 = 860, meteorY1 = 520;

		//カウント120超えたら予兆から攻撃に変化
		if (bossCount > 120)
		{
			attackflag = 1;
		}

		//カウント200超えたらパターンが変わる
		if (bossCount > 200)
		{
			attack_rand = rand() % 10 ;
			bossCount = 0;
			attackflag = 0;
		}
		break;
	case 1: //パターン2

		bossCount++;
		//隕石の座標
		meteorX = 750, meteorY = 320;
		meteorX1 = 960, meteorY1 = 620;

		//カウント120超えたら予兆から攻撃に変化
		if (bossCount > 120)
		{
			attackflag = 1;
		}

		//カウント200超えたらパターンが変わる
		if (bossCount > 200)
		{
			attack_rand = rand() % 10;
			bossCount = 0;
			attackflag = 0;
		}
		break;
	case 2: //パターン3

		bossCount++;
		//隕石の座標
		meteorX = 720, meteorY = 400;
		meteorX1 = 950, meteorY1 = 320;

		//カウント120超えたら予兆から攻撃に変化
		if (bossCount > 120)
		{
			attackflag = 1;
		}

		//カウント200超えたらパターンが変わる
		if (bossCount > 200)
		{
			attack_rand = rand() % 10;
			bossCount = 0;
			attackflag = 0;
		}
		break;
	case 3: //パターン4

		bossCount++;
		//隕石の座標
		meteorX = 820, meteorY = 200;
		meteorX1 = 820, meteorY1 = 550;

		//カウント120超えたら予兆から攻撃に変化
		if (bossCount > 120)
		{
			attackflag = 1;
		}

		//カウント200超えたらパターンが変わる
		if (bossCount > 200)
		{
			attack_rand = rand() % 10;
			bossCount = 0;
			attackflag = 0;
		}
		break;
	}
}

void Boss::Update()
{
	//攻撃パターン
	switch (bossMove)
	{
	case 0:
		Meteor();
		break;

	}

}

void Boss::Draw()
{
	//ボスの描画
	DrawCircle(posX, posY, radius, GetColor(255, 0, 0), true);
	//ボスの攻撃範囲
	DrawCircle(posX - 50, posY, radius + 50, GetColor(255, 0, 0), false);

	//ボスの攻撃(予兆)
	if (attackflag == 0)
	{
		switch (pattern)
		{
		case 0:
			DrawCircle(meteorX, meteorY, radius + 30, GetColor(255, 0, 255), false);
			DrawCircle(meteorX1, meteorY1, radius + 10, GetColor(255, 0, 255), false);
			break;

		case 1:
			DrawCircle(meteorX, meteorY, radius + 20, GetColor(255, 0, 255), false);
			DrawCircle(meteorX1, meteorY1, radius + 30, GetColor(255, 0, 255), false);
			break;

		case 2:
			DrawCircle(meteorX, meteorY, radius + 40, GetColor(255, 0, 255), false);
			DrawCircle(meteorX1, meteorY1, radius + 10, GetColor(255, 0, 255), false);
			break;
		case 3:
			DrawCircle(meteorX, meteorY, radius + 100, GetColor(255, 0, 255), false);
			DrawCircle(meteorX1, meteorY1, radius + 100, GetColor(255, 0, 255), false);
			break;
		}
	}
	//ボスの攻撃
	if (attackflag == 1)
	{
		switch (pattern)
		{
		case 0:
			DrawCircle(meteorX, meteorY, radius + 30, GetColor(255, 0, 255), true);
			DrawCircle(meteorX1, meteorY1, radius + 10, GetColor(255, 0, 255), true);
			break;

		case 1:
			DrawCircle(meteorX, meteorY, radius + 20, GetColor(255, 0, 255), true);
			DrawCircle(meteorX1, meteorY1, radius + 30, GetColor(255, 0, 255), true);
			break;

		case 2:
			DrawCircle(meteorX, meteorY, radius + 40, GetColor(255, 0, 255), true);
			DrawCircle(meteorX1, meteorY1, radius + 10, GetColor(255, 0, 255), true);
			break;
		case 3:
			DrawCircle(meteorX, meteorY, radius + 100, GetColor(255, 0, 255), true);
			DrawCircle(meteorX1, meteorY1, radius + 100, GetColor(255, 0, 255), true);
			break;
		}
	}

	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", bossCount);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", pattern);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "Hp:%d", hp);

}

