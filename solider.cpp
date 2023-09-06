#include "solider.h"
#include "DxLib.h"
void solider::initialize(int& posX, int& posY)
{
	this->posX = posX;
	this->posY = posY;
}

void solider::Update()
{

}

void solider::Draw()
{
	int posX2 = posX + radius;
	int posY2 = posY + radius;

	DrawBox(posX, posY, posX2, posY2, GetColor(255, 255, 255), true);
}

