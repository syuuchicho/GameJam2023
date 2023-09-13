#include "Boss.h"
#include "DxLib.h"
#include <time.h>

void Boss::Initialize()
{
	LoadDivGraph("Resource/Boss1.png", 3, 3, 1, 320, 320, BossGH);
	LoadDivGraph("Resource/GetDamage.png", 3, 3, 1, 320, 320, BossHitGH);
	LoadDivGraph("Resource/meteor.png", 3, 3, 1, 320, 320, meteorGH);
	HPGaugeGH = LoadGraph("Resource/HpGauge.png");

}

//攻撃関数A
void Boss::Meteor()
{
	//乱数が0∼2だったらパターン1
	if (attack_randA == 0 || attack_randA == 1 || attack_randA == 2)
	{
		patternA = 0;
	}
	//乱数が3∼5だったらパターン2
	if (attack_randA == 3 || attack_randA == 4 || attack_randA == 5)
	{
		patternA = 1;
	}
	//乱数が6∼8だったらパターン3
	if (attack_randA == 6 || attack_randA == 7 || attack_randA == 8)
	{
		patternA = 2;
	}
	//乱数が9だったらパターン4
	if (attack_randA == 9)
	{
		patternA = 3;
	}

	srand(time(NULL));//乱数の種
	switch (patternA)
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
			attack_randA = rand() % 10 ;
			bossCount = 0;
			attackflag = 0;
		}
		break;
	case 1: //パターン2

		bossCount++;
		//隕石の座標
		meteorX = 890, meteorY = 360;
		meteorX1 = 590, meteorY1 = 360;

		//カウント120超えたら予兆から攻撃に変化
		if (bossCount > 120)
		{
			attackflag = 1;
		}

		//カウント200超えたらパターンが変わる
		if (bossCount > 200)
		{
			attack_randA = rand() % 10;
			bossCount = 0;
			attackflag = 0;
		}
		break;
	case 2: //パターン3

		bossCount++;
		//隕石の座標
		meteorX = 720, meteorY = 200;
		meteorX1 = 750, meteorY1 = 590;

		//カウント120超えたら予兆から攻撃に変化
		if (bossCount > 120)
		{
			attackflag = 1;
		}

		//カウント200超えたらパターンが変わる
		if (bossCount > 200)
		{
			attack_randA = rand() % 10;
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
			attack_randA = rand() % 10;
			bossCount = 0;
			attackflag = 0;
		}
		break;
	}
}

void Boss::Beam()
{
	
}

void Boss::Update()
{
	timer++;

	if (timer == 30)
	{
		timer = 0;
	}

	if (attackflag == 1)
	{
		flagTimer++;
	}
	else
	{
		flagTimer = 0;
	}


	//攻撃パターン
	switch (bossMove)
	{
	case 0:
		Meteor();
		break;

	}
	//Hpゲージ計算
	HPGaugeX = (100 - hp) * 4.52;
}

void Boss::Reset()
{
	hp = 100; //HP
}

void Boss::Draw()
{
	//ボスの描画
	if (IsHit)//ダメージを受けたら
	{
		if (timer <= 10)
		{
			DrawGraph(posX - magicPosX, posY - magicNumY, BossHitGH[0], true);
		}
		if (timer > 10 && timer <= 20)
		{
			DrawGraph(posX - magicPosX, posY - magicNumY, BossHitGH[1], true);
		}
		if (timer > 20 && timer <= 30)
		{
			DrawGraph(posX - magicPosX, posY - magicNumY, BossHitGH[2], true);
		}
	}
	else if (timer <= 10)
	{
		DrawGraph(posX - magicPosX, posY - magicNumY, BossGH[0], true);
	}
	else if (timer > 10 && timer <= 20)
	{
		DrawGraph(posX - magicPosX, posY - magicNumY, BossGH[1], true);
	}
	else if (timer > 20 && timer <= 30)
	{
		DrawGraph(posX - magicPosX, posY - magicNumY, BossGH[2], true);
	}

	////ボスの攻撃範囲
	//DrawCircle(posX, posY, radius, GetColor(255, 0, 0), false);

	//ボスの攻撃(予兆)
	if (attackflag == 0)
	{
		switch (patternA)
		{
		case 0:
			DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[0], true);
			DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[0], true);
			break;

		case 1:
			DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[0], true);
			DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[0], true);
			break;

		case 2:
			DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[0], true);
			DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[0], true);
			break;
		case 3:
			DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[0], true);
			DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[0], true);
			break;
		}
	}
	//ボスの攻撃
	if (attackflag == 1)
	{
		if (flagTimer < 20)
		{
			switch (patternA)
			{
			case 0:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[1], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[1], true);
				break;

			case 1:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[1], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[1], true);
				break;

			case 2:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[1], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[1], true);
				break;

			case 3:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[1], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[1], true);
				break;
			}
		}
		if (flagTimer > 20)
		{
			switch (patternA)
			{
			case 0:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[2], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[2], true);
				break;

			case 1:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[2], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[2], true);
				break;

			case 2:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[2], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[2], true);
				break;

			case 3:
				DrawGraph(meteorX - magicNumX, meteorY - magicNumY, meteorGH[2], true);
				DrawGraph(meteorX1 - magicNumX, meteorY1 - magicNumY, meteorGH[2], true);
				break;
			}
		}

	}

	DrawExtendGraph(600, 0, 1450, 500, HPGaugeGH, true);
	//ゲージの長さ=451ドット,スクリーン上始点820
	DrawBox(1271 - HPGaugeX, 50, 1271, 101, GetColor(0, 0, 0), true);
	//1271-820=451

	/*DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", bossCount);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", patternA);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "%d:%d:%d", meteorX,meteorY,meteorR);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "%d:%d:%d", meteorX1, meteorY1, meteorR1);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "%d", timer);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "ボス Hp:%d", hp);*/
}

