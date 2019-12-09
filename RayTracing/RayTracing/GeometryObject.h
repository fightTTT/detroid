#pragma once
#include"Geometry.h"

//表面模様定義
enum class Pattern {
	none,		//模様なし 
	hstripe,	//縞模様(横) 
	vstripe,	//縞模様(縦) 
	checkered,	//市松模様(チェッカーフラッグ) 
	textured	//テクスチャマッピング 
};

//表面材質  
struct Material {
	Color diffuse;		//拡散反射成分(cosで表されるやつが返す色) 
	Color specular;		//鏡面反射成分(スペキュラで決定される表面材質が返す色) 
	Color ambient;		//環境光(ゲタ) 
	float specularity;	//スペキュラの強さ(乗数) 
	float reflectance;	//反射率 
	Pattern pattern;	//模様種別 

	Material() :
		diffuse(1, 1, 1), specular(0, 0, 0), ambient(0, 0, 0), specularity(0), reflectance(0) {}

	Material(const Color& diff,
			 const Color& spec,
			 const Color& amb,
			 float inSpecularity,
			 float inReflectance,
			 Pattern p = Pattern::none) : diffuse(diff), specular(spec), ambient(amb),
			 specularity(inSpecularity), reflectance(inReflectance),pattern(p) {}
};



class GeometryObject
{
public:
	GeometryObject();
	Material material;
	GeometryObject(Material m) :material(m) {};
	~GeometryObject();

	///当たり判定 
	///@param ray 視線から始まる直線 
	///@param hitpos[out] 衝突点 
	///@param normal[out] 衝突点の法線ベクトル 
	///@retval true 当たった 
	///@retval false 外れた
	virtual bool CheckHit(const RayLine& ray, Position3& hitPos, Vector3& normal)const = 0;

	///マテリアルを返します 
	///@return マテリアルオブジェクト
	virtual const Material& GetMaterial()const = 0;

	///指定座標からの最短距離(球だったら中心との距離-半径。平面だったら垂線の長さ) 
	///@param p 距離を測りたい点(座標) 
	virtual	float DistanceFromStart(const Position3& pos) = 0;
};

