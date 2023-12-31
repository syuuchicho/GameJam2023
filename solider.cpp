#include "solider.h"
#include "DxLib.h"
void Solider::initialize(
	int& MousePosX,
	int& MousePosY,
	int& GraphHandlle,
	int WalkHandle[],
	int AttackHandle[])
{
	pos.x = MousePosX;
	pos.y = MousePosY;
	for (size_t i = 0; i < 4; i++)
	{
		WalkHandle_[i] = WalkHandle[i];
		AttackHandle_[i] = AttackHandle[i];
	}

}

void Solider::Update(int& enemyX, int& enemyY, int& enemyRadius)
{
	//プレイヤーの座標を取得
	len = { static_cast<float>(pos.x - enemyX), static_cast<float>(pos.y - enemyY) };
	len.normalize();
	len *= -1;
	len *= speed;
	velocity = len;
	//攻撃範囲に敵がいなければ追跡
	//円の当たり判定
	if (( atkRadius+enemyRadius ) * ( atkRadius+enemyRadius) 
		< (enemyX - pos.x) * (enemyX - pos.x) + (enemyY - pos.y) * (enemyY- pos.y))
	{
		pos += velocity;
		isMove = true;
	}
	else
	{
		isMove = false;
	}
	//移動アニメーションタイマー
	if (isMove)
	{
		moveTimer++;
	}
	if(moveTimer>=60||isMove==false)
	{
		moveTimer = 0;
	}
}

void Solider::Eraser(int& MousePosX, int& MousePosY, int& MouseRadius, int& solNo)
{
	//マウスとの円の当たり判定
	if ((radius + MouseRadius) * (radius + MouseRadius)
		>= (MousePosX - pos.x) * (MousePosX - pos.x) + (MousePosY - pos.y) * (MousePosY - pos.y))
	{
		Dead();
		solNo++;
	}
}

void Solider::Draw(int& GraphHandle)
{
	int posX2 = pos.x + radius ;
	int posY2 = pos.y + radius ;

	//DrawBox(pos.x - radius , pos.y - radius , posX2, posY2, GetColor(255, 255, 255), true);
	//移動アニメーション
	if (isMove)
	{
		if (moveTimer<=15)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[0], true);
		}
		if (moveTimer >15&&moveTimer <= 30)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[1], true);
		}
		if (moveTimer > 30&&moveTimer <= 45)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[2], true);
		}
		if (moveTimer > 45 &&moveTimer <= 60)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[3], true);
		}
	}
	else//立ち姿
	{
		DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, GraphHandle, true);
	}
	
	//攻撃範囲
	DrawCircle(pos.x, pos.y, atkRadius, GetColor(255, 0, 0), false);
}

