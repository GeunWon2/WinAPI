#pragma once
#define _USE_MATH_DEFINES
#include <cmath>




class Player
{
protected:

	int Player_x;
	int Player_y;
	POINT cannon[4];


public:


	Player() :Player_x(350), Player_y(795)
	{ 
		cannon[0].x = cannon[3].x = 355;
		cannon[0].y = cannon[1].y = 720;
		cannon[1].x = cannon[2].x = 346;
		cannon[2].y = cannon[3].y = 750;
	};
	~Player() {};

	void Player_Update(int Angle);
	void Player_Draw(HDC hdc);

};

#define Bullet_Size 5
#define Bullet_Speed 2


class Bullet: protected Player
{
private:



public:
	int Bullet_x;
	int Bullet_y;
	bool Bullet_Create = false;
	int x_inc, y_inc;


	Bullet()
	{
		Bullet_x = ((cannon[0].x + cannon[1].x) / 2);
		Bullet_y = cannon[1].y;

	};
	~Bullet() {};

	void Bullet_Draw(HDC hdc);
	void Bullet_Update(int Angle);
	void Bullet_Move();


};


#define Enemy_Speed 7;

class Enemy
{
public:
	int Enemy_Size;

	int Enemy_x;
	int Enemy_y;
	POINT Enemy_box[4];
	bool Enemy_Create;

	Enemy()
	{
		Enemy_x = 50;
		Enemy_y = 50;
		Enemy_Size = 40;
		Enemy_Create = true;

		Enemy_box[0].x = Enemy_box[3].x = Enemy_x - Enemy_Size;
		Enemy_box[0].y = Enemy_box[1].y = Enemy_y - Enemy_Size;
		Enemy_box[1].x = Enemy_box[2].x = Enemy_x + Enemy_Size;
		Enemy_box[2].y = Enemy_box[3].y = Enemy_y + Enemy_Size;

	};
	~Enemy() {};

	void Enemy_Draw(HDC hdc);
	void Enemy_Update(int add);
	void Enemy_Move();
	

};


class Player_HP
{
private:
	int HP_w;

public:
	int HP_h;
	int HP_y;
	int HP_x;
	POINT HP_box[4];
	bool HP_Create = true;


	Player_HP()
	{
		HP_x = 50;
		HP_y = 820;
		HP_h = 20;
		HP_w = 50;

		HP_box[0].x = HP_box[3].x = HP_x - HP_w;
		HP_box[0].y = HP_box[1].y = HP_y - HP_h;
		HP_box[1].x = HP_box[2].x = HP_x + HP_w;
		HP_box[2].y = HP_box[3].y = HP_y + HP_h;
	};
	~Player_HP() {};

	void HP_Draw(HDC hdc);
	void HP_Update(int add);

};


