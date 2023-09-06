#pragma once
#include"Vector2.h"
#include<memory>
#include<list>
class Solider
{
public:
	void initialize(int& posX, int& posY);
	void Update();
	void Draw();

	bool IsDead() const { return isDead_; }

private:
	int Hp = 0;
	int posX = 0;
	int posY = 0;
	int radius = 16;
	int speed = 4;
	bool isDead_ = false;

};

