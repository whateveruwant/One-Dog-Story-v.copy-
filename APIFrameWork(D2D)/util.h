#pragma once
//==================================================================
//		## using namespace MY_UTIL ##
//==================================================================

//angle * DEG_TO_RAD
#define DEG_TO_RAD 0.017435f	//degree 1��(���Ȱ�)
#define PI 3.141592654f
#define PI2 (PI * 2)
#define PI3 (PI * 3)
#define PI4 (PI * 4)

#define PI_2	(PI / 2)
#define PI_4	(PI / 4)
#define PI_8	(PI / 8)
#define PI_16	(PI / 16)
#define PI_32	(PI / 32)

namespace MY_UTIL
{
	//���� ������ ����
	float getAngle(float startX, float startY, float endX, float endY);
	//���� ������ �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
}