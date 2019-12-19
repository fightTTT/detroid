#pragma once
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

// 衝突のタイプ
enum class C_TYPE
{
	MOVE,		// 左右衝突
	UPDOWN		// 上下衝突
};

class CPoint
{
public:
	//　衝突用の点の初期化
	CPoint();
	CPoint(int index, Vec2 pos);
	CPoint(int index, Vec2 pos, Size size, C_TYPE type);
	~CPoint();

	void SetOffset(Size size);				// XY座標をずらす
	void SetOffsetX(float size);			// X座標をずらす
	void SetOffsetX(float size, int index);	// 指定されたX座標をずらす
	void SetOffsetY(float size);			// Y座標をずらす
	void SetOffsetY(float size, int index);	// 指定されたY座標をずらす
	const Vec2 GetPoint(int index);			// 指定された点の座標をとる
	const int GetPointSize(void);			// コンテナの要素数を取る
	const std::vector<Vec2> GetGroup(void);	// ベクトル配列を取る
private:
	std::vector<Vec2> _point;
};