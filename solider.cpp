#include "solider.h"
#include "DxLib.h"
void Solider::initialize(int& posX, int& posY)
{
	pos.x = posX;
	pos.y = posY;
}

void Solider::Update(int& enemyX, int& enemyY, int& enemyRadius)
{
	//ƒvƒŒƒCƒ„[‚ÌÀ•W‚ğæ“¾
	len = { static_cast<float>(pos.x - enemyX), static_cast<float>(pos.y - enemyY) };
	len.normalize();
	len *= -1;
	len *= speed;
	velocity = len;
	//UŒ‚”ÍˆÍ‚É“G‚ª‚¢‚È‚¯‚ê‚Î’ÇÕ
	//‰~‚Ì“–‚½‚è”»’è
	if (( atkRadius+enemyRadius ) * ( atkRadius+enemyRadius) 
		< (enemyX - pos.x) * (enemyX - pos.x) + (enemyY - pos.y) * (enemyY- pos.y))
	{
		pos += len;
	}
}

void Solider::Eraser(int& MousePosX, int& MousePosY, int& MouseRadius, int& solNo)
{
	//ƒ}ƒEƒX‚Æ‚Ì‰~‚Ì“–‚½‚è”»’è
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
	
	//UŒ‚”ÍˆÍ
	DrawCircle(pos.x, pos.y, atkRadius, GetColor(255, 0, 0), false);
}

