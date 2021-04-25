#pragma once


struct map_info
{
	POINT pos;
	int object_num;
	bool create;


};


class Map
{
private:
	RECT rectView;

	HBITMAP hBackImage;
	BITMAP bitBack;

	HBITMAP hBackImage2;
	BITMAP bitBack2;



public:
	Map();
	~Map();

	void Initailize();

	void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc, std::vector<map_info*>m_map);
	void CreateBitmap();


};

