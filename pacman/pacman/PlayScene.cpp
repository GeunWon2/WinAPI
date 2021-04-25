#include "stdafx.h"
#include "PlayScene.h"

#define pac_move 16


#define MAP_SIZE_X 31
#define MAP_SIZE_Y 28	

#define MAP_SQUARE 16

extern Singleton* m_Single;

enum Enemy_name { Blinky, Pinky, Inky, Clyde };

enum Map_check { open, close, well, none };


HANDLE timerQueue = CreateTimerQueue();
HANDLE timer;

VOID CALLBACK TimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	time_cnt = 1;

}



PlayScene::PlayScene()
{
	m_UI = m_Play_UI;
	Initialize();

}

PlayScene::~PlayScene()
{
	Free();
}

void PlayScene::Initialize(void)
{
	P_dir = 2;
	draw_dir = 2;
	temp_dir = 0;

	life_cnt = 3;

	blinky->setEnemy_Location(322, 290, 0);
	blinky->setEnemy_Image_Location(452, 65);
	blinky->setEnemy_mode(1);
	blinky->setEnemy_dir(LEFT);

	pinky->setEnemy_Location(306, 338, 0);
	pinky->setEnemy_Image_Location(452, 81);
	pinky->setEnemy_mode(1);
	pinky->setEnemy_dir(UP);

	inky->setEnemy_Location(322, 338, 0);
	inky->setEnemy_Image_Location(452, 97);
	inky->setEnemy_mode(1);
	inky->setEnemy_dir(UP);

	clyde->setEnemy_Location(338, 338, 0);
	clyde->setEnemy_Image_Location(452, 113);
	clyde->setEnemy_mode(1);
	clyde->setEnemy_dir(UP);


	

	int map_arr[31][28] =
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1 },
		{ 1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1 },
		{ 1,4,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,4,1 },
		{ 1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1 },
		{ 1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
		{ 1,3,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,3,1 },
		{ 1,3,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,3,1 },
		{ 1,3,3,3,3,3,3,1,1,3,3,3,3,1,1,3,3,3,3,1,1,3,3,3,3,3,3,1 },
		{ 1,1,1,1,1,1,3,1,1,1,1,1,2,1,1,2,1,1,1,1,1,3,1,1,1,1,1,1 },
		{ 2,2,2,2,2,1,3,1,1,1,1,1,2,1,1,2,1,1,1,1,1,3,1,2,2,2,2,2 },
		{ 2,2,2,2,2,1,3,1,1,2,2,2,2,2,2,2,2,2,2,1,1,3,1,2,2,2,2,2 },
		{ 2,2,2,2,2,1,3,1,1,2,1,1,1,7,7,1,1,1,2,1,1,3,1,2,2,2,2,2 },
		{ 1,1,1,1,1,1,3,1,1,2,1,2,2,2,2,2,2,1,2,1,1,3,1,1,1,1,1,1 },
		{ 0,2,2,2,2,2,3,2,2,2,1,2,2,2,2,2,2,1,2,2,2,3,2,2,2,2,2,0 },
		{ 1,1,1,1,1,1,3,1,1,2,1,2,2,2,2,2,2,1,2,1,1,3,1,1,1,1,1,1 },
		{ 2,2,2,2,2,1,3,1,1,2,1,1,1,1,1,1,1,1,2,1,1,3,1,2,2,2,2,2 },
		{ 2,2,2,2,2,1,3,1,1,2,2,2,2,2,2,2,2,2,2,1,1,3,1,2,2,2,2,2 },
		{ 2,2,2,2,2,1,3,1,1,2,1,1,1,1,1,1,1,1,2,1,1,3,1,2,2,2,2,2 },
		{ 1,1,1,1,1,1,3,1,1,2,1,1,1,1,1,1,1,1,2,1,1,3,1,1,1,1,1,1 },
		{ 1,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1 },
		{ 1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1 },
		{ 1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1 },
		{ 1,4,3,3,1,1,3,3,3,3,3,3,3,2,2,3,3,3,3,3,3,3,1,1,3,3,4,1 },
		{ 1,1,1,3,1,1,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,3,1,1,3,1,1,1 },
		{ 1,1,1,3,1,1,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,3,1,1,3,1,1,1 },
		{ 1,3,3,3,3,3,3,1,1,3,3,3,3,1,1,3,3,3,3,1,1,3,3,3,3,3,3,1 },
		{ 1,3,1,1,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,1,1,3,1 },
		{ 1,3,1,1,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,1,1,3,1 },
		{ 1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	EnemyPath->GetMap(map_arr);

	int add_pos_y = 0;
	for (int i = 0; i < 31; i++)
	{
		int add_pos_x = 0;
		for (int j = 0; j < 28; j++)
		{

			map_info *temp = new map_info;

			temp->pos.y = 114 + add_pos_y;
			temp->pos.x = 114 + add_pos_x;
			temp->create = true;
			temp->object_num = map_arr[i][j];

			m_map.push_back(temp);

			add_pos_x += 16;
		}
		add_pos_y += 16;
	}

}

void PlayScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{

	if (time_cnt == 0)
	{
		CreateTimerQueueTimer(&timer, timerQueue, TimerCallback, NULL, 3000, 3000, 0);
	}
	else if (time_cnt != 0)
	{
		input_dir(wParam);
		
		if (message == WM_TIMER)
		{

			PacmanMove(message, temp_dir);
			EnemyMove(message, m_Player->getPlayer_Location_x(), m_Player->getPlayer_Location_y(), blinky);

			EnemyMove(message, m_Player->getPlayer_Location_x(), m_Player->getPlayer_Location_y(), pinky);

			EnemyMove(message, m_Player->getPlayer_Location_x(), m_Player->getPlayer_Location_y(), inky);

			EnemyMove(message, m_Player->getPlayer_Location_x(), m_Player->getPlayer_Location_y(), clyde);


		}

		
	}



}

void PlayScene::Rendering(HWND hWnd, HDC hdc)
{

	m_Map->DrawBitmapDoubleBuffering(hWnd, hdc, m_map);

	m_Player->DrawBitmapDoubleBuffering(hWnd, hdc, draw_dir);

	blinky->DrawBitmapDoubleBuffering(hWnd, hdc);
	pinky->DrawBitmapDoubleBuffering(hWnd, hdc);
	inky->DrawBitmapDoubleBuffering(hWnd, hdc);
	clyde->DrawBitmapDoubleBuffering(hWnd, hdc);

	m_UI->Draw_UI(hdc);

	life_draw(hdc);

	victory(hdc);

}

void PlayScene::Free(void)
{
	m_map.clear();
	m_map.shrink_to_fit();

}



void PlayScene::pacman_eat(int P_x, int P_y)
{
	if (P_x == blinky->getEnemy_Location_x() && P_y == blinky->getEnemy_Location_y() && blinky->getEnemy_mode() == 2)
	{
		blinky->setEnemy_Image_Location(583, 81);
		blinky->setEnemy_mode(3);
	}
	else if (P_x == inky->getEnemy_Location_x() && P_y == inky->getEnemy_Location_y() && inky->getEnemy_mode() == 2)
	{
		inky->setEnemy_Image_Location(583, 81);
		inky->setEnemy_mode(3);
	}
	else if (P_x == clyde->getEnemy_Location_x() && P_y == clyde->getEnemy_Location_y() && clyde->getEnemy_mode() == 2)
	{
		clyde->setEnemy_Image_Location(583, 81);
		clyde->setEnemy_mode(3);
	}
	else if (P_x == pinky->getEnemy_Location_x() && P_y == pinky->getEnemy_Location_y() && pinky->getEnemy_mode() == 2)
	{
		pinky->setEnemy_Image_Location(583, 81);
		pinky->setEnemy_mode(3);
	}


	for (it_map = m_map.begin(); it_map != m_map.end(); it_map++)
	{
		if ((*it_map)->pos.x == P_x && (*it_map)->pos.y == P_y && (*it_map)->object_num == 3 && (*it_map)->create == true)
		{
			(*it_map)->create = false;
		}

		if ((*it_map)->pos.x == P_x && (*it_map)->pos.y == P_y && (*it_map)->object_num == 4 && (*it_map)->create == true)
		{
			(*it_map)->create = false;

			if (blinky->getEnemy_mode() == 1)
			{
				blinky->setEnemy_Image_Location(583, 65);
				blinky->setEnemy_mode(2);
			}
			if (pinky->getEnemy_mode() == 1)
			{
				pinky->setEnemy_Image_Location(583, 65);
				pinky->setEnemy_mode(2);
			}
			if (inky->getEnemy_mode() == 1)
			{
				inky->setEnemy_Image_Location(583, 65);
				inky->setEnemy_mode(2);
			}
			if (clyde->getEnemy_mode() == 1)
			{
				clyde->setEnemy_Image_Location(583, 65);
				clyde->setEnemy_mode(2);
			}
		}

	}

	if (
		(P_x == blinky->getEnemy_Location_x() && P_y == blinky->getEnemy_Location_y() && blinky->getEnemy_mode() == 1)||
		(P_x == pinky ->getEnemy_Location_x() && P_y == pinky ->getEnemy_Location_y() && pinky ->getEnemy_mode() == 1)||
		(P_x == inky  ->getEnemy_Location_x() && P_y == inky  ->getEnemy_Location_y() && inky  ->getEnemy_mode() == 1)||
		(P_x == clyde ->getEnemy_Location_x() && P_y == clyde ->getEnemy_Location_y() && clyde ->getEnemy_mode() == 1)
	   )
	{
		life_cnt -= 1;
		m_Player->setPlayer_Location(338, 482, 1);
	}
	
	
}

void PlayScene::victory(HDC hdc)
{
	int victory_num = 0;

	for (it_map = m_map.begin(); it_map != m_map.end(); it_map++)
	{
		if (((*it_map)->object_num == 3 || (*it_map)->object_num == 4) && (*it_map)->create == false)
		{
			victory_num += 1;
		}

	}

	if (victory_num == 244 || life_cnt == 0)
	{
		Free();
		m_Single->Scene_Change(Scene_Enum::E_Menu_Scene);
		Initialize();
	}


}

void PlayScene::teleport(int P_x, int P_y)
{
	if (P_x == 546 && P_y == 338)
	{
		m_Player->setPlayer_Location(-416, 0, 0);
	}
	else if (P_x == 114 && P_y == 338)
	{
		m_Player->setPlayer_Location(416, 0, 0);
	}
}



bool PlayScene::move_check(int object_x, int object_y, int dir)
{

	switch (dir)
	{
	case RIGHT:

		object_x += pac_move;

		break;

	case LEFT:

		object_x -= pac_move;

		break;

	case UP:

		object_y -= pac_move;

		break;

	case DOWN:

		object_y += pac_move;

		break;

	}


	for (it_map = m_map.begin(); it_map != m_map.end(); it_map++)
	{
		if ((*it_map)->pos.x == object_x && (*it_map)->pos.y == object_y && (*it_map)->object_num != 1 && (*it_map)->object_num != 7)
		{
			return true;
		}
	}

	return false;
}



void PlayScene::input_dir(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_RIGHT:
		temp_dir = RIGHT;
		break;

	case VK_LEFT:
		temp_dir = LEFT;
		break;

	case VK_UP:
		temp_dir = UP;
		break;

	case VK_DOWN:
		temp_dir = DOWN;

		break;
	}

}

void PlayScene::PacmanMove(UINT message, int dir)
{

	int	P_x = m_Player->getPlayer_Location_x();
	int	P_y = m_Player->getPlayer_Location_y();
	int x = 0, y = 0;

	switch (dir)
	{
	case RIGHT:

		if (move_check(P_x, P_y, RIGHT))
		{
			P_dir = dir;
		}
		else
		{
			if (move_check(P_x, P_y, P_dir))
			{
				P_dir;
			}
		}
		break;

	case LEFT:

		if (move_check(P_x, P_y, LEFT))
		{
			P_dir = dir;
		}
		else
		{
			if (move_check(P_x, P_y, P_dir))
			{
				P_dir;
			}

		}
		break;

	case UP:

		if (move_check(P_x, P_y, UP))
		{
			P_dir = dir;
		}
		else
		{
			if (move_check(P_x, P_y, P_dir))
			{
				P_dir;
			}

		}
		break;

	case DOWN:

		if (move_check(P_x, P_y, DOWN))
		{
			P_dir = dir;
		}
		else
		{
			if (move_check(P_x, P_y, P_dir))
			{
				P_dir;
			}
		}
		break;
	}


	if (message == WM_TIMER)
	{
		switch (P_dir)
		{
		case RIGHT:
			if (move_check(P_x, P_y, RIGHT))
			{
				draw_dir = RIGHT;
				x = pac_move;
			}
			else
			{
				x = 0;
			}
			break;

		case LEFT:
			if (move_check(P_x, P_y, LEFT))
			{
				draw_dir = LEFT;
				x = -pac_move;
			}
			else
			{
				x = 0;
			}
			break;

		case UP:
			if (move_check(P_x, P_y, UP))
			{
				draw_dir = UP;
				y = -pac_move;
			}
			else
			{
				y = 0;
			}
			break;

		case DOWN:
			if (move_check(P_x, P_y, DOWN))
			{
				draw_dir = DOWN;
				y = pac_move;
			}
			else
			{
				y = 0;
			}
			break;

		}
		m_Player->setPlayer_Location(x, y, 0);

		teleport(P_x, P_y);
		pacman_eat(P_x, P_y);
	}

}


void PlayScene::EnemyMove(UINT message, int P_x, int P_y, Enemy* name)
{
	int E_x = name->getEnemy_Location_x(), E_y = name->getEnemy_Location_y(), E_dir = name->getEnemy_dir();

	POINT start = { E_x, E_y };
	POINT dest = { 0,0 };

	static int p_move_cnt = 0;
	static int i_move_cnt = 0;
	static int c_move_cnt = 0;

	switch (name->getEnemy_mode())
	{
	case 1:
	{
		if (name == blinky)
		{
			dest = { P_x, P_y };
		}
		
		if (name == pinky)
		{
			
			if (p_move_cnt >= 20)
			{
				dest = { P_x, P_y };
			}
			else
			{
				static int p_dest_x = 306, p_dest_y = 354;

				if (pinky->getEnemy_Location_x() == 306 && pinky->getEnemy_Location_y() == 354)
				{
					p_dest_x = 306;
					p_dest_y = 338;

					p_move_cnt += 1;
				}
				else if (pinky->getEnemy_Location_x() == 306 && pinky->getEnemy_Location_y() == 338)
				{
					p_dest_x = 306;
					p_dest_y = 354;
				}

				dest = { p_dest_x, p_dest_y };
			}

		}


		if (name == inky)
		{
		
			if (i_move_cnt >= 30)
			{
				dest = { P_x, P_y };
			}
			else
			{

				static int i_dest_x = 322, i_dest_y = 354;

				if (inky->getEnemy_Location_x() == 322 && inky->getEnemy_Location_y() == 354)
				{
					i_dest_x = 322;
					i_dest_y = 338;
					i_move_cnt += 1;
				}
				else if (inky->getEnemy_Location_x() == 322 && inky->getEnemy_Location_y() == 338)
				{
					i_dest_x = 322;
					i_dest_y = 354;
				}

				dest = { i_dest_x, i_dest_y };
			}
		}

		if (name == clyde)
		{
			

			if (c_move_cnt >= 40)
			{
				dest = { P_x, P_y };
			}
			else
			{

				static int c_dest_x = 338, c_dest_y = 354;

				if (clyde->getEnemy_Location_x() == 338 && clyde->getEnemy_Location_y() == 354)
				{
					c_dest_x = 338;
					c_dest_y = 338;
					c_move_cnt += 1;
				}
				else if (clyde->getEnemy_Location_x() == 338 && clyde->getEnemy_Location_y() == 338)
				{
					c_dest_x = 338;
					c_dest_y = 354;
				}

				dest = { c_dest_x, c_dest_y };
			}
		}

		


	}
	break;

	case 2:
	{
		
			if (name == blinky)
			{
				static int b_dest_x = 130, b_dest_y = 130;
				static int gost_cnt = 4;

				if (blinky->getEnemy_Location_x() == 130 && blinky->getEnemy_Location_y() == 130)
				{
					b_dest_x = 210;
					b_dest_y = 194;
					gost_cnt -= 1;
				}
				else if (blinky->getEnemy_Location_x() == 210 && blinky->getEnemy_Location_y() == 194)
				{
					b_dest_x = 130;
					b_dest_y = 130;
					gost_cnt -= 1;
				}

				if (gost_cnt == 0)
				{
					blinky->setEnemy_Image_Location(452, 65);
					blinky->setEnemy_mode(1);
					gost_cnt = 4;
				}

				dest = { b_dest_x, b_dest_y };
			}



			if (name == pinky)
			{
				static int p_dest_x = 130, p_dest_y = 578;
				static int gost_cnt = 3;

				if (pinky->getEnemy_Location_x() == 130 && pinky->getEnemy_Location_y() == 578)
				{
					p_dest_x = 274;
					p_dest_y = 530;
					gost_cnt -= 1;
				}
				else if (pinky->getEnemy_Location_x() == 274 && pinky->getEnemy_Location_y() == 530)
				{
					p_dest_x = 130;
					p_dest_y = 578;
					gost_cnt -= 1;
				}

				if (gost_cnt == 0)
				{
					pinky->setEnemy_Image_Location(452, 81);
					pinky->setEnemy_mode(1);
					gost_cnt = 3;
				}

				dest = { p_dest_x, p_dest_y };


			}

			if (name == inky)
			{
				static int i_dest_x = 450, i_dest_y = 130;
				static int gost_cnt = 3;

				if (inky->getEnemy_Location_x() == 530 && inky->getEnemy_Location_y() == 194)
				{
					i_dest_x = 450;
					i_dest_y = 130;
					gost_cnt -= 1;
				}
				else if (inky->getEnemy_Location_x() == 450 && inky->getEnemy_Location_y() == 130)
				{
					i_dest_x = 530;
					i_dest_y = 194;
					gost_cnt -= 1;
				}


				if (gost_cnt == 0)
				{
					inky->setEnemy_Image_Location(452, 97);
					inky->setEnemy_mode(1);
					gost_cnt =3;
				}

				dest = { i_dest_x, i_dest_y };

			}

			if (name == clyde)
			{
				static int c_dest_x = 530, c_dest_y = 578;
				static int gost_cnt = 2;

				if (clyde->getEnemy_Location_x() == 402 && clyde->getEnemy_Location_y() == 514)
				{
					c_dest_x = 530;
					c_dest_y = 578;
					gost_cnt -= 1;
				}
				else if (clyde->getEnemy_Location_x() == 530 && clyde->getEnemy_Location_y() == 578)
				{
					c_dest_x = 402;
					c_dest_y = 514;
					gost_cnt -= 1;
				}

				if (gost_cnt == 0)
				{
					clyde->setEnemy_Image_Location(452, 113);
					clyde->setEnemy_mode(1);
					gost_cnt = 2;
				}

				dest = { c_dest_x, c_dest_y };

			}


	}
		break;

	case 3:
	{
		dest = { 322 , 338 };


		if (blinky->getEnemy_Location_x() == 322 && blinky->getEnemy_Location_y() == 338)
		{
			blinky->setEnemy_Image_Location(452, 65);
			blinky->setEnemy_mode(1);
		}

		if (pinky->getEnemy_Location_x() == 322 && pinky->getEnemy_Location_y() == 338)
		{
			pinky->setEnemy_Image_Location(452, 81);
			pinky->setEnemy_mode(1);
		}

		if (inky->getEnemy_Location_x() == 322 && inky->getEnemy_Location_y() == 338)
		{
			inky->setEnemy_Image_Location(452, 97);
			inky->setEnemy_mode(1);
		}

		if (clyde->getEnemy_Location_x() == 322 && clyde->getEnemy_Location_y() == 338)
		{
			clyde->setEnemy_Image_Location(452, 113);
			clyde->setEnemy_mode(1);
		}


	}
		break;


	}


	std::list<POINT>_vEnemyMove;

	_vEnemyMove = EnemyPath->GetPath(start, dest);
		
	if (_vEnemyMove.size())
	{	
		name->setEnemy_Location(_vEnemyMove.front().x, _vEnemyMove.front().y, 0);
		_vEnemyMove.erase(_vEnemyMove.begin());	
	}


}

void PlayScene::life_draw(HDC hdc)
{
	BITMAP lifeBack;
	HBITMAP life;

	HBITMAP h01dBitmap = nullptr;
	HDC hMemDC = nullptr;

	life = (HBITMAP)LoadImage(NULL, TEXT("images/life.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(life, sizeof(BITMAP), &lifeBack);

	if (!hMemDC)
		hMemDC = CreateCompatibleDC(hdc);

	if (life == NULL)
		life = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);

	int bx = lifeBack.bmWidth/3;
	int by = lifeBack.bmHeight;


	h01dBitmap = (HBITMAP)SelectObject(hMemDC, life);
	TransparentBlt(hdc, 130, 610, bx*life_cnt, by, hMemDC, 0, 0, bx*life_cnt, by, RGB(255, 0, 255));
	SelectObject(hMemDC, h01dBitmap);
	DeleteDC(hMemDC);


}



