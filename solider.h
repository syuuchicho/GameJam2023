#pragma once
#include"Vector2.h"
#include<memory>
#include<list>
#include"Boss.h"

class Solider
{
public:
	void initialize(int& MousePosX, int& MousePosY);
	void Update(int& enemyX, int& enemyY, int& enemyRadius);
	void Eraser(int& MousePosX, int& MousePosY, int& MouseRadius, int& solNo);
	void Draw();
	
	bool isDeath() { return isDead_ = true; }

	bool IsDead() const { return isDead_; }

	int Hp = 5;
	int GetPosX() { return pos.x; }
	int GetPosY() { return pos.y; }
	int GetPosR() { return radius; }

private:
	Vector2 pos = { 0,0 };
	Vector2 len = { 0,0 };
	Vector2 velocity = { 0,0 };
	int radius = 8;
	int atkRadius = 32;
	int speed = 4;
	bool isDead_ = false;
};

