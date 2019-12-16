#include <dxlib.h>
#include <cmath>
#include "Geometry.h"
#include "Plane.h"
#include "Sphere.h"
const int screen_width = 640;
const int screen_height = 480;

//Vector3 N;
float  Nmag;
float spacular;
Vector3 eyeVec;
constexpr int tileSize = 50;
Vector3	light(1, 1, 1);


//ヒントになると思って、色々と関数を用意しておりますが
//別にこの関数を使わなければいけないわけでも、これに沿わなければいけないわけでも
//ありません。レイトレーシングができていれば構いません。


///レイ(光線)と球体の当たり判定
///@param ray (視点からスクリーンピクセルへのベクトル)
///@param sphere 球
///@hint レイは正規化しといたほうが使いやすいだろう
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere1& sp,Vector3& normal,Vector3& hitPos) 
{
	////レイが正規化済みである前提で…
	////視点から球体中心へのベクトルを作ります
	//Vector3 center = sp.pos - eye;
	////
	////中心から視線への内積をとります＝＞ベクトル長
	//float shadowLength = Dot(ray, center);
	////Vector3 shadowRay = ray * syaeityou;
	////Vector3 shadowRay2 = eye + shadowRay;
	////// C-R ベクトルを作る
	////Vector3 suisen = sp.pos - shadowRay2;
	//Vector3 shadowRay = ray * shadowLength;
	//Vector3 verticalLine = center - shadowRay;
	//
	//
	//if (verticalLine.Magnitude() > sp.radius)
	//{
	//	return false;
	//}
	//// ベクトル長と半径を比較して、半径以下だったらtrue
	//
	//// 三平方の定理を使って交点の座標を調べる
	//hitPos = eye + ray * ((shadowLength - sqrt(sp.radius * sp.radius - verticalLine.Magnitude()*verticalLine.Magnitude())));
	//
	//eyeVec = hitPos - eye;
	//eyeVec.Normalize();
	//// 法線を求める
	//normal = hitPos - sp.pos;
	//normal.Normalize();

	//Light = Light - p;
	//Light.Normalize();
	// ライトの向きを決める
	Material material;
	RayLine rayLine(eye,ray);

	Sphere* sphere;
	sphere = new Sphere(sp.radius,sp.pos, material);

	if (!sphere->CheckHit(rayLine, hitPos, normal))
	{
		return false;
	}

	auto nvec = normal;

	Nmag = Dot(light, normal);
	if (Nmag <= 0)
	{
		nvec = sp.pos - hitPos;
		nvec.Normalize();
	}

	auto reflect = light - nvec * Nmag * 2;

	reflect.Normalize();
	auto notEyeVec = eye - hitPos;
	notEyeVec.Normalize();
	if (Dot(reflect, notEyeVec) < 0)
	{
		auto a = 0;
	}

	spacular = 0.7f * 1 * abs(std::pow(Dot(reflect, notEyeVec), 19));
	Nmag = 0.5 * Nmag;
	Nmag = Clamp(Nmag);
	

	// 当たっていたらdistatnceを求めてtrueを返す
	////if (verticalLine.Magnitude() <= sp.radius)
	////{
	////	//distance = (shadowLength - (sqrt(sp.radius * sp.radius - verticalLine.Magnitude()*verticalLine.Magnitude())));
	////	return true;
	////}
	////
	return true;

	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
}

///反射ベクトルを作って返す 
///@param inVec 入射ベクトル 
///@param normalVec 正規化済み法線ベクトル 
///@return 反射された入射ベクトル
Vector3 ReflectedVector(const Vector3& inVec, const Vector3& normalVec)
{
	return inVec - normalVec * Dot(inVec, normalVec) * 2;
}

Color PlaneColor(Vector3 hitPos)
{
	Color color1 = { 0.9,0.9,0.4 };
	Color color2 = {0.4,0.4,0.9 };
	Color color = color1;
	if ((int)hitPos.z / tileSize % 2 && (int)hitPos.x / tileSize % 2
		|| (int)hitPos.z / tileSize % 2 == 0 && (int)hitPos.x / tileSize % 2 == 0)
	{
		color = color2;
	}

	if((int)hitPos.x <= 0)
	{
		if (color == color1)
		{
			color = color2;
		}
		else
		{
			color = color1;
		}
	}
	if ((int)hitPos.z <= 0)
	{
		if (color == color1)
		{
			color = color2;
		}
		else
		{
			color = color1;
		}
	}
	
	return color;
}

