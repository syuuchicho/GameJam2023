#include "solider.h"
#include "DxLib.h"
void Solider::initialize(int& MousePosX, int& MousePosY)
{
	pos.x = MousePosX;
	pos.y = MousePosY;
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
	}
}

void Solider::Eraser(int& MousePosX, int& MousePosY, int& MouseRadius, int& solNo)
{
	//マウスとの円の当たり判定
	if ((radius + MouseRadius) * (radius + MouseRadius)
		>= (MousePosX - pos.x) * (MousePosX - pos.x) + (MousePosY - pos.y) * (MousePosY - pos.y))
	{
		isDead_ = true;
		solNo++;
	}
}

void Solider::Draw()
{
	int posX2 = pos.x + radius ;
	int posY2 = pos.y + radius ;

	DrawBox(pos.x - radius , pos.y - radius , posX2, posY2, GetColor(255, 255, 255), true);
	
	//攻撃範囲
	DrawCircle(pos.x, pos.y, atkRadius, GetColor(255, 0, 0), false);
}

