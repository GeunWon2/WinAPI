// Defence.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Defence.h"
#include "Object.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFENCE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFENCE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFENCE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEFENCE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   600, 80, 700, 900, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

Player m_Player;

vector<Enemy*>Enemy_list;
vector<Enemy*>::iterator Enemy_it;

vector<Player_HP*>HP_list;
vector<Player_HP*>::iterator HP_it;

vector<Bullet*>Bullet_list;
vector<Bullet*>::iterator Bullet_it;

vector<wstring>Rank_ID;
vector<int>Rank_Score;

#define HP_Speed 20
#define ID_max 10
#define ID_x  270
#define ID_y 300

RECT rectView;
HBITMAP hDoubleBufferImage;
HBITMAP hTransparentImage;
HBITMAP hTransparentImage2;
void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	enum Menu { Main_Menu, Gameplay_Screen, Game_End };
	HDC hdc;
	static int Angle;
	static int add;
	static int game_end;


	HBRUSH hBrush, oldBrush;
	HFONT hFont, OldFont;
	TCHAR TitleName[125] = TEXT("Defence");
	static TCHAR ID[ID_max];
	static SIZE ID_size;
	static int Score;
	static int select_menu;
	static int ID_cnt;

	static int select_x, select_y;

	switch (message)
	{
	case WM_CREATE:
	{

		add = 0;
		select_x = 223;
		select_y = 648;
		Score = 0;
		ID_cnt = 0;
		game_end = 0;
		Angle = 0;
		GetClientRect(hWnd, &rectView);

		for (int i = 0; i < 7; i++, add += 100)
		{
			Player_HP* H = new Player_HP;
			HP_list.push_back(H);
			(*H).HP_Update(add);
		}

		add = 0;

		for (int i = 0; i < 7; i++, add += 100)
		{
			Enemy* E = new Enemy;
			Enemy_list.push_back(E);
			(*E).Enemy_Update(add);
		}

		SetTimer(hWnd, 1, 40, NULL);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_CHAR:
	{
		if (select_menu == Main_Menu)
		{
			if (wParam == VK_BACK && ID_cnt >= 0)
			{
				ID[ID_cnt] = NULL;
				ID_cnt--;
			}
			else if (ID_cnt < ID_max - 1)
			{
				ID[ID_cnt++] = wParam;
			}
			else if (ID_cnt >= ID_max - 1)
			{
				ID[--ID_cnt] = wParam;
			}

		}
	}

	case WM_KEYDOWN:
	{

		switch (select_menu)
		{
		case Main_Menu:
			if (wParam == VK_RETURN)
			{
				select_menu = Gameplay_Screen;
			}
			break;

		case Gameplay_Screen:
			if (wParam == VK_LEFT && Angle >= -88)
			{
				Angle -= 5;
			}
			else if (wParam == VK_RIGHT && Angle <= 88)
			{
				Angle += 5;
			}
			else
			{
				Angle += 0;
			}

			if (wParam == VK_SPACE && game_end != 7)
			{
				Bullet* B = new Bullet;
				Bullet_list.push_back(B);
				(*B).Bullet_Create = true;
				(*B).Bullet_Update(Angle);

			}
			m_Player.Player_Update(Angle);

			if (wParam == VK_ESCAPE&&game_end == 7)
			{
				wofstream File_O("Rank.dat", ios_base::out | ios_base::app | ios_base::binary);

				if (!File_O.is_open())
				{
					exit(1);
				}


				File_O << ID << "-" << Score << endl;

				File_O.close();
				select_menu = Game_End;
			}
			break;

		case Game_End:

			if (wParam == VK_LEFT && select_x == 343)
			{
				select_x -= 120;
			}
			else if (wParam == VK_RIGHT && select_x == 223)
			{
				select_x += 120;
			}
			else
			{
				select_x += 0;
			}

			if (wParam == VK_RETURN)
			{
				if (select_x == 223)
				{
					for (HP_it = HP_list.begin(); HP_it != HP_list.end(); HP_it++)
					{
						(*HP_it)->HP_Create = true;
					}

					for (Enemy_it = Enemy_list.begin(); Enemy_it != Enemy_list.end(); Enemy_it++)
					{
						(*Enemy_it)->Enemy_y = -50;
					}

					for (Bullet_it = Bullet_list.begin(); Bullet_it != Bullet_list.end(); Bullet_it++)
					{
						(*Bullet_it)->Bullet_Create = false;
					}

					Rank_ID.clear();
					Rank_Score.clear();

					Score = 0;
					game_end = 0;

					select_menu = Gameplay_Screen;
				}
				else if (select_x == 343)
				{
					exit(1);
				}

			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
	}
	
	break;

	case WM_TIMER:
	{
		if (select_menu == Gameplay_Screen)
		{
			for (Bullet_it = Bullet_list.begin(); Bullet_it != Bullet_list.end(); Bullet_it++)
			{
				(*Bullet_it)->Bullet_Move();
			}

			for (Enemy_it = Enemy_list.begin(); Enemy_it != Enemy_list.end(); Enemy_it++)
			{
				(*Enemy_it)->Enemy_Move();
			}

			for (HP_it = HP_list.begin(); HP_it != HP_list.end(); HP_it++)
			{
				(*HP_it)->HP_Update(HP_Speed);

				if ((*HP_it)->HP_x >= 700)
				{
					for (; (*HP_it)->HP_x >= 0;)
					{
						(*HP_it)->HP_Update(-HP_Speed);
					}
				}

			}

			for (int i = 0, x = 50; i < 7, x <= 650; i++, x += 100)
			{
				for (int j = 0; j < 7; j++)
				{
					if (((Enemy_list[i]->Enemy_box[2].x <= HP_list[j]->HP_box[1].x &&
						Enemy_list[i]->Enemy_box[2].x >= HP_list[j]->HP_box[0].x) ||
						(Enemy_list[i]->Enemy_box[3].x <= HP_list[j]->HP_box[1].x &&
							Enemy_list[i]->Enemy_box[3].x >= HP_list[j]->HP_box[0].x)) &&
						Enemy_list[i]->Enemy_box[2].y >= HP_list[j]->HP_box[0].y &&
						Enemy_list[i]->Enemy_box[2].y <= HP_list[j]->HP_box[2].y &&
						HP_list[j]->HP_Create == true)
					{
						HP_list[j]->HP_Create = false;
						game_end += 1;
						Enemy_list[i]->Enemy_x = x;
						Enemy_list[i]->Enemy_y = -60;
					}
				}
			}

			for (Bullet_it = Bullet_list.begin(); Bullet_it != Bullet_list.end();)
			{
				if ((*Bullet_it)->Bullet_x <= 0 || (*Bullet_it)->Bullet_y <= 0 || (*Bullet_it)->Bullet_x >= 700)
				{
					Bullet_it = Bullet_list.erase(Bullet_it);
				}
				else
				{
					for (int i = 0, x = 50; i < 7, x <= 650; i++, x += 100)
					{
						if ((*Bullet_it)->Bullet_Create == true &&
							(Enemy_list[i]->Enemy_box[0].x <= (*Bullet_it)->Bullet_x &&
								Enemy_list[i]->Enemy_box[1].x >= (*Bullet_it)->Bullet_x &&
								Enemy_list[i]->Enemy_box[2].y >= (*Bullet_it)->Bullet_y &&
								Enemy_list[i]->Enemy_box[0].y <= (*Bullet_it)->Bullet_y))
						{
							Bullet_it = Bullet_list.erase(Bullet_it);
							(*Bullet_it)->Bullet_Create = false;
							Score += 1;
							Enemy_list[i]->Enemy_x = x;
							Enemy_list[i]->Enemy_y = -60;
						}
					}
					++Bullet_it;
				}
			}

		}


	}
	InvalidateRgn(hWnd, NULL, FALSE);
	break;

	case WM_KEYUP:
	{
		if (wParam == VK_ESCAPE&&select_menu == Game_End)
		{

			wifstream fin;
			fin.open("Rank.dat", ios_base::in | ios_base::binary);

			if (!fin.is_open())
			{
				exit(1);
			}

			while (!fin.eof())
			{
				WCHAR temp[20];
				fin.getline(temp, 20);
				wstring user_id;
				wstring user_score;
				bool flag_load = false;

				if (temp[0] == '\0')
				{
					break;
				}

				if (temp != L"")
				{
					for (int i = 0; i <= 19; i++)
					{
						if (!flag_load)
						{
							if (temp[i] != '-')
							{
								user_id += temp[i];
							}
							else
							{
								Rank_ID.push_back(user_id);
								user_id.clear();
								flag_load = true;
							}

						}
						else
						{
							if (temp[i] != '\0')
							{
								user_score += temp[i];
							}
							else
							{
								Rank_Score.push_back(stoi(user_score));
								user_score.clear();
								flag_load = false;
							}
						}
					}
				}
			}
			fin.close();


			for (int i = 1; i < Rank_Score.size(); i++)
			{
				for (int j = i; j > 0; j--)
				{
					if (Rank_Score[j] > Rank_Score[j - 1])
					{
						swap(Rank_Score[j], Rank_Score[j - 1]);
						swap(Rank_ID[j], Rank_ID[j - 1]);

					}
					else
					{
						break;
					}

				}
			}


		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);



		switch (select_menu)
		{
		case Main_Menu:
		{
			hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은고딕"));
			OldFont = (HFONT)SelectObject(hdc, hFont);
			TextOut(hdc, 285, 100, TitleName, lstrlen(TitleName));
			SelectObject(hdc, OldFont);
			DeleteObject(hFont);
			TextOut(hdc, ID_x - 25, ID_y, _T("ID : "), _tcslen(_T("ID : ")));
			TextOut(hdc, ID_x + 2, ID_y, _T("max 9"), _tcslen(_T("max 9")));
			TextOut(hdc, ID_x, ID_y, ID, _tcslen(ID));
			GetTextExtentPoint(hdc, ID, _tcslen(ID), &ID_size);
			SetCaretPos(ID_x + ID_size.cx, ID_y);
		}
		break;

		case Gameplay_Screen:
		{
			HideCaret(hWnd);

			DrawBitmapDoubleBuffering(hWnd, hdc);

			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			m_Player.Player_Draw(hdc);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);


			TextOut(hdc, 0, 0, ID, _tcslen(ID));
			TextOut(hdc, 500, 0, _T("Score : "), _tcslen(_T("Score : ")));
			TextOut(hdc, 650, 0, to_wstring(Score).c_str(), _tcslen(to_wstring(Score).c_str()));

			if (game_end == 7)
			{

				TextOut(hdc, 310, 350, _T("Game Over"), _tcslen(_T("Game Over")));
				TextOut(hdc, 287, 370, _T("Press 'ESC' Key"), _tcslen(_T("Press 'ESC' Key")));
			}
		}
		break;

		case Game_End:
		{
			hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은고딕"));
			OldFont = (HFONT)SelectObject(hdc, hFont);
			TextOut(hdc, 250, 100, _T("Good Job"), _tcslen(_T("Good Job")));
			SelectObject(hdc, OldFont);
			DeleteObject(hFont);

			TextOut(hdc, 310, 170, ID, _tcslen(ID));
			TextOut(hdc, 330, 210, to_wstring(Score).c_str(), _tcslen(to_wstring(Score).c_str()));

			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, select_x, select_y, select_x + 104, select_y + 44);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);

			Rectangle(hdc, 225, 650, 325, 690);
			TextOut(hdc, 255, 662, _T("Replay"), _tcslen(_T("Replay")));

			Rectangle(hdc, 345, 650, 445, 690);
			TextOut(hdc, 365, 662, _T("Game End"), _tcslen(_T("Game End")));






			for (int i = 0; i<5 && i < Rank_ID.size(); i++)
			{
				TextOut(hdc, 210, 260 + (i * 50), to_wstring(i + 1).c_str(), _tcslen(to_wstring(i + 1).c_str()));
				TextOut(hdc, 230, 260 + (i * 50), Rank_ID[i].c_str(), _tcslen(Rank_ID[i].c_str()));
				TextOut(hdc, 450, 260 + (i * 50), to_wstring(Rank_Score[i]).c_str(), _tcslen(to_wstring(Rank_Score[i]).c_str()));
			}




		}
		break;

		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		Rank_ID.clear();
		Rank_Score.clear();
		Bullet_list.clear();
		Enemy_list.clear();
		HP_list.clear();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
{

	HBRUSH hBrush, oldBrush;

	HDC hMemDC;  //화면
	HBITMAP h01dBitmap; //그릴 비트맵들의 핸들 



	hMemDC = CreateCompatibleDC(hdc);

	if (!hMemDC)
		hMemDC = CreateCompatibleDC(hdc);

	if (hDoubleBufferImage == NULL)
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //종이 규격정하기 종이 준비

	h01dBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //종이 교체



		FillRect(hMemDC, &rectView, (HBRUSH)GetStockObject(WHITE_BRUSH));

		hBrush = CreateSolidBrush(RGB(139, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		for (HP_it = HP_list.begin(); HP_it != HP_list.end(); HP_it++)
		{	
			(*HP_it)->HP_Draw(hMemDC);
		}
		SelectObject(hMemDC, oldBrush);
		DeleteObject(hBrush);


		hBrush = CreateSolidBrush(RGB(128, 128, 128));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		for (Enemy_it = Enemy_list.begin(); Enemy_it != Enemy_list.end(); Enemy_it++)
		{
			(*Enemy_it)->Enemy_Draw(hMemDC);
		}
		SelectObject(hMemDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(105, 105, 105));
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		for (Bullet_it = Bullet_list.begin(); Bullet_it != Bullet_list.end(); Bullet_it++)
		{
			(*Bullet_it)->Bullet_Draw(hMemDC);
		}
		SelectObject(hMemDC, oldBrush);
		DeleteObject(hBrush);


	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, h01dBitmap);
	DeleteDC(hMemDC);



}
