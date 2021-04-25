#pragma once
#include "stdafx.h"
#include "NodeInfo.h"

class FindPath
{
private:

	std::list<NodeInfo*> OpenList;

	std::list<NodeInfo*> CloseList;

	std::list<POINT> PathList;

	POINT Direction[4];

	int MapData[31][28];


public:

	FindPath()
	{
		Direction[0] = POINT{ 0, 16 }; 
		Direction[1] = POINT{ 16, 0 }; 
		Direction[2] = POINT{ 0, -16 };
		Direction[3] = POINT{ -16, 0 }; 
	};

	~FindPath()
	{
		Release();
	};

	void GetMap(int _Map[][28]);


	std::list<POINT> GetPath(POINT start, POINT end);


private:

	bool AppOpenList(NodeInfo* _node);

	NodeInfo* Recursive_FindPath(NodeInfo* parent, POINT end);

	void Release();

	bool Exception(POINT pos);

};