#pragma once
class Play_UI: public UI
{
	BITMAP readyBack;
	HBITMAP ready;

	int load_UI;

public:
	Play_UI();
	~Play_UI();

	void Initialize(void);
	void Draw_UI(HDC hdc);

	void Createbitmap();



};

