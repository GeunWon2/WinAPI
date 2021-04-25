#pragma once
class UI
{

public:
	UI();
	virtual ~UI();

	virtual void Initialize(void) = 0;
	virtual void Draw_UI(HDC hdc) = 0;


};

