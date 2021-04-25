#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	CreateBitmap();

}


Map::~Map()
{
	DeleteObject(hBackImage);
}

void Map::Initailize()
{
	
}

void Map::DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc, std::vector<map_info*>m_map)
{
	std::vector<map_info*>::iterator temp_map;

	HBITMAP h01dBitmap;
	HDC hMemDC = nullptr;

	HBITMAP h01dBitmap2;
	HDC hMemDC2 = nullptr;

	int bx = 227;
	int by = bitBack.bmHeight;

	if (!hMemDC)
		hMemDC = CreateCompatibleDC(hdc);

	if (hBackImage == NULL)
		hBackImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);


	h01dBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);

	StretchBlt(hdc, 105, 107, bx * 2, by * 2, hMemDC, 227, 0, bx, by, SRCCOPY);

	SelectObject(hMemDC, h01dBitmap);
	DeleteDC(hMemDC);


	
	int bx2 = 8;
	int by2 = bitBack2.bmHeight;

	if (!hMemDC2)
		hMemDC2 = CreateCompatibleDC(hdc);

	if (hBackImage2 == NULL)
		hBackImage2 = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);

	h01dBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage2);

	static int dot_move = 0;
	if (dot_move > 9)
		dot_move = 0;

	for (temp_map = m_map.begin(); temp_map != m_map.end(); temp_map++)
	{
		if ((*temp_map)->object_num == 3 && (*temp_map)->create == true)
		{
			TransparentBlt(hdc, (*temp_map)->pos.x - 8, (*temp_map)->pos.y - 8, bx2 * 2, by2 * 2, hMemDC2, 0, 0, bx2, by2, RGB(255, 0, 255));
		}

		if ((*temp_map)->object_num == 4 && (*temp_map)->create == true)
		{
			TransparentBlt(hdc, (*temp_map)->pos.x - 8, (*temp_map)->pos.y - 8, bx2 * 2, by2 * 2, hMemDC2, 18 - dot_move, 0, bx2, by2, RGB(255, 0, 255));
		}

	}

	dot_move += 9;

	SelectObject(hMemDC2, h01dBitmap2);
	DeleteDC(hMemDC2);
}

void Map::CreateBitmap()
{
	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/resource.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage, sizeof(BITMAP), &bitBack);

	hBackImage2 = (HBITMAP)LoadImage(NULL, TEXT("images/dot.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage2, sizeof(BITMAP), &bitBack2);

}


