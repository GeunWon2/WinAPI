// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <algorithm>

#include <vector>
#include <list>

#include "Singleton.h"

#include "NodeInfo.h"
#include "FindPath.h"

#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "UI.h"
#include "Menu_UI.h"
#include "Play_UI.h"
#include "End_UI.h"


#include "Scene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "EndScene.h"

enum Direction { RIGHT = 1, LEFT, UP, DOWN };
#pragma comment(lib, "msimg32.lib")

// TODO: reference additional headers your program requires here
