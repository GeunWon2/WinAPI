#pragma once

class Player;
class Map;
class Enemy;
class FindPath;


class PlayScene: public Scene
{
	

	HBITMAP hBackImage2;
	BITMAP bitBack2;
	std::vector<map_info*>m_map;
	std::vector<map_info*>::iterator it_map;
	int P_dir;
	int draw_dir;

	int temp_dir;
	int life_cnt;

public:
	PlayScene();
	~PlayScene();

	

	Player* m_Player = new Player;

	Map* m_Map = new Map;
	Enemy* blinky = new Enemy;
	Enemy* pinky = new Enemy;
	Enemy* inky = new Enemy;
	Enemy* clyde = new Enemy;

	FindPath* EnemyPath = new FindPath;
	

	void Initialize(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Rendering(HWND hWnd, HDC hdc);
	void Free(void);
	bool move_check(int P_x, int P_y, int dir);

	void pacman_eat(int P_x, int P_y);

	void victory(HDC hdc);
	void teleport(int P_x, int P_y);

	void input_dir(WPARAM wParam);
	void PacmanMove(UINT message,int dir);



	void EnemyMove(UINT message, int P_x, int P_y, Enemy* name);

	void life_draw(HDC hWnd);

};

