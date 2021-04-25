#pragma once

class UI;
class Menu_UI;
class Play_UI;
class End_UI;


class Scene
{
public:

	UI* m_UI = nullptr;
	Menu_UI* m_Menu_UI = new Menu_UI;
	Play_UI* m_Play_UI = new Play_UI;
	End_UI* m_End_UI = new End_UI;


	Scene();
	virtual ~Scene();


	virtual void Initialize(void) = 0;
	virtual void Update(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Rendering(HWND hWnd, HDC hdc) = 0;
	virtual void Free(void) = 0;
};
