#include "PlayerBullet.h"
#include "Global.h"
void PlayerBullet::Move(){
	Particle::Move();
	if(GetState()==PlayerBullet::Exist && InScreen(GetX(),GetY(),-16,-16) == false){
		PlayerBullet::SetDead();
		return;
	}else{
	//レーザーとして繋げるように、後ろの辺の位置情報を更新

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
	//これより前の弾が無いなら先頭の位置を計算
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

//全ての弾に対して当たり判定
int PBulletGroup::HitCheckAll(double x, double y,int width,int height){
	int hitCount = 0;

	for(unsigned int i=0; i<_unit.size(); i++){
		if(_unit[i].GetState() == PlayerBullet::Exist){
			if(HitCheck(x,y,width,height,
					    _unit[i].GetX(),_unit[i].GetY(),_unit[i].GetHitRect(),_unit[i].GetHitRect()) == true){
				hitCount+=_unit[i].GetPower();
				//パーティクルを飛ばす
				gParticle.Create(_unit[i].GetX(), _unit[i].GetY(),
						(45 + GetRand(900)*0.1)*RAD, 1+GetRand(50)*0.1, gPlayer.Particle.imgCommon, nullptr, &Particle::Fadeout, nullptr, 0.3, 64);
				SetDead(i);
			}
		}
	}
	return hitCount;
}
PlayerBullet* PBulletGroup::Create(double x, double y, //誕生時の座標
		    double angle, double speed, //誕生時の角度と速度
			int image, //画像
			void (*BornFunc)(Particle& Obj), //誕生エフェクト
			void (*MoveFunc)(Particle& Obj), //動作スクリプト
			void (*DeadFunc)(Particle& Obj), //死亡エフェクト
			double drawExp, int drawParam, bool deletable,
			PlayerBullet* beforePtr){
	//空いているリソースを検索
	for(int i=0; i<(signed)_unit.size(); i++){
		if(_unit[i].GetState() == PlayerBullet::NotExist){
			_unit[i].Create(x, y, angle, speed, image, BornFunc, MoveFunc, DeadFunc, drawExp, drawParam, deletable);
			_unit[i].SetB4Ptr(beforePtr);
			if(beforePtr!=nullptr){beforePtr->SetAfterPtr(&(_unit[i]));}
			return &(_unit[i]);
		}
	}
	return nullptr; //見つからなかった
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

//消す
void PBulletGroup::Delete(int Index){
	_unit[Index].SetState(Particle::NotExist);
}

//すべて消す
void PBulletGroup::DeleteAll(){
	for(unsigned int i=0; i<_unit.size(); i++){
			Delete(i);
	}
}

//消去エフェクトにする
void PBulletGroup::SetDead(int Index){
	_unit[Index].SetDead();
}

//全て消去エフェクトにする
void PBulletGroup::SetDeadAll(){
	for(unsigned int i=0; i<_unit.size(); i++){
			SetDead(i);
	}
}