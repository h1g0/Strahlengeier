#ifndef __OBJECT_H
#define __OBJECT_H
#include<vector>
#include "Common.h"
/*############################
 *
 *�I�u�W�F�N�g�N���X
 *
 *#########################*/

class Object{
public:
	//��Ԃ�����Enumerator(���ɂ�߂�[���[���Ĕ������ɂ�����ˁI)
	enum State{
		NotExist,
		Born,
		Exist,
		Dead
	};

private:
	State _state; //���
	double _x,_y; //���W
	double _vx,_vy; //�x���V�e�B
	int _frame; //�t���[��
	int _image; //�摜
public:
	//�R���X�g���N�^
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

	//�Z�b�^�E�Q�b�^
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
		//�I�[�o�[�t���[�h�~�̂��߁A30���𒴂�����1�ɖ߂�
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

	//����������
	virtual void SetBorn(){
		_frame = 0;
		_state = Born;
	}

	//���񂾏�Ԃɂ���
	virtual void SetDead(){
		_frame = 0;
		_state = Dead;
	}
};
#endif