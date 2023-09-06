#pragma once
#include"Vector2.h"
#include<memory>
#include<list>
class Solider
{
public:
	void initialize(int& posX, int& posY);
	void Update(int&enemyX,int&enemyY);
	void Draw();

	bool IsDead() const { return isDead_; }

private:
	int Hp = 0;
	Vector2 pos = { 0,0 };
	Vector2 len = { 0,0 };
	Vector2 velocity = { 0,0 };
	int radius = 16;
	int speed = 4;
	bool isDead_ = false;

};

