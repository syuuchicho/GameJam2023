#pragma once
#include"Vector2.h"
#include<memory>
#include<list>
#include"Boss.h"

class Solider
{
public:
	void initialize(
		int& MousePosX,
		int& MousePosY,
		int& GraphHandlle,
		int WalkHandle[],
		int AttackHandle[]);
	void Update(int& enemyX, int& enemyY, int& enemyRadius);
	void Eraser(int& MousePosX, int& MousePosY, int& MouseRadius, int& solNo, int& soAlive);
	void Attack(int& bossPosX, int& bossPosY, int& bossPosR, int& bossHp, int& HitSound, bool& bossIsHit);
	void Draw(int& GraphHandle);
	void Reset();
	
	bool IsDead() const { return isDead_; }
	bool Dead() { return isDead_ = true; }

	int GetPosX() { return pos.x; }
	int GetPosY() { return pos.y; }
	int GetPosR() { return radius; }

private:
	Vector2 pos = { 0,0 };
	Vector2 len = { 0,0 };
	Vector2 velocity = { 0,0 };
	int radius = 32;
	int atkRadius = 30;
	int speed = 4;

	int WalkHandle_[4] = {};
	int AttackHandle_[4] = {};

	int moveTimer = 0;
	int atkTimer = 0;

	bool isMove = false;
	bool isAttack = false;
	bool isDead_ = false;
};

