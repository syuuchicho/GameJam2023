#include "solider.h"
#include "DxLib.h"
void Solider::initialize(int& posX, int& posY)
{
	this->posX = posX;
	this->posY = posY;
}

void Solider::Update()
{
	//‰EˆÚ“®
	posX += speed;
}

void Solider::Draw()
{
	int posX2 = posX + radius;
	int posY2 = posY + radius;

	DrawBox(posX, posY, posX2, posY2, GetColor(255, 255, 255), true);
}

