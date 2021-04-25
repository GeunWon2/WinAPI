#include "stdafx.h"
#include "Object.h"


void Player::Player_Update(int Angle)
{
	cannon[0].x = cannon[3].x = 355;
	cannon[0].y = cannon[1].y = 720;
	cannon[1].x = cannon[2].x = 346;
	cannon[2].y = cannon[3].y = 750;

	for (int i = 0; i < 4; i++)
	{
		float temp;
		temp = (cannon[i].x - Player_x)*cos(Angle * M_PI / 180) - (cannon[i].y - Player_y)*sin(Angle * M_PI / 180) + Player_x;
		cannon[i].y = (cannon[i].x - Player_x)*sin(Angle * M_PI / 180) + (cannon[i].y - Player_y)*cos(Angle * M_PI / 180) + Player_y;
		cannon[i].x = temp;

	}

}

void Player::Player_Draw(HDC hdc)
{
	Polygon(hdc, cannon, 4);
	Pie(hdc, 300, 750, 400, 850, 400, 800, 300, 800);

}




void Bullet::Bullet_Draw(HDC hdc)
{
	if(Bullet_Create==true)
		Ellipse(hdc, Bullet_x - Bullet_Size, Bullet_y - Bullet_Size, Bullet_x + Bullet_Size, Bullet_y + Bullet_Size);

}

void Bullet::Bullet_Update(int Angle)
{

	cannon[0].x = cannon[3].x = 355;
	cannon[0].y = cannon[1].y = 720;
	cannon[1].x = cannon[2].x = 346;
	cannon[2].y = cannon[3].y = 750;

	for (int i = 0; i < 4; i++)
	{
		float temp;
		temp = (cannon[i].x - Player_x)*cos(Angle * M_PI / 180) - (cannon[i].y - Player_y)*sin(Angle * M_PI / 180) + Player_x;
		cannon[i].y = (cannon[i].x - Player_x)*sin(Angle * M_PI / 180) + (cannon[i].y - Player_y)*cos(Angle * M_PI / 180) + Player_y;
		cannon[i].x = temp;

	}


	Bullet_x = (cannon[0].x + cannon[1].x) / 2;

	if (Angle < 0)
		Bullet_y = cannon[1].y - Bullet_Size;
	else
		Bullet_y = cannon[1].y + Bullet_Size;

	x_inc = Player_x - Bullet_x;
	y_inc = Player_y - Bullet_y;


}

void Bullet::Bullet_Move()
{

	Bullet_y -= y_inc/Bullet_Speed;
	Bullet_x -= x_inc/Bullet_Speed;

}

void Enemy::Enemy_Draw(HDC hdc)
{
	if (Enemy_Create == true)
		Polygon(hdc, Enemy_box, 4);
}

void Enemy::Enemy_Update(int add)
{
	Enemy_x += add;

	Enemy_box[0].x = Enemy_box[3].x = Enemy_x - Enemy_Size;
	Enemy_box[1].x = Enemy_box[2].x = Enemy_x + Enemy_Size;

}

void Enemy::Enemy_Move()
{
	Enemy_box[0].x = Enemy_box[3].x = Enemy_x - Enemy_Size;
	Enemy_box[0].y = Enemy_box[1].y = Enemy_y - Enemy_Size;
	Enemy_box[1].x = Enemy_box[2].x = Enemy_x + Enemy_Size;
	Enemy_box[2].y = Enemy_box[3].y = Enemy_y + Enemy_Size;

	Enemy_y += Enemy_Speed;

	if (Enemy_y+Enemy_Size >= 950)
	{
		Enemy_y = 50;
	}



}

void Player_HP::HP_Draw(HDC hdc)
{
	if(HP_Create == true)
		Polygon(hdc, HP_box, 4);
}

void Player_HP::HP_Update(int add)
{
	HP_x += add;

	HP_box[0].x = HP_box[3].x = HP_x - HP_w;
	HP_box[1].x = HP_box[2].x = HP_x + HP_w;
}


