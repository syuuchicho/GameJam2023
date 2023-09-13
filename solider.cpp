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

void Solider::Update(int& bossPosX, int& bossPosY, int& bossPosR)
{
	//�v���C���[�̍��W���擾
	len = { static_cast<float>(pos.x - bossPosX), static_cast<float>(pos.y - bossPosY) };
	len.normalize();
	len *= -1;
	len *= speed;
	velocity = len;
	//�U���͈͂ɓG�����Ȃ���Βǐ�
	//�~�̓����蔻��
	if ((atkRadius + bossPosR) * (atkRadius + bossPosR)
		< (bossPosX - pos.x) * (bossPosX - pos.x) + (bossPosY - pos.y) * (bossPosY - pos.y))
	{
		pos += velocity;
		isMove = true;
	}
	else
	{
		isMove = false;
		isAttack = true;
	}
	//�ړ��A�j���[�V�����^�C�}�[
	if (isMove)
	{
		moveTimer++;
	}
	if (moveTimer >= 60 || isMove == false)
	{
		moveTimer = 0;
	}
	//�U���A�j���[�V����
	if (isAttack)
	{
		atkTimer++;
	}
	if (atkTimer >= 60 || isAttack == false)
	{
		atkTimer = 0;
	}
}

void Solider::Eraser(int& MousePosX, int& MousePosY, int& MouseRadius, int& solNo,int&soAlive)
{
	//�}�E�X�Ƃ̉~�̓����蔻��
	if ((radius + MouseRadius) * (radius + MouseRadius)
		>= (MousePosX - pos.x) * (MousePosX - pos.x) + (MousePosY - pos.y) * (MousePosY - pos.y))
	{
		isDead_ = true;
		solNo++;
		soAlive--;
	}
}

void Solider::Attack(int& bossPosX, int& bossPosY, int& bossPosR, int& bossHp,int& HitSound,bool& bossIsHit)
{
	//�{�X�Ƃ̍U�������蔻��
	if (isAttack&&atkTimer==59)
	{
		if ((atkRadius + bossPosR) * (atkRadius + bossPosR)
			>= (bossPosX - pos.x) * (bossPosX - pos.x) + (bossPosY - pos.y) * (bossPosY - pos.y))
		{
			PlaySoundMem(HitSound, DX_PLAYTYPE_BACK, true);
			bossHp -= 1;
			bossIsHit = true;
		}
	}
}

void Solider::Draw(int& GraphHandle)
{
	int posX2 = pos.x + radius;
	int posY2 = pos.y + radius;

	//DrawBox(pos.x - radius , pos.y - radius , posX2, posY2, GetColor(255, 255, 255), true);
	//�ړ��A�j���[�V����
	if (isMove && isAttack == false)
	{
		if (moveTimer <= 15)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[0], true);
		}
		if (moveTimer > 15 && moveTimer <= 30)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[1], true);
		}
		if (moveTimer > 30 && moveTimer <= 45)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[2], true);
		}
		if (moveTimer > 45 && moveTimer <= 60)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, WalkHandle_[3], true);
		}
	}
	//�U���A�j���[�V����
	if (isAttack && isMove == false)
	{
		if (atkTimer <= 15)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, AttackHandle_[0], true);
		}
		if (atkTimer > 15 && atkTimer <= 30)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, AttackHandle_[1], true);
		}
		if (atkTimer > 30 && atkTimer <= 45)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, AttackHandle_[2], true);
		}
		if (atkTimer > 45 && atkTimer <= 60)
		{
			DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, AttackHandle_[3], true);
		}
	}
	//�����p
	if (isMove == false && isAttack == false)
	{
		DrawExtendGraph(pos.x - radius, pos.y - radius, posX2, posY2, GraphHandle, true);
	}
	//�U���͈�
	DrawCircle(pos.x, pos.y, atkRadius, GetColor(255, 0, 0), false);
}

void Solider::Death(int& solAlive)
{
	isDead_ = true;
	solAlive--;
}

void Solider::Reset()
{
	isDead_ = true;
}
