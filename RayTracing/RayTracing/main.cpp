#include<dxlib.h>
#include<cmath>
#include"Geometry.h"
const int screen_width = 640;
const int screen_height = 480;

//Vector3 N;
float  Nmag;
float spacular;

//�q���g�ɂȂ�Ǝv���āA�F�X�Ɗ֐���p�ӂ��Ă���܂���
//�ʂɂ��̊֐����g��Ȃ���΂����Ȃ��킯�ł��A����ɉ���Ȃ���΂����Ȃ��킯�ł�
//����܂���B���C�g���[�V���O���ł��Ă���΍\���܂���B


///���C(����)�Ƌ��̂̓����蔻��
///@param ray (���_����X�N���[���s�N�Z���ւ̃x�N�g��)
///@param sphere ��
///@hint ���C�͐��K�����Ƃ����ق����g���₷�����낤
bool IsHitRayAndObject(const Position3& eye,const Vector3& ray,const Sphere& sp,float& distance,Vector3& normal,Vector3& hitPos) 
{
	//���C�����K���ς݂ł���O��Łc
	//
	//���_���狅�̒��S�ւ̃x�N�g�������܂�
	Vector3 center = sp.pos - eye;
	//
	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	float shadowLength = Dot(ray, center);
	//Vector3 shadowRay = ray * syaeityou;
	//Vector3 shadowRay2 = eye + shadowRay;
	//// C-R �x�N�g�������
	//Vector3 suisen = sp.pos - shadowRay2;
	Vector3 shadowRay = ray * shadowLength;
	Vector3 verticalLine = center - shadowRay;
	
	
	if (verticalLine.Magnitude() > sp.radius)
	{
		return false;
	}
	// �x�N�g�����Ɣ��a���r���āA���a�ȉ���������true
	
	// �O�����̒藝���g���Č�_�̍��W�𒲂ׂ�
	hitPos = eye + ray * ((shadowLength - sqrt(sp.radius * sp.radius - verticalLine.Magnitude()*verticalLine.Magnitude())));
	
	// �@�������߂�
	normal = hitPos - sp.pos;
	normal.Normalize();

	//Light = Light - p;
	//Light.Normalize();
	// ���C�g�̌��������߂�
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
	

	// �������Ă�����distatnce�����߂�true��Ԃ�
	if (verticalLine.Magnitude() <= sp.radius)
	{
		distance = (shadowLength - (sqrt(sp.radius * sp.radius - verticalLine.Magnitude()*verticalLine.Magnitude())));
		return true;
	}
	else
	{
		return true;
	}

	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
}

///���˃x�N�g��������ĕԂ� 
///@param inVec ���˃x�N�g�� 
///@param normalVec ���K���ςݖ@���x�N�g�� 
///@return ���˂��ꂽ���˃x�N�g��
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

///���C�g���[�V���O
///@param eye ���_���W
///@param sphere ���I�u�W�F�N�g(���̂��������ɂ���)
void RayTracing(const Position3& eye,const Sphere& sphere) 
{
	for (int y = 0; y < screen_height; ++y) {//�X�N���[���c����
		for (int x = 0; x < screen_width; ++x) {//�X�N���[��������
			//�@���_�ƃX�N���[�����W���王���x�N�g�������
			Vector3 ray =Vector3(x- (screen_width /2), -y +( screen_height / 2) ,0)- eye;
			//�A���K�����Ƃ�
			ray.Normalize();
			float distance = 0;

			DrawPlane(eye, ray, x, y);
	
			//�BIsHitRay�֐���True�������甒���h��Ԃ�
			//���h��Ԃ���DrawPixel�Ƃ����֐����g���B

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
	SetMainWindowText(_T("1816019_�� ���q"));
	DxLib_Init();

	DrawBox(0, 0, screen_width, screen_height, 0xAAC863,true);

	RayTracing(Vector3(0, 0, 300), Sphere(100, Position3(0, 0, -100)));

	WaitKey();
	DxLib_End();
}