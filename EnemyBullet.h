#ifndef __ENEMYBULLET_H
#define __ENEMYBULLET_H
#include"Particle.h"
#include "Player.h"
#include "Rank.h"
//#include "Global.h"
//#include "Enemy.h"
#include <vector>

class EnemyBullet: public Particle{
public:

	//�������ɋA���Ă�����Q
	struct ReturnInfo{
		int shotCount;
		double angleShot; //�Ō�Ɍ������p�x
		int waitFrame; //���ꂩ��҂t���[����
	};

	//�������ɓn�����Q
	struct CreateInfo{
		double x; double y;//�a�����̍��W
		double angleB4; //�O�񌂂����p�x
		int shotCount; //�������������H
		int image; //�摜
		void (*MoveFunc)(EnemyBullet& obj, ReturnInfo *resultPtr); //����X�N���v�g�Bnullptr�Ő���������
	};

private:
	int _hitRect;
	bool _isCreating; //���������ۂ��̃t���O
	int _shotCnt; //�e�ł���G�ɂƂ��ĉ����߂��H
	double _angleShotB4;
	void (*_MoveFunc)(EnemyBullet& obj, ReturnInfo *resultPtr); //�������w�肷��|�C���^
	void (*_BornFunc)(EnemyBullet& obj); //�a�����G�t�F�N�g
	void (*_DeadFunc)(EnemyBullet& obj); //���񂾎��̃G�t�F�N�g

	PlayerShip *_playerPtr; //�_���ׂ����@
	InnerRank *_rank; //���݂̃����N
public:
	EnemyBullet(){
		_MoveFunc = nullptr;
		_BornFunc = nullptr;
		_DeadFunc = nullptr;
		_hitRect = 2;
		_shotCnt = 0;
	}
	void SetHitRect(int rect){_hitRect = rect;}
	int GetHitRect() const{return _hitRect;}
	void SetPlayer(PlayerShip *ptr){_playerPtr = ptr;}
	PlayerShip& GetPlayer() const{return *_playerPtr;}
	void SetRankCls(InnerRank *ptr){_rank = ptr;}
	InnerRank& GetRankCls(){return *_rank;}
	bool GetIsCreating() const{return _isCreating;}
	int GetShotCount() const{return _shotCnt;}
	double GetAngleB4() const{return _angleShotB4;}
	ReturnInfo Create(CreateInfo obj);
	void Move();
	void Draw();
	void HitCheck2Player();

	static void PlayerOriented(EnemyBullet& obj, ReturnInfo *resultPtr){ //���@�_��
		if(obj.GetIsCreating() == true){
			double rad = MyMath::atan2(obj.GetPlayer().GetY() - obj.GetY(),
				                       obj.GetPlayer().GetX() - obj.GetX());
			obj.SetAngle(rad);
			obj.SetSpeed(4);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = GetRand(30) + obj.GetRankCls().GetInvLiner(50);
		}
	}
	static void PlayerOrientedRandom(EnemyBullet& obj, ReturnInfo *resultPtr){ //���@�_���΂�T��
		if(obj.GetIsCreating() == true){
			double rad = MyMath::atan2(obj.GetPlayer().GetY() - obj.GetY(),
				                       obj.GetPlayer().GetX() - obj.GetX());
			double randRad=(GetRand(400)*0.1 - 20)*RAD;
			rad+=randRad;
			obj.SetAngle(rad);
			obj.SetSpeed(2+GetRand(200)*0.01);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = GetRand(30) + obj.GetRankCls().GetInvLiner(50);
		}
	}

	static void Spiral10way(EnemyBullet& obj, ReturnInfo *resultPtr){ //20way����C��(�჉���N����5way)
		if(obj.GetIsCreating() == true){
			double rad = (obj.GetRankCls().GetLiner()>0.5)?obj.GetAngleB4() + 18 * RAD:obj.GetAngleB4() + 36 * RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(2);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = (obj.GetShotCount()%20==19)?obj.GetRankCls().GetInvLiner(90)+30:obj.GetRankCls().GetInvLiner(20)+10;
		}
	}
	static void Fall(EnemyBullet& obj, ReturnInfo *resultPtr){ //��������
		if(obj.GetIsCreating() == true){
			obj.SetAngle(270*RAD);
			obj.SetSpeed(GetRand(100)*0.01);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = 270*RAD;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = GetRand(30) + obj.GetRankCls().GetInvLiner(50);
		}else{
			if(obj.GetVy()<4){
				obj.SetVy(obj.GetVy() + 0.1);
				obj.SetAngle(MyMath::atan2(obj.GetVy(),obj.GetVx()));
			}
		}
	}

	static void Fountain(EnemyBullet& obj, ReturnInfo *resultPtr){ //����
		if(obj.GetIsCreating() == true){
			double rad=(GetRand(90)+270-45)*RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(3+GetRand(100)*0.03);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = GetRand(40) + obj.GetRankCls().GetInvLiner(30);
		}else{
			if(obj.GetVy()<4){
				obj.SetVx(obj.GetVx()*0.9999);
				obj.SetVy(obj.GetVy() + 0.2);
				obj.SetAngle(MyMath::atan2(obj.GetVy(),obj.GetVx()));
			}
		}
	}
	static void Random(EnemyBullet& obj, ReturnInfo *resultPtr){ //�����_��
		if(obj.GetIsCreating() == true){
			double rad=(GetRand(3600)*0.1)*RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(1+GetRand(100)*0.05);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = GetRand(20) + obj.GetRankCls().GetInvLiner(50);
		}
	}
	static void RestrictedRandom(EnemyBullet& obj, ReturnInfo *resultPtr){ //�����݂̂̃����_��
		if(obj.GetIsCreating() == true){
			double rad=(45+GetRand(900)*0.1)*RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(1+GetRand(100)*0.05);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = GetRand(60) + obj.GetRankCls().GetInvLiner(50);
		}
	}

	static void Circle20way(EnemyBullet& obj, ReturnInfo *resultPtr){ //20way���S�~�e
		if (obj.GetIsCreating() == true){
			double rad = obj.GetAngleB4()+18*RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(2);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = (obj.GetShotCount() % 20 == 19) ? obj.GetRankCls().GetInvLiner(50) + 10 : 0;
		}
	}
	static void Rotate20way(EnemyBullet& obj, ReturnInfo *resultPtr){ //����C��*4
		if (obj.GetIsCreating() == true){
			double rad = obj.GetAngleB4() + 92 * RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(2);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = (obj.GetShotCount() % 4 == 3) ? obj.GetRankCls().GetInvLiner(12) + 2:0;
		}
	}
	static void Circle72way(EnemyBullet& obj, ReturnInfo *resultPtr){ //72way
		if (obj.GetIsCreating() == true){
			double rad = obj.GetAngleB4() + 5 * RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(3+MyMath::sin((obj.GetShotCount()%72)*80*RAD)*1);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = (obj.GetShotCount() % 72 == 71) ? obj.GetRankCls().GetInvLiner(80) + 10 : 0;
		}
	}
	static void Circle20way2Plyr(EnemyBullet& obj, ReturnInfo *resultPtr){ //20way���S�~�e���玩�@�_����
		if (obj.GetIsCreating() == true){
			double rad = obj.GetAngleB4() + 18 * RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(2 + obj.GetRankCls().GetInvLiner(3));
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = (obj.GetShotCount() % 20 == 19) ? obj.GetRankCls().GetInvLiner(90) + 10 : 0;
		}
		else if (obj.GetFrame()==20){
			double rad = MyMath::atan2(obj.GetPlayer().GetY() - obj.GetY(),
				obj.GetPlayer().GetX() - obj.GetX());
			obj.SetAngle(rad);
			obj.SetSpeed(5);
			obj.SetVxVyFromSpeedAngle();
		}
	}

	static void DownBroom(EnemyBullet& obj, ReturnInfo *resultPtr){ //���ւ�ⴑ|��
		if (obj.GetIsCreating() == true){
			double rad = (90 + MyMath::sin((obj.GetShotCount() % 45) * 16 * RAD)*45) * RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(2);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = (obj.GetShotCount() % 45 == 44) ? obj.GetRankCls().GetInvLiner(90) + 30 : obj.GetRankCls().GetInvLiner(3) + 1;
		}
	}

	static void BigCircle(EnemyBullet& obj, ReturnInfo *resultPtr){ //�傫���~�e��������C��
		if (obj.GetIsCreating() == true){
			double rad = (obj.GetShotCount() % 10 == 0) ? obj.GetAngleB4() + 80 * RAD : obj.GetAngleB4()+2 * RAD;
			obj.SetAngle(rad);
			obj.SetSpeed(2 + MyMath::sin((obj.GetShotCount() % 10)*18*RAD)*0.5);
			obj.SetVxVyFromSpeedAngle();
			resultPtr->angleShot = rad;
			resultPtr->shotCount = 1;
			resultPtr->waitFrame = (obj.GetShotCount() % 40 == 39) ? obj.GetRankCls().GetInvLiner(50) + 10 : 0;
		}
	}

};

class EBGroup{
private :
	std::vector<EnemyBullet> _unit;
public:
	int imgCommon;
	EBGroup(){
		_unit.resize(1000);
	}
	void SetPlayerPtr(PlayerShip *ptr);
	void SetRankPtr(InnerRank *ptr);
	void SetLimit(int size){_unit.resize(size);}
	int GetLimit() const{_unit.size();}

	/*-----------------
	 * �G�e�𐶐�����B
	 ����: obj: ��������n���\����
	       result: ���ʋA���Ă�����񂪑�������\���̂ւ̎Q��
	�߂�l: �������ꂽ�C���f�b�N�X�B-1�ŃG���[
	 *----------------*/
	int Create(EnemyBullet::CreateInfo obj, EnemyBullet::ReturnInfo& result);
	int Move();
	void Draw();
	void HitCheckAll2Player();
};

#endif