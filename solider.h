#pragma once
#include"Vector2.h"
#include<memory>
#include<list>
class Solider
{
public:
	void initialize(
		int& MousePosX,
		int& MousePosY,
		int&GraphHandlle,
		int WalkHandle[],
		int AttackHandle[]);
	void Update(int&enemyX,int&enemyY,int&enemyRadius);
	void Eraser(int& MousePosX, int& MousePosY,int&MouseRadius,int&solNo );
	void Draw(int&GraphHandle);

	bool IsDead() const { return isDead_; }
	bool Dead() { return isDead_ = true; }

private:
	int Hp = 0;
	Vector2 pos = { 0,0 };
	Vector2 len = { 0,0 };
	Vector2 velocity = { 0,0 };
	int radius = 32;
	int atkRadius = 32;
	int speed = 4;
	int WalkHandle_[4] = {};
	int moveTimer = 0;
	int AttackHandle_[4] = {};

	bool isMove = false;
	bool isDead_ = false;
};

