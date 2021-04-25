#pragma once
class Enemy
{
private:

	POINT Enemy_Location;

	HBITMAP hBackImage4;
	BITMAP bitBack4;

	POINT Enemy_Image_Location;

	int Enemy_mode;
	int Enemy_dir;

public:
	Enemy();
	~Enemy();

	int getEnemy_Location_x()
	{
		return Enemy_Location.x;
	}

	int getEnemy_Location_y()
	{
		return Enemy_Location.y;
	}

	void setEnemy_Location(int x, int y, int flag)
	{
		if (flag == 1)
		{
			this->Enemy_Location.x += x;
			this->Enemy_Location.y += y;
		}
		else if (flag == 0)
		{
			Enemy_Location.x = x;
			Enemy_Location.y = y;

		}
	}

	int getEnemy_Image_Location_x()
	{
		return Enemy_Image_Location.x;
	}

	int getEnemy_Image_Location_y()
	{
		return Enemy_Image_Location.y;
	}

	void setEnemy_Image_Location(int x, int y)
	{
		this->Enemy_Image_Location.x = x;
		this->Enemy_Image_Location.y = y;
	}


	int getEnemy_dir()
	{
		return Enemy_dir;
	}

	void setEnemy_dir(int dir)
	{
		Enemy_dir = dir;
	}

	void setEnemy_mode(int mode)
	{
		Enemy_mode = mode;
	}
		

	int getEnemy_mode()
	{
		return Enemy_mode;
	}




	void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
	void Createbitmap();

};