Color DrawPlane(Vector3 eyePos,Vector3 ray,bool& isHit,Position3& hitPos)
{
	Plane1 plane;
	plane.normal = Vector3(0, 1, 0);
	plane.offSet = -100.0f;

	auto vn = Dot(-ray, plane.normal);

	if (vn <= 0)
	{
		isHit = false;
		return{ 0,0,0 };
	}
	auto hitPosLen = (Dot(eyePos, plane.normal) - plane.offSet) / vn;
	hitPos = ray * hitPosLen + eyePos;

	if (Dot(-ray,plane.normal) > 0.0f)
	{
		isHit = true;
		return PlaneColor(hitPos);
	}
	isHit = false;
	return {1,1,1};
}

Color ReflectHitColor(Vector3 eyePos, Vector3 reflectVec)
{
	Plane1 plane;
	plane.normal = Vector3(0, 1, 0);
	plane.offSet = -100.0f;

	auto vn = Dot(-reflectVec, plane.normal);
	// 床にあたってない時
	if (vn <= 0)
	{
		return { 1,1,1 };
	}
	auto hitPosLen = (Dot(eyePos, plane.normal) - plane.offSet) / vn;
	auto hitPos = reflectVec * hitPosLen + eyePos;

	if (Dot(-reflectVec, plane.normal) > 0.0f)
	{			
		return PlaneColor(hitPos);
	}

	return { 1,1,1 };
}
bool DrawShadow(const Sphere1& sp,const Position3& PlanePos, const Vector3& light)
{
	Vector3 center = sp.pos - PlanePos;
	
	Vector3 ray = light* -1;
	ray.Normalize();
	float shadowLength = Dot(ray, center);

	Vector3 shadowRay = ray * shadowLength;
	Vector3 verticalLine = center - shadowRay;


	if (verticalLine.Magnitude() > sp.radius)
	{
		return false;
	}

	return true;
}

///レイトレーシング
///@param eye 視点座標
///@param sphere 球オブジェクト(そのうち複数にする)
void RayTracing(const Position3& eye,const Sphere1& sphere) 
{
	for (int y = 0; y < screen_height; ++y) {//スクリーン縦方向
		for (int x = 0; x < screen_width; ++x) {//スクリーン横方向
			//①視点とスクリーン座標から視線ベクトルを作る
			Vector3 ray =Vector3(x - (screen_width /2), -y + ( screen_height / 2) ,0)- eye;
			//②正規化しとく
			ray.Normalize();
			bool DrawPlaneFlag = false;
			Position3 PlanePos = { 0,0,0 };

			auto plane = DrawPlane(eye, ray, DrawPlaneFlag, PlanePos);

			if (DrawShadow(sphere, PlanePos, light))
			{
				plane.x = plane.x + (-0.3);
				plane.y = plane.y + (-0.3);
				plane.z = plane.z + (-0.3);

			}
			plane *= 255;
			
			if (DrawPlaneFlag)
			{
				DrawPixel(x, y, GetColor(plane.x, plane.y, plane.z));
			}
	
			//③IsHitRay関数がTrueだったら白く塗りつぶす
			//※塗りつぶしはDrawPixelという関数を使う。

			Vector3 normal = { 0,0,0 };
			Position3 hitPos = { 0,0,0 };

			if ((IsHitRayAndObject(eye,ray,sphere, normal,hitPos)))
			{
				Vector3 reflectVec = ReflectedVector(ray, normal);
				reflectVec.Normalize();

				float albedo[3] = { 1.0f , 0.0f, 0.0f };
				float diffuse[3] = { Nmag * albedo[0],Nmag * albedo[1],Nmag * albedo[2] };
				float color[3] = { diffuse[0] + spacular + 0.1f,diffuse[1] + spacular + 0.1f,diffuse[2] + spacular + 0.1f };

				for (int i = 0; i < 3; i++)
				{
					color[i] = Clamp(color[i]);
				}
		
				int b = 255;

				auto hoge = GetColor(b * color[0]* ReflectHitColor(hitPos, reflectVec).x,
							b * color[1]* ReflectHitColor(hitPos, reflectVec).y,
							b * color[2] * ReflectHitColor(hitPos, reflectVec).z);
				/*float c = (400.f - distance) / 100.f;*/
				
				DrawPixel(x, y, hoge);
			}
		}
	}
}

int main() 
{
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(_T("1816019_作 明航"));
	DxLib_Init();

	float x = 0;

	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DrawBox(0, 0, screen_width, screen_height, 0xAAC863, true);
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x += 3.0f;
		}
		else if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x -= 3.0f;
		}

		RayTracing(Vector3(0, 0, 300), Sphere1(100, Position3(x, 0, 100)));
	}
	
	//WaitKey();
	
	DxLib_End();
}