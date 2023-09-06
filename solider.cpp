#include "solider.h"
#include "DxLib.h"
void Solider::initialize(int& posX, int& posY)
{
	pos.x = posX;
	pos.y= posY;
}

void Solider::Update(int& enemyX, int& enemyY)
{
	//プレイヤーの座標を取得
	len = { static_cast<float>(pos.x - enemyX), static_cast<float>(pos.y - enemyY) };
	len.normalize();
	len *= -1;
	len *= speed;
	velocity = len;
	//敵を追跡
	pos += len;
}

void Solider::Draw()
{
	int posX2 = pos.x + radius;
	int posY2 = pos.y + radius;

	DrawBox(pos.x, pos.y, posX2, posY2, GetColor(255, 255, 255), true);
}

