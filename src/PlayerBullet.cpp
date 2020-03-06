#include "PlayerBullet.h"
#include "Global.h"
void PlayerBullet::Move(){
	Particle::Move();
	if(GetState()==PlayerBullet::Exist && InScreen(GetX(),GetY(),-16,-16) == false){
		PlayerBullet::SetDead();
		return;
	}else{
	//���[�U�[�Ƃ��Čq����悤�ɁA���̕ӂ̈ʒu�����X�V

		Point backCenter;
		backCenter.Set(this->GetX() - MyMath::cos(this->GetAngle()) * (_THICKNESS/2),
			this->GetY() - MyMath::sin(this->GetAngle()) * (_THICKNESS/2));
		_back[0].Set(backCenter.x - MyMath::cos(this->GetAngle() + DX_PI/2) * (_THICKNESS/2),
			backCenter.y - MyMath::sin(this->GetAngle() + DX_PI/2) * (_THICKNESS/2));
		_back[1].Set(backCenter.x + MyMath::cos(this->GetAngle() + DX_PI/2) * (_THICKNESS/2),
			backCenter.y + MyMath::sin(this->GetAngle() + DX_PI/2) * (_THICKNESS/2));
	}
}

void PlayerBullet::Draw(){
	if(GetState()!=PlayerBullet::Exist){
		return;
	}
	Point front[2];
	//������O�̒e�������Ȃ�擪�̈ʒu���v�Z
	if(_B4Ptr == nullptr){
		Point center;
		center.Set(this->GetX() + MyMath::cos(this->GetAngle()) * (_THICKNESS/2),
			this->GetY() + MyMath::sin(this->GetAngle()) * (_THICKNESS/2));
		front[0].Set(center.x - MyMath::cos(this->GetAngle() + DX_PI/2) * (_THICKNESS/2),
			center.y - MyMath::sin(this->GetAngle() + DX_PI/2) * (_THICKNESS/2));
		front[1].Set(center.x + MyMath::cos(this->GetAngle() + DX_PI/2) * (_THICKNESS/2),
			center.y + MyMath::sin(this->GetAngle() + DX_PI/2) * (_THICKNESS/2));
	}else{
		front[0] = _B4Ptr->GetBack(0);
		front[1] = _B4Ptr->GetBack(1);
	}
	SetDrawMode(1);
	SetDrawBlendMode(DX_BLENDMODE_ADD,GetDrawParam());
	DrawModiGraphF(
		static_cast<float>(front[0].x),
		static_cast<float>(front[0].y),
		static_cast<float>(front[1].x),
		static_cast<float>(front[1].y),
		static_cast<float>(_back[1].x),
		static_cast<float>(_back[1].y),
		static_cast<float>(_back[0].x),
		static_cast<float>(_back[0].y),
		GetImage(),TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);

	SetDrawMode(0);
}
void PBulletGroup::SetPowerAll(int pow){
	for(unsigned int i=0; i<_unit.size(); i++){
		_unit[i].SetPower(pow);
	}
}
void PBulletGroup::SetHitXYAll(int r){
	for(unsigned int i=0; i<_unit.size(); i++){
		_unit[i].SetHitXY(r);
	}
}

//�S�Ă̒e�ɑ΂��ē����蔻��
int PBulletGroup::HitCheckAll(double x, double y,int width,int height){
	int hitCount = 0;

	for(unsigned int i=0; i<_unit.size(); i++){
		if(_unit[i].GetState() == PlayerBullet::Exist){
			if(HitCheck(x,y,width,height,
					    _unit[i].GetX(),_unit[i].GetY(),_unit[i].GetHitRect(),_unit[i].GetHitRect()) == true){
				hitCount+=_unit[i].GetPower();
				//�p�[�e�B�N�����΂�
				gParticle.Create(_unit[i].GetX(), _unit[i].GetY(),
						(45 + GetRand(900)*0.1)*RAD, 1+GetRand(50)*0.1, gPlayer.Particle.imgCommon, nullptr, &Particle::Fadeout, nullptr, 0.3, 64);
				SetDead(i);
			}
		}
	}
	return hitCount;
}
PlayerBullet* PBulletGroup::Create(double x, double y, //�a�����̍��W
		    double angle, double speed, //�a�����̊p�x�Ƒ��x
			int image, //�摜
			void (*BornFunc)(Particle& Obj), //�a���G�t�F�N�g
			void (*MoveFunc)(Particle& Obj), //����X�N���v�g
			void (*DeadFunc)(Particle& Obj), //���S�G�t�F�N�g
			double drawExp, int drawParam, bool deletable,
			PlayerBullet* beforePtr){
	//�󂢂Ă��郊�\�[�X������
	for(int i=0; i<(signed)_unit.size(); i++){
		if(_unit[i].GetState() == PlayerBullet::NotExist){
			_unit[i].Create(x, y, angle, speed, image, BornFunc, MoveFunc, DeadFunc, drawExp, drawParam, deletable);
			_unit[i].SetB4Ptr(beforePtr);
			if(beforePtr!=nullptr){beforePtr->SetAfterPtr(&(_unit[i]));}
			return &(_unit[i]);
		}
	}
	return nullptr; //������Ȃ�����
}

int PBulletGroup::Move(){
	unsigned int cnt = 0;
	for(unsigned int i=0;i<_unit.size();i++){
		_unit[i].Move();
		if(_unit[i].GetState() == _unit[i].Exist/* && i>cnt*/){
			//cnt = i;
			cnt++;
		}
	}
	return (signed int)cnt;
}
void PBulletGroup::Draw(){
	for(unsigned int i=0;i<_unit.size();i++){
		_unit[i].Draw();
	}
}

//����
void PBulletGroup::Delete(int Index){
	_unit[Index].SetState(Particle::NotExist);
}

//���ׂď���
void PBulletGroup::DeleteAll(){
	for(unsigned int i=0; i<_unit.size(); i++){
			Delete(i);
	}
}

//�����G�t�F�N�g�ɂ���
void PBulletGroup::SetDead(int Index){
	_unit[Index].SetDead();
}

//�S�ď����G�t�F�N�g�ɂ���
void PBulletGroup::SetDeadAll(){
	for(unsigned int i=0; i<_unit.size(); i++){
			SetDead(i);
	}
}