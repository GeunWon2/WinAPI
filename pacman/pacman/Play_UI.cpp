#include "stdafx.h"
#include "Play_UI.h"


Play_UI::Play_UI()
{
	Initialize();
}


Play_UI::~Play_UI()
{
}

void Play_UI::Initialize(void)
{
	Createbitmap();
}

void Play_UI::Draw_UI(HDC hdc)
{
	HBITMAP h01dBitmap = nullptr;
	HDC hMemDC = nullptr;
	int bx = readyBack.bmWidth;
	int by = readyBack.bmHeight/2;

	if (!hMemDC)
		hMemDC = CreateCompatibleDC(hdc);

	if (ready == NULL)
		ready = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);

		h01dBitmap = (HBITMAP)SelectObject(hMemDC, ready);

		if (time_cnt == 0)
		{
			TransparentBlt(hdc, 235, 368, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));
			SelectObject(hMemDC, h01dBitmap);
			DeleteDC(hMemDC);

		}

}

void Play_UI::Createbitmap()
{
	ready = (HBITMAP)LoadImage(NULL, TEXT("images/ready.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(ready, sizeof(BITMAP), &readyBack);

}
