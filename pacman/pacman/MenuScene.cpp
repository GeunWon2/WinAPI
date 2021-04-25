#include "stdafx.h"
#include "MenuScene.h"

extern Singleton* m_Single;


MenuScene::MenuScene()
{
	m_UI = m_Menu_UI;
	Initialize();
}


MenuScene::~MenuScene()
{
	DeleteObject(hBackImage);
}

void MenuScene::Initialize(void)
{
	CreateBitmap();

}

void MenuScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	
	if (message == WM_KEYDOWN)
	{

		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		else
		{
			m_Single->Scene_Change(Scene_Enum::E_Play_Scene);

		}

	}

}

void MenuScene::Rendering(HWND hWnd, HDC hdc)
{
	m_UI->Draw_UI(hdc);

	HBITMAP h01dBitmap;
	HDC hMemDC = nullptr;
	RECT rectView;

	GetClientRect(hWnd, &rectView);

	int bx = bitBack.bmWidth;
	int by = bitBack.bmHeight;

	if (!hMemDC)
		hMemDC = CreateCompatibleDC(hdc);

	if (hBackImage == NULL)
		hBackImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);


	h01dBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);

	BitBlt(hdc, 150, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, h01dBitmap);
	DeleteDC(hMemDC);


}


void MenuScene::CreateBitmap()
{
	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/menu.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackImage, sizeof(BITMAP), &bitBack);

}


void MenuScene::Free(void)
{

}
