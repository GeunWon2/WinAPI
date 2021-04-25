#include "stdafx.h"
#include "Singleton.h"

extern Singleton* m_Single;

RECT rectView;
int time_cnt = 0;
Singleton::Singleton()
{
	m_Scene = nullptr;
	m_MenuScene = nullptr;
	m_PlayScene = nullptr;
	m_EndScene = nullptr;
	Initialize();
}


Singleton::~Singleton()
{

}

void Singleton::Initialize()
{
	m_Scene_Enum = Scene_Enum::E_Menu_Scene;
	m_Scene = m_MenuScene = new MenuScene; //== Scene m_MenuScene = new MenuScene;
	m_Scene->Initialize();

	
}

void Singleton::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	m_Scene->Update(message, wParam, lParam);
}

void Singleton::Draw(HWND hWnd, HDC hdc)
{
	client_rect(hWnd);
	m_Scene->Rendering(hWnd,hdc);
}

void Singleton::Scene_Change(Scene_Enum Next_Scene)
{
	switch (Next_Scene)
	{
		case Scene_Enum::E_Menu_Scene:
			m_Scene = m_MenuScene;
			m_Scene_Enum = Scene_Enum::E_Menu_Scene;
			break;

		case Scene_Enum::E_Play_Scene:
			if (m_PlayScene == nullptr)
			{
				m_PlayScene = new PlayScene;
			}
			m_Scene = m_PlayScene;
			m_Scene_Enum = Scene_Enum::E_Play_Scene;
			break;

		case Scene_Enum::E_End_Scene:

			break;

	}





}

void Singleton::client_rect(HWND hWnd)
{
	GetClientRect(hWnd, &rectView);
}
