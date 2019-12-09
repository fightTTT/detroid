#pragma once
#include "GeometryObject.h"
class Plane :
	public GeometryObject
{
public:
	Plane();
	Vector3 normal;	// 法線ベクトル
	float	offset; // 原点からのオフセット
	Plane(Vector3& n,float o,const Material& m):normal(n),offset(o),GeometryObject(m){}
	~Plane();

	///当たり判定 
	///@param ray 視線から始まる直線 
	///@param hitpos[out] 衝突点 
	///@param norm[out] 衝突点の法線ベクトル 
	///@retval true 当たった 
	///@retval false 外れた 
	bool CheckHit(const RayLine& ray, Position3& hitPos, Vector3& normal)const override;

	//マテリアルを返します 
	const Material& GetMaterial()const override;

	float DistanceFromStart(const Position3& pos)override;
};

