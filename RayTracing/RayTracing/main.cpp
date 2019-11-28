#include<dxlib.h>
#include<cmath>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//Vector3 N;
float  Nmag;
float spacular;

//ヒントになると思って、色々と関数を用意しておりますが
//別にこの関数を使わなければいけないわけでも、これに沿わなければいけないわけでも
//ありません。レイトレーシングができていれば構いません。


///レイ(光線)と球体の当たり判定
///@param ray (視点からスクリーンピクセルへのベクトル)
///@param sphere 球
///@hint レイは正規化しといたほうが使いやすいだろう
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp,float& distance,Vector3& normal,Vector3& hitPos) 
{
	//レイが正規化済みである前提で…
	//
	//視点から球体中心へのベクトルを作ります
	Vector3 center = sp.pos - eye;
	//
	//中心から視線への内積をとります＝＞ベクトル長
	float shadowLength = Dot(ray, center);
	//Vector3 shadowRay = ray * syaeityou;
	//Vector3 shadowRay2 = eye + shadowRay;
	//// C-R ベクトルを作る
	//Vector3 suisen = sp.pos - shadowRay2;
	Vector3 shadowRay = ray * shadowLength;
	Vector3 verticalLine = center - shadowRay;
	
	
	if (verticalLine.Magnitude() > sp.radius)
	{
		return false;
	}
	// ベクトル長と半径を比較して、半径以下だったらtrue
	
	// 三平方の定理を使って交点の座標を調べる
	hitPos = eye + ray * ((shadowLength - sqrt(sp.radius * sp.radius - verticalLine.Magnitude()*verticalLine.Magnitude())));
	
	// 法線を求める
	normal = hitPos - sp.pos;
	normal.Normalize();

	//Light = Light - p;
	//Light.Normalize();
	// ライトの向きを決める
	Vector3 Light = Vector3(-1,1, 1);


	Nmag = Dot(Light, normal);
	if (Nmag <= 0)
	{
		normal = sp.pos - hitPos;
		normal.Normalize();
	}

	auto reflect = Light - normal * Nmag * 2;

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
	if (verticalLine.Magnitude() <= sp.radius)
	{
		distance = (shadowLength - (sqrt(sp.radius * sp.radius - verticalLine.Magnitude()*verticalLine.Magnitude())));
		return true;
	}
	else
	{
		return true;
	}

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


void DrawPlane(Vector3 eyePos,Vector3 ray,int screenPosX,int screenPosY)
{
	Plane plane;
	plane.normal = Vector3(0, 1, 0);
	plane.offSet = 100.0f;

	auto vn = Dot(-ray, plane.normal);
	if (vn <= 0)
	{
		return;
	}
	auto hitPosLen = (plane.offSet - Dot(eyePos, plane.normal)) / vn;
	auto hitPos = ray * hitPosLen + eyePos;
	auto a = eyePos - hitPos;

	
	if (Dot(a,plane.normal) > 0.0f)
	{
		unsigned int color = 0x000000;

		if ((int)hitPos.z / 10 % 2 && (int)hitPos.x / 10 % 2
			|| (int)hitPos.z / 10 % 2 == 0 && (int)hitPos.x / 10 % 2 == 0)
		{
			// 11
			color = 0xffffff;
		}

		if((int)hitPos.x <= 0)
		{ 
			color = ~color;
		}

		if ((int)hitPos.z <= 0)
		{
			color = ~color;
		}


		DrawPixel(screenPosX, screenPosY, color);
	}
}

int ReflectHitColor(Vector3 eyePos, Vector3 ray)
{
	Plane plane;
	plane.normal = Vector3(0, 1, 0);
	plane.offSet = 100.0f;

	auto vn = Dot(-ray, plane.normal);
	if (vn <= 0)
	{
		return 1;
	}
	auto hitPosLen = (plane.offSet - Dot(eyePos, plane.normal)) / vn;
	auto hitPos = ray * hitPosLen + eyePos;
	auto a = eyePos - hitPos;

	if (Dot(a, plane.normal) > 0.0f)
	{
		unsigned int color = 0x000000;

		if ((int)hitPos.z / 10 % 2 && (int)hitPos.x / 10 % 2
			|| (int)hitPos.z / 10 % 2 == 0 && (int)hitPos.x / 10 % 2 == 0)
		{
			// 11
			color = 0xffffff;
		}

		if ((int)hitPos.x <= 0)
		{
			color = ~color;
		}

		if ((int)hitPos.z <= 0)
		{
			color = ~color;
		}
			
		return color;
	}

	return 1;
}

///レイトレーシング
///@param eye 視点座標
///@param sphere 球オブジェクト(そのうち複数にする)
void RayTracing(const Position3& eye,const Sphere& sphere) 
{
	for (int y = 0; y < screen_height; ++y) {//スクリーン縦方向
		for (int x = 0; x < screen_width; ++x) {//スクリーン横方向
			//①視点とスクリーン座標から視線ベクトルを作る
			Vector3 ray =Vector3(x- (screen_width /2), -y +( screen_height / 2) ,0)- eye;
			//②正規化しとく
			ray.Normalize();
			float distance = 0;

			DrawPlane(eye, ray, x, y);
	
			//③IsHitRay関数がTrueだったら白く塗りつぶす
			//※塗りつぶしはDrawPixelという関数を使う。

			Vector3 normal = { 0,0,0 };
			Vector3 hitPos = { 0,0,0 };

			if ((IsHitRayAndObject(eye,ray,sphere, distance,normal,hitPos)))
			{
				Vector3 reflectVec = ReflectedVector(eye, normal);

				float albedo[3] = { 0.4f , 0.7f, 1.0f };
				float diffuse[3] = { Nmag * albedo[0],Nmag * albedo[1],Nmag * albedo[2] };
				float color[3] = { diffuse[0] + spacular,diffuse[1] + spacular,diffuse[2] + spacular };

				for (int i = 0; i < 3; i++)
				{
					color[i] = Clamp(color[i]* ReflectHitColor(hitPos, reflectVec));
				}

				int b = 255;
				float c = (400.f - distance) / 100.f;
				
				DrawPixel(x, y, GetColor(b * color[0], b * color[1], b * color[2]));
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

	DrawBox(0, 0, screen_width, screen_height, 0xAAC863,true);

	RayTracing(Vector3(0, 0, 300), Sphere(100, Position3(0, 0, -100)));

	WaitKey();
	DxLib_End();
}