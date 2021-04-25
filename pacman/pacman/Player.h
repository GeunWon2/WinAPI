#pragma once
class Player
{
private:

	POINT Player_Location;

	HBITMAP hBackImage3;
	BITMAP bitBack3;


public:
	Player();
	~Player();

	int getPlayer_Location_x()
	{
		return Player_Location.x;
	}

	int getPlayer_Location_y()
	{
		return Player_Location.y;
	}

	
	void setPlayer_Location(int x, int y, int flag)
	{
		if (flag == 0)
		{
			this->Player_Location.x += x;
			this->Player_Location.y += y;
		}
		else if(flag ==1)
		{
			this->Player_Location.x = x;
			this->Player_Location.y = y;
		}
	}
	

	void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc, int dir);
	void Createbitmap();

};

