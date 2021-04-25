#pragma once
class MenuScene : public Scene
{

	HBITMAP hBackImage;
	BITMAP bitBack;


public:
	MenuScene();
	~MenuScene();

	int Select_Button_x, Select_Button_y, Select_Button_w, Select_Button_h;

	void Initialize(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Rendering(HWND hWnd, HDC hdc);
	void Free(void);
	
	void CreateBitmap();



};

