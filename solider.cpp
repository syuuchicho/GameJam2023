#include "solider.h"
#include "DxLib.h"
void Solider::initialize(int& posX, int& posY)
{
	pos.x = posX;
	pos.y = posY;
}

void Solider::Update(int& enemyX, int& enemyY, int& enemyRadius)
{
	//�v���C���[�̍��W���擾
	len = { static_cast<float>(pos.x - enemyX), static_cast<float>(pos.y - enemyY) };
	len.normalize();
	len *= -1;
	len *= speed;
	velocity = len;
	//�U���͈͂ɓG�����Ȃ���Βǐ�
	//�~�̓����蔻��
	if (( atkRadius+enemyRadius ) * ( atkRadius+enemyRadius) < 
		(enemyX - pos.x) * (enemyX - pos.x) + (enemyY - pos.y) * (enemyY- pos.y))
	{
		pos += len;
	}
}

void Solider::Draw()
{
	int posX2 = pos.x + radius / 2;
	int posY2 = pos.y + radius / 2;


	DrawBox(pos.x - radius / 2, pos.y - radius / 2, posX2, posY2, GetColor(255, 255, 255), true);
	//�U���͈�
	DrawCircle(pos.x, pos.y, atkRadius, GetColor(255, 0, 0), false);
}

