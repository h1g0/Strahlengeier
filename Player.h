#ifndef __PLAYER_H
#define __PLAYER_H

#include <DxLib.h>
#include<string>
#include "Common.h"
#include "Particle.h"
#include "PlayerBullet.h"

static const long int MaxScore=999999999;

static const int rankUpConst = 2000; //2k pts.
static const int everyExtendConst = 20000; //20k pts.

class PlayerShip: public Object{
private:
	bool _move;
	int _speed;
	int _stock;
	long _score;
	int _invFrm; //���G�t���[��(0���傫����Ζ��G)
	int _invImg; //���G���摜
	int _sndBorn; //��������SE
	int _sndShot; //�V���b�g����SE
	int _sndDead; //���S����SE
	int _rankUpNext;
	int _extendNext;
	std::vector<PlayerBullet*> _recentPtr; //�O�Ɍ������e�̃|�C���^
	double _angle;
	double _vx[8]; //45�x���̈ړ���
	double _vy[8];//45�x���̈ړ���

	bool _isShooting[2]; //�����Ă邩�H(�ߋ�1�t���[�������ۑ�)

	void (*_ShotFunc)(PlayerShip& Obj); //�ʏ�V���b�g
	void (*_NarrowShotFunc)(PlayerShip& Obj); //�ᑬ���V���b�g

	void (*_BornDrawFunc)(PlayerShip& Obj);
	void (*_ExistDrawFunc)(PlayerShip& Obj);
	void (*_DeadDrawFunc)(PlayerShip& Obj);

	void _SetSound(int& dist, const std::string& filepath);
	void _PlaySound(int dist);
	void _UnloadSound(int& dist);
public:
	static const int HitRect = 2; //�����蔻��̈�ӂ̑傫��

	PBulletGroup BltGrp; //�e
	ParticleGroup Particle;//�p�[�e�B�N��(������)

	bool gameOver;

	PlayerShip(){
		gameOver=false;
		SetMove(true);
		SetSpeed(3);
		SetAngle(270*RAD);
		SetStock(3);
		_ShotFunc = &ShotNormal;
		_BornDrawFunc = &BornNormal;
		_ExistDrawFunc = &ExistNormal;
		_DeadDrawFunc = &DeadNormal;
		_NarrowShotFunc = &ShotNarrow;
	}
	inline long GetScore(){return _score;}
	inline long SetScore(long score){
		if(score<0 || score > MaxScore){return GetScore();}
		else{
			_score = score;
		}
		return GetScore();
	}
	inline void InitScore(){
		SetScore(0);
		_rankUpNext=rankUpConst;
		_extendNext = everyExtendConst;
	}

	void AddScore(long score);
	void SetAngle(double angle){_angle=angle;}
	double GetAngle() const{return _angle;}
	void SetInvinvincibleImage(int img){_invImg = img;} //���G���̉摜���Z�b�g
	int GetInvincibleImage() const{return _invImg;} //���G���̉摜��Ԃ�
	void SetInvincibleFrame(int frm){
		if(frm>0){
			_invFrm = frm;
		}else{
			_invFrm = 0;
		}
	}
	int GetInvincibleFrame() const{return _invFrm;}
	void DecreaseInvincibleFrame(){
		if(_invFrm>0){_invFrm--;}
	}

	//���G�摜��`�悷��
	void DrawInvincibleImage(){
		if(GetInvincibleFrame()>0){
			int param = 255;
			if(GetInvincibleFrame()<16){
				param = 16 * GetInvincibleFrame();
			}
			SetDrawBlendMode(DX_BLENDMODE_ADD,param);
			DrawRotaGraph((int)GetX(),(int)GetY(),1.0,0,_invImg,TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		}
	}
	void SetStock(int stock){
		_stock=stock;
	}
	int GetStock(){
		return _stock;
	}
	void AddStock(int stock){
		_stock+=stock;
	}
	void SetSpeed(int speed);
	bool GetIsShooting(int idx = 0) const{return _isShooting[idx];}
	void SetMove(bool move){_move = move;}
	void Draw();
	void Move();//����
	void MoveByHand(); //�L�[�{�[�h����

	//���܂ꂽ��(Object::SetBorn()���I�[�o�[���C�h)
	void SetBorn(){
		if(GetStock()<=0){
			gameOver=true;
			return;
		}else{
			AddStock(-1);
		}
		SetInvincibleFrame(60);
		_recentPtr.resize(3,nullptr);
		Object::SetBorn();
		_PlaySound(_sndBorn);
	}
	//���񂾎�(Object::SetDead()���I�[�o�[���C�h)
	void SetDead(){
		if(GetInvincibleFrame()>0){return;} //���G�Ȃ玀�ȂȂ�
		Object::SetDead();
		_PlaySound(_sndDead);
	}

	void SetSE(std::string bornFile, std::string shotFile, std::string deadFile){
		_SetSound(_sndBorn,bornFile);
		_SetSound(_sndShot,shotFile);
		_SetSound(_sndDead,deadFile);
	}
	void UnloadSE(){
		_UnloadSound(_sndBorn);
		_UnloadSound(_sndShot);
		_UnloadSound(_sndDead);
	}
	//�ʏ�V���b�g
	static void ShotNormal(PlayerShip& Obj);
	static void ShotNarrow(PlayerShip& Obj);

	//�ʏ펞�`��
	static void ExistNormal(PlayerShip& Obj);
	//�a�����`��
	static void BornNormal(PlayerShip& Obj);
	//���S���`��
	static void DeadNormal(PlayerShip& Obj);
};
#endif