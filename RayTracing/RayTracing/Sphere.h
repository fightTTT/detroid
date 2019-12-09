#pragma once
#include "GeometryObject.h"
class Sphere :
	public GeometryObject
{
public:
	float radius;	// 半径
	Position3 pos;	// 中心座標
	Sphere():radius(0),pos(0,0,0),GeometryObject(Material()){}
	Sphere(float r,Position3& p,Material m):radius(r),pos(p),GeometryObject(m){}
	~Sphere();

	//当たり判定 
	bool CheckHit(const RayLine& ray, Position3& hitpos, Vector3& normal)const;

	//マテリアルを返します 
	const Material& GetMaterial()const;

	//指定座標からの最短距離(球だったら中心との距離-半径。平面だったら垂線の長さ) 
	float DistanceFromStart(const Position3& pos);
};

