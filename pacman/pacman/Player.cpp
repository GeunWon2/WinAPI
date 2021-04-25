#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	Player_Location.x = 322;
	Player_Location.y = 482;

	Createbitmap();
}


Player::~Player()
{
	DeleteObject(hBackImage3);
}



void Player::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc, int dir)
{
	HBITMAP h01dBitmap;
	HDC hMemDC = nullptr;
	int xStart = 0, yStart = 0;

	static int bit_move_x = 0, bit_move_y = 0;

	int bx = bitBack3.bmWidth/36;
	int by = bitBack3.bmHeight/16;

	if (!hMemDC)
		hMemDC = CreateCompatibleDC(hdc);

	if (hBackImage3 == NULL)
		hBackImage3 = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);


	h01dBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage3);
	if (bit_move_x > 32)
		bit_move_x = 0;

	if (dir == RIGHT)
	{
		bit_move_y = 0;
	}
	else if (dir == LEFT)
	{
		if (bit_move_x != 0)
		{
			bit_move_y = 16;
		}
		else
		{
			bit_move_y = 0;
		}

	}
	else if (dir == UP)
	{
		if (bit_move_x != 0)
		{
			bit_move_y = 32;
		}
		else
		{
			bit_move_y = 0;
		}

	}
	else if (dir == DOWN)
	{
		if (bit_move_x != 0)
		{
			bit_move_y = 48;
		}
		else
		{
			bit_move_y = 0;
		}

	}
	xStart = 486 - bit_move_x;
	yStart = 0 + bit_move_y;

	bit_move_x += 16;

	TransparentBlt(hdc, Player_Location.x-16, Player_Location.y-16, bx* 2, by*2 , hMemDC, xStart, yStart, bx, by, RGB(0, 0, 0));


	SelectObject(hMemDC, h01dBitmap);
	DeleteDC(hMemDC);


}

void Player::Createbitmap()
{
	hBackImage3 = (HBITMAP)LoadImage(NULL, TEXT("images/resource.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage3, sizeof(BITMAP), &bitBack3);

}

