#pragma once

class Scene;
class MenuScene;
class PlayScene;
class EndScene;

extern RECT rectView;
extern int time_cnt;

enum class Scene_Enum : size_t
{
	E_Menu_Scene,
	E_Play_Scene,
	E_End_Scene
};


class Singleton
{
private:
	Singleton();

	Scene_Enum m_Scene_Enum;

	Scene* m_Scene;
	MenuScene* m_MenuScene;
	PlayScene* m_PlayScene;
	EndScene* m_EndScene;


	

public:

	~Singleton();

	void Initialize();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Draw(HWND hWnd, HDC hdc);


	void Scene_Change(Scene_Enum Next_Scene);


	void client_rect(HWND hWnd);

	static Singleton* GetInstance()
	{
		static Singleton ins;
		return &ins;
	}


	

};

