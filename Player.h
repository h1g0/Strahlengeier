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
	int _invFrm; //無敵フレーム(0より大きければ無敵)
	int _invImg; //無敵時画像
	int _sndBorn; //生成時のSE
	int _sndShot; //ショット時のSE
	int _sndDead; //死亡時のSE
	int _rankUpNext;
	int _extendNext;
	std::vector<PlayerBullet*> _recentPtr; //前に撃った弾のポインタ
	double _angle;
	double _vx[8]; //45度毎の移動量
	double _vy[8];//45度毎の移動量

	bool _isShooting[2]; //撃ってるか？(過去1フレーム分も保存)

	void (*_ShotFunc)(PlayerShip& Obj); //通常ショット
	void (*_NarrowShotFunc)(PlayerShip& Obj); //低速時ショット

	void (*_BornDrawFunc)(PlayerShip& Obj);
	void (*_ExistDrawFunc)(PlayerShip& Obj);
	void (*_DeadDrawFunc)(PlayerShip& Obj);

	void _SetSound(int& dist, const std::string& filepath);
	void _PlaySound(int dist);
	void _UnloadSound(int& dist);
public:
	static const int HitRect = 2; //当たり判定の一辺の大きさ

	PBulletGroup BltGrp; //弾
	ParticleGroup Particle;//パーティクル(かざり)

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
	void SetInvinvincibleImage(int img){_invImg = img;} //無敵時の画像をセット
	int GetInvincibleImage() const{return _invImg;} //無敵時の画像を返す
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

	//無敵画像を描画する
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
	void Move();//動作
	void MoveByHand(); //キーボード操作

	//生まれた時(Object::SetBorn()をオーバーライド)
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
	//死んだ時(Object::SetDead()をオーバーライド)
	void SetDead(){
		if(GetInvincibleFrame()>0){return;} //無敵なら死なない
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
	//通常ショット
	static void ShotNormal(PlayerShip& Obj);
	static void ShotNarrow(PlayerShip& Obj);

	//通常時描画
	static void ExistNormal(PlayerShip& Obj);
	//誕生時描画
	static void BornNormal(PlayerShip& Obj);
	//死亡時描画
	static void DeadNormal(PlayerShip& Obj);
};
#endif