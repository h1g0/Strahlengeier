#ifndef __PLAYERBULLET_H
#define __PLAYERBULLET_H

#include <DxLib.h>
#include "Common.h"
#include "Particle.h"
/*#################################

	自弾関係

#################################*/

class PlayerBullet: public Particle{
public:
	struct Point{
		double x;
		double y;
		void Set(double X, double Y){
			x = X;
			y = Y;
		}
	};
private:
	int _hitRect; //当たり判定の大きさ
	int _power; //威力
	static const int _NORMAL_POW = 1;
	static const int _NORMAL_RECT = 32;
	static const int _THICKNESS = 32; //画像の一辺の長さ
	PlayerBullet* _B4Ptr; //レーザーとして繋げるための前の弾へのポインタ
	PlayerBullet* _afterPtr;//レーザーとして繋げるための後ろの弾へのポインタ
	Point _back[2]; //四角形の4辺のうちの後ろ2点(0: 左 1: 右)
public:

	void SetHitXY(int rect){
		_hitRect = rect;
	}
	int GetHitRect() const{return _hitRect;}
	int GetPower() const{return _power;}
	void SetPower(int pow){_power = pow;}
	void SetB4Ptr(PlayerBullet* ptr){_B4Ptr = ptr;}
	void SetAfterPtr(PlayerBullet* ptr){_afterPtr = ptr;}
	Point GetBack(int id){
		if(id<0 || id>1){
			Point err;
			err.Set(0,0);
			return err;
		}else{
			return _back[id];
		}
	}
	//コンストラクタ
	PlayerBullet(){
		_B4Ptr=nullptr;
		_afterPtr=nullptr;
		_back[0].Set(0,0);
		_back[1].Set(0,0);
		SetAngle(270 * RAD);
		SetSpeed(10);
		SetVxVyFromSpeedAngle();
		SetHitXY(16);
		SetPower(1);
	}
	void Move();
	void Draw();
	void SetDead(){
		if(_afterPtr != nullptr){
			_afterPtr->SetB4Ptr(nullptr);
		}
		Particle::SetDead();
	}
};

class PBulletGroup{
private:
	std::vector<PlayerBullet> _unit;
public:
	void SetLimit(int size){ _unit.resize(size); }
	int GetLimit() const{ return _unit.size(); }

	PBulletGroup(){
		SetLimit(100);
	}

	PBulletGroup(int size){
		SetLimit(size);
	}

	int imgCommon;

	PlayerBullet* Create(double x, double y, //誕生時の座標
		double angle, double speed, //誕生時の角度と速度
		int image, //画像
		void(*BornFunc)(Particle& Obj) = nullptr, //誕生エフェクト
		void(*MoveFunc)(Particle& Obj) = nullptr, //動作スクリプト
		void(*DeadFunc)(Particle& Obj) = nullptr, //死亡エフェクト
		double drawExp = 1.0, //拡大率
		int drawParam = 255, //描画パラメータ
		bool deletable = true, //画面外に飛び出した時に消去するか？
		PlayerBullet* beforePtr = nullptr //前の弾へのポインタ(初弾ならnullptr)
		);

	//消す
	void Delete(int Index);
	//すべて消す
	void DeleteAll();

	void SetDead(int index);
	void SetDeadAll();

	//動かす函数。現在存在するパーティクルの数を返す。
	int Move();
	void Draw();

	void SetPowerAll(int pow = 1);
	void SetHitXYAll(int r = 16);
	//全ての弾に対して当たり判定。戻り値は当たった事によって発生したダメージの総計
	int HitCheckAll(double x, double y, int width, int height);

};

#endif