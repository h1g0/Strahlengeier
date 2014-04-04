#include "Common.h"
#include <DxLib.h>
#include<string>
bool isDebug = true;

//‰æ–Ê“à‚É‚ ‚é‚©H
bool InScreen(double x, double y, int marginX, int marginY){
	if(x >= 0 + marginX &&
	   x <= SCR_WIDTH - marginX &&
	   y >= 0 + marginY &&
	   y <= SCR_HEIGHT - marginY
	   ){return true;}
	else{return false;}
}

//‰æ–Ê“à‚É–³‚©‚Á‚½‚ç•â³‚·‚é
void Fix2Screen(double& x, double& y, int marginX , int marginY){
	if(x < marginX){x = marginX;}
	else if(x > SCR_WIDTH - marginX){x = SCR_WIDTH - marginX;}
	if(y < marginY){y = marginY;}
	else if(y > SCR_HEIGHT - marginY){y = SCR_HEIGHT - marginY;}
}

//‚‘¬‹éŒ`“–‚½‚è”»’è
bool HitCheck(double x1,double y1, int Width1,int Height1,
			  double x2,double y2, int Width2,int Height2){
	if( ((Width1+Width2) >> 1 >= std::abs(x2-x1)) &&
		((Height1+Height2) >> 1 >= std::abs(y2-y1)) ){
		return true;
	}else{
		return false;
	}
}

void LoadImg(int& dist, std::string filePath){
	if(dist!=0){DeleteGraph(dist);}
	dist=LoadGraph(filePath.c_str());
}
void UnloadImg(int& dist){
	DeleteGraph(dist);
	dist=0;
}
void LoadSnd(int& dist, std::string filePath){
	if(dist!=0){DeleteSoundMem(dist);}
	dist=LoadSoundMem(filePath.c_str());
}
void UnloadSnd(int& dist){
	DeleteSoundMem(dist);
	dist=0;
}