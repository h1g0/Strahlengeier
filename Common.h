#ifndef __COMMON_H
#define __COMMON_H

#include<cmath>
#include "MathFunc.h"
#include<string>

//��ʂ̑傫��
#define SCR_WIDTH 640
#define SCR_HEIGHT 480

#define PJVERSION _T("ver. 0.4.0a")
#define PJTITLE _T("Strahlengeier "##PJVERSION) //�^�C�g��
#define PHI_F DX_PI_F
extern bool isDebug; //�f�o�b�O���[�h�H
extern int gDrawScr; //�ꎞ�I�ȕ`���

//��ʓ��ɂ��邩�H
bool InScreen(double x, double y, int marginX = 0, int marginY = 0);
//��ʓ��ɖ���������␳����
void Fix2Screen(double& x, double& y, int marginX = 0, int marginY = 0);
//������`�����蔻��
bool HitCheck(double x1,double y1, int Width1,int Height1,
			  double x2,double y2, int Width2,int Height2);

void LoadImg(int& dist, std::string filePath);
void UnloadImg(int& dist);
void LoadSnd(int& dist, std::string filePath);
void UnloadSnd(int& dist);
#endif