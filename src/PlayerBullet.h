#ifndef __PLAYERBULLET_H
#define __PLAYERBULLET_H

#include <DxLib.h>
#include "Common.h"
#include "Particle.h"
/*#################################

	���e�֌W

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
	int _hitRect; //�����蔻��̑傫��
	int _power; //�З�
	static const int _NORMAL_POW = 1;
	static const int _NORMAL_RECT = 32;
	static const int _THICKNESS = 32; //�摜�̈�ӂ̒���
	PlayerBullet* _B4Ptr; //���[�U�[�Ƃ��Čq���邽�߂̑O�̒e�ւ̃|�C���^
	PlayerBullet* _afterPtr;//���[�U�[�Ƃ��Čq���邽�߂̌��̒e�ւ̃|�C���^
	Point _back[2]; //�l�p�`��4�ӂ̂����̌��2�_(0: �� 1: �E)
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
	//�R���X�g���N�^
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

	PlayerBullet* Create(double x, double y, //�a�����̍��W
		double angle, double speed, //�a�����̊p�x�Ƒ��x
		int image, //�摜
		void(*BornFunc)(Particle& Obj) = nullptr, //�a���G�t�F�N�g
		void(*MoveFunc)(Particle& Obj) = nullptr, //����X�N���v�g
		void(*DeadFunc)(Particle& Obj) = nullptr, //���S�G�t�F�N�g
		double drawExp = 1.0, //�g�嗦
		int drawParam = 255, //�`��p�����[�^
		bool deletable = true, //��ʊO�ɔ�яo�������ɏ������邩�H
		PlayerBullet* beforePtr = nullptr //�O�̒e�ւ̃|�C���^(���e�Ȃ�nullptr)
		);

	//����
	void Delete(int Index);
	//���ׂď���
	void DeleteAll();

	void SetDead(int index);
	void SetDeadAll();

	//�����������B���ݑ��݂���p�[�e�B�N���̐���Ԃ��B
	int Move();
	void Draw();

	void SetPowerAll(int pow = 1);
	void SetHitXYAll(int r = 16);
	//�S�Ă̒e�ɑ΂��ē����蔻��B�߂�l�͓����������ɂ���Ĕ��������_���[�W�̑��v
	int HitCheckAll(double x, double y, int width, int height);

};

#endif