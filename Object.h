#ifndef __OBJECT_H
#define __OBJECT_H
#include<vector>
#include "Common.h"
/*############################
 *
 *オブジェクトクラス
 *
 *#########################*/

class Object{
public:
	//状態を示すEnumerator(いにゅめれーたーって発音しにくいよね！)
	enum State{
		NotExist,
		Born,
		Exist,
		Dead
	};

private:
	State _state; //状態
	double _x,_y; //座標
	double _vx,_vy; //ベロシティ
	int _frame; //フレーム
	int _image; //画像
public:
	//コンストラクタ
	Object():
	_state(NotExist),
	_x(0),_y(0),
	_vx(0),_vy(0),
	_frame(0),
	_image(0)
	{}

	Object(State state, double x, double y, int image, double vx = 0, double vy = 0):
	_state(state),
	_x(x),_y(y),
	_vx(vx),_vy(vy),
	_frame(0),
	_image(image)
	{}

	//セッタ・ゲッタ
	void SetState(State state){
		_frame = 0;
		_state = state;
	}
	State GetState() const{ return _state; }

	void SetX(double x){ _x=x; }
	void SetY(double y){ _y=y; }
	void SetXY(double x, double y){
		_x=x;
		_y=y;
	}
	double GetX() const{return _x;}
	double GetY() const{return _y;}
	void GetXY(double& x, double& y) const{
		x=_x;
		y=_y;
	}
	void AddX(double x){
		_x += x;
	}

	void AddY(double y){
		_y += y;
	}

	void SetVx(double vx){ _vx=vx; }
	void SetVy(double vy){ _vy=vy; }
	void SetVxVy(double vx, double vy){
		_vx=vx;
		_vy=vy;
	}
	double GetVx() const{return _vx;}
	double GetVy() const{return _vy;}
	void GetVxVy(double& vx, double& vy) const{
		vx=_vx;
		vy=_vy;
	}

	void AddVxVy2XY(){
		_x += _vx;
		_y += _vy;
	}

	void AddFrame(){
		_frame++;
		//オーバーフロー防止のため、30分を超えたら1に戻る
		if(_frame==18001){_frame = 1;}
	}
	void SetFrame(int frame){_frame = frame;}
	int GetFrame() const{return _frame;}

	void SetImage(int imageHandle){
		_image = imageHandle;
	}
	int GetImage() const{
		return _image;
	}

	//発生させる
	virtual void SetBorn(){
		_frame = 0;
		_state = Born;
	}

	//死んだ状態にする
	virtual void SetDead(){
		_frame = 0;
		_state = Dead;
	}
};
#endif