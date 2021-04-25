#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	Enemy_Location.x = 0;
	Enemy_Location.y = 0;
	Enemy_Image_Location.x = 0;
	Enemy_Image_Location.y = 0;
	Enemy_dir = UP;
	Createbitmap();
}


Enemy::~Enemy()
{
	DeleteObject(hBackImage4);
}

void Enemy::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HBITMAP h01dBitmap;
	HDC hMemDC = nullptr;


	int bx = bitBack4.bmWidth / 36;
	int by = bitBack4.bmHeight / 16;

	if (!hMemDC)
		hMemDC = CreateCompatibleDC(hdc);

	if (hBackImage4 == NULL)
		hBackImage4 = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);


	h01dBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage4);

	TransparentBlt(hdc, Enemy_Location.x - 24, Enemy_Location.y - 12, bx * 2, by * 2, hMemDC, Enemy_Image_Location.x, Enemy_Image_Location.y, bx, by, RGB(0, 0, 0));

	SelectObject(hMemDC, h01dBitmap);
	DeleteDC(hMemDC);

}

void Enemy::Createbitmap()
{
	hBackImage4 = (HBITMAP)LoadImage(NULL, TEXT("images/resource.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage4, sizeof(BITMAP), &bitBack4);

}
