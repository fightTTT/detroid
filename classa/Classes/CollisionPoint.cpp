#include "CollisionPoint.h"

CPoint::CPoint()
{
}

CPoint::CPoint(int index, Vec2 pos)
{
	_point.reserve(index);
	for (int i = 0; i < index; i++)
	{
		_point.emplace_back(pos);
	}
}

CPoint::CPoint(int index, Vec2 pos, Size offset,C_TYPE type)
{
	_point.reserve(index);
	for (int i = 0; i < index; i++)
	{
		_point.emplace_back(pos);
	}

	if (type == C_TYPE::MOVE)
	{
		for (int i = 0; i < _point.size(); i++)
		{
			_point[i].x += offset.width;
			if (index != 1)
			{
				_point[i].y += offset.height - i * offset.height / (_point.size() - 1);
			}
		}
	}
	else
	{
		for (int i = 0; i < _point.size(); i++)
		{
			if (index != 1)
			{
				_point[i].x += offset.width - i * offset.width / (_point.size() - 1);
			}
			_point[i].y += offset.height;
		}
	}
}

CPoint::~CPoint()
{
}

void CPoint::SetOffset(Size size)
{
	for (int i = 0; i < _point.size(); i++)
	{
		_point[i] += size;
	}
}

void CPoint::SetOffsetX(float size)
{
	for (int i = 0; i < _point.size(); i++)
	{
		_point[i].x += size;
	}
}

void CPoint::SetOffsetX(float size, int index)
{
	_point[index].x += size;
}

void CPoint::SetOffsetY(float size)
{
	for (int i = 0; i < _point.size(); i++)
	{
		_point[i].y += size;
	}
}

void CPoint::SetOffsetY(float size, int index)
{
	_point[index].y += size;
}

const Vec2 CPoint::GetPoint(int index)
{
	return _point[index];
}

const int CPoint::GetPointSize(void)
{
	return _point.size();;
}

const std::vector<Vec2> CPoint::GetGroup(void)
{
	return _point;
}
