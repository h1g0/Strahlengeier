#ifndef __COMMON_H
#define __COMMON_H

#include<cmath>
#include "MathFunc.h"
#include<string>

//画面の大きさ
#define SCR_WIDTH 640
#define SCR_HEIGHT 480

#define PJVERSION _T("ver. 0.4.0a")
#define PJTITLE _T("Strahlengeier "##PJVERSION) //タイトル
#define PHI_F DX_PI_F
extern bool isDebug; //デバッグモード？
extern int gDrawScr; //一時的な描画先

//画面内にあるか？
bool InScreen(double x, double y, int marginX = 0, int marginY = 0);
//画面内に無かったら補正する
void Fix2Screen(double& x, double& y, int marginX = 0, int marginY = 0);
//高速矩形当たり判定
bool HitCheck(double x1,double y1, int Width1,int Height1,
			  double x2,double y2, int Width2,int Height2);

void LoadImg(int& dist, std::string filePath);
void UnloadImg(int& dist);
void LoadSnd(int& dist, std::string filePath);
void UnloadSnd(int& dist);
#endif