#pragma once
#include "stdafx.h"

class NodeInfo
{
private:

	POINT _NodePosition;

	int _costG;
	int _costH;

	NodeInfo* _NodeParent;

public:
	NodeInfo(){};

	NodeInfo(POINT pos, NodeInfo* parent, int g, POINT h)
	{
		_NodePosition = pos;
		_NodeParent = parent;
		_costG = g;
		setCostH(h);
	}
	~NodeInfo(){};


	int getCostF(){ return _costG + _costH; }
	int getCostG(){ return _costG; }
	int getCostH(){ return _costH; }

	POINT getPosition(){ return _NodePosition; }
	int getPositionX(){ return _NodePosition.x; }
	int getPositionY(){ return _NodePosition.y; }


	NodeInfo* getParent(){ return _NodeParent; }


	void setCostG(int G){ _costG = G; }
	void setCostH(POINT endNode)
	{

		_costH = abs(endNode.x - _NodePosition.x) + abs(endNode.y - _NodePosition.y);
	}
};

inline bool Overlap_Start_End(POINT start, POINT end)
{
	if (start.x == end.x && start.y == end.y)
		return true;
	else
		return false;
}

