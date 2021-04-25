#include "stdafx.h"

void FindPath::GetMap(int _Map[][28])
{
	for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x < 28; x++)
		{
			MapData[y][x] = _Map[y][x];
		}
	}
}

std::list<POINT> FindPath::GetPath(POINT start, POINT end)
{
	this-> Release();
	
	if (Overlap_Start_End(start, end))
	{

		return PathList;
	}

	if (!Exception(end))
		return PathList;

	NodeInfo* _Parent = new NodeInfo(start, nullptr, 0, end);
	CloseList.push_back(_Parent);
	
	NodeInfo* FindPath = Recursive_FindPath(_Parent, end);

	while (FindPath->getParent() != NULL)
	{
		PathList.insert(PathList.begin(), FindPath->getPosition());
		FindPath = FindPath->getParent();
	}
	
	return PathList;
}


NodeInfo* FindPath::Recursive_FindPath(NodeInfo* parent, POINT end)
{

	if (Overlap_Start_End(parent->getPosition(), end))
	{
		return parent;
	}

	for (int i = 0; i < 4; i++)
	{
		POINT _ChildPos = { parent->getPosition().x + Direction[i].x, parent->getPosition().y + Direction[i].y };

		if (Exception(_ChildPos))
		{
			NodeInfo* _Child = new NodeInfo(_ChildPos, parent, parent->getCostG() + 1, end);
			AppOpenList(_Child);
		}
	}

	NodeInfo* _Best = OpenList.front();
	for (auto it : OpenList)
	{
		if (_Best->getCostF() >= it->getCostF())
		{
			_Best = it;
		}
	}

	OpenList.remove(_Best);

	CloseList.push_back(_Best);
	

	return Recursive_FindPath(_Best, end);
}


void FindPath::Release()
{
	if (OpenList.size())
		OpenList.clear();

	if (CloseList.size())
		CloseList.clear();

	if (PathList.size())
		PathList.clear();
}


bool FindPath::AppOpenList(NodeInfo* _node)
{

	for (auto it : CloseList)
	{
		if (Overlap_Start_End(it->getPosition(), _node->getPosition()))
		{
			return true;
		}
	}


	for (auto it : OpenList)
	{
		if (Overlap_Start_End(it->getPosition(),_node->getPosition()))
		{

			if (it->getCostF() > _node->getCostF())
			{
				OpenList.remove(it);
				OpenList.push_back(_node);
				return true;
			}
		}
	}

	OpenList.push_back(_node);
	return true;
}


bool FindPath::Exception(POINT pos)
{
	if (pos.x < 114 || pos.x > 546)
	{
		return false;
	}

	if (pos.y < 114 || pos.y > 610)
	{
		return false;
	}


	int Xpos = (pos.x-114)/16;
	int Ypos = (pos.y-114)/16;


	if (MapData[Ypos][Xpos] == 1 
		|| MapData[Ypos][Xpos] == 9)
	{

		return false;
	}

	return true;
}