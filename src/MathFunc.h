#ifndef __MATHFUNC_H
#define __MATHFUNC_H

#define PI 3.1415926535897932384626433832795 //��=3.14159265...
#define RIGHT_ANGLE PI/2 //��/2=90��
#define PI_F 3.1415926535897932384626433832795f
#define RIGHT_ANGLE_F PI_F/2.0f
#define RAD PI/180

//======================
//�����O�p�֐��֌W
//======================
#define TABLESIZE 128 //2�̏搔�ł��邱��
#define SUBBIT    8
#define SUBINDEX  (1 << SUBBIT)
#define I_PI      (TABLESIZE * SUBINDEX * 2)
#define I_HPI     (TABLESIZE * SUBINDEX)

namespace MyMath{
	//�O�p�֌W�萔
	extern const unsigned short sin_table[];

	double sin(double rad);
	float sin(float rad);

	double cos(double rad);
	float cos(float rad);

	extern const double atan_table[];
	extern const int atan_table_num;
	double atan2(double y, double x);
	float atan2(float y, float x);
}

#endif