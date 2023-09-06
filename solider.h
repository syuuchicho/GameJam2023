#pragma once
#include"Vector2.h"
class solider
{
public:
	void initialize(int& posX, int& posY);
	void Update();
	void Draw();

	void SetEnemyPos(int&enemyPosX,int&enemyPosY){
		this->enemyPosX=enemyPosX,this->enemyPosY=enemyPosY;}
private:
	int Hp = 0;
	int posX = 0;
	int posY = 0;
	int radius = 16;
	//エネミー
	int enemyPosX = 0;
	int enemyPosY = 0;
};

