#include<DxLib.h>

#include "GameManager.h"
#include "Global.h"

void GameManager::SetBGM(std::string filepath, bool playNow){
	if(_nowBGM!=0){
		DeleteSoundMem(_nowBGM);
	}
	_nowBGM=LoadSoundMem(filepath.c_str());
	if(playNow){PlayBGM();}
}
void GameManager::PlayBGM(){
	PlaySoundMem(_nowBGM,DX_PLAYTYPE_LOOP);
}
void GameManager::StopBGM(){
	StopSoundMem(_nowBGM);
}
void GameManager::Init(GameManager& parent, int frame){
	InitGraph();
	InitSoundMem();
	parent.Set(&LoadMainMenu);
}
void GameManager::LoadMainMenu(GameManager& parent, int frame){
	gBGround.Set(10,MV1LoadModel("img\\background.mv1"),true);
	gEnemy.imgCommon = LoadGraph("img\\title.png");
	gDrawScr = MakeScreen(SCR_WIDTH,SCR_HEIGHT);
	parent.Set(&FrontMenu);
}
void GameManager::UnloadMainMenu(GameManager& parent, int frame){
	parent.Set(&LoadGameMain);
}

void GameManager::FrontMenu(GameManager& parent, int frame){
	gBGround.Move();
	gBGround.Draw();
	SetDrawBlendMode(DX_BLENDMODE_ADD,255);
	DrawRotaGraph(SCR_WIDTH/2,100,1.0,0,gEnemy.imgCommon,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,static_cast<int>(128+127*MyMath::sin(frame*3*RAD)));
	DrawString(SCR_WIDTH/2-120,SCR_HEIGHT-40,"Press shot button to start.",GetColor(255,255,255));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & shotButton) != 0){
		parent.Set(&UnloadMainMenu);
	}/*else if(CheckHitKey(KEY_INPUT_K)==1){
		parent.Set(&KeyConfig1);
	}*/
}

void GameManager::KeyConfig1(GameManager& parent, int frame){
	gBGround.Move();
	gBGround.Draw();
	DrawString(10,SCR_HEIGHT/2,"キー設定を開始します。キーボードのショットキーを押して下さい。右矢印キーでスキップします。",
		GetColor(255,255,255));
	if((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0){
		parent.Set(&KeyConfig2);
		return;
	}

	char Buf[ 256 ] ;
	GetHitKeyStateAll( Buf ) ;
	for(int i=0;i<256;i++){
		if(Buf[i]==1){
			gConfig.put("Key.Shot",i);
			SetJoypadInputToKeyInput(DX_INPUT_PAD1, shotButton,i, -1, -1, -1 ) ;
			parent.Set(&KeyConfig2);
			return;
		}
	}
}
void GameManager::KeyConfig2(GameManager& parent, int frame){
}
void GameManager::KeyConfig3(GameManager& parent, int frame){
}
void GameManager::KeyConfig4(GameManager& parent, int frame){
}

void GameManager::LoadGameMain(GameManager& parent, int frame){
	//初期化
	//SRand(42);
	gRank.Init();
	parent.SetBGM("snd\\bgm1.mp3");
	gPlayer.SetStock(3);
	gPlayer.InitScore();
	gPlayer.SetSE("snd\\player_born.wav","snd\\player_shot.wav","snd\\player_dead.wav");
	gPlayer.SetXY(320,400);
	gPlayer.SetSpeed(6);
	gPlayer.SetBorn();
	gPlayer.SetImage(LoadGraph("img\\player.bmp"));
	gPlayer.SetInvinvincibleImage(LoadGraph("img\\player_inv.bmp"));
	LoadImg(gPlayer.BltGrp.imgCommon, "img\\playerblt.bmp");
	gPlayer.BltGrp.SetHitXYAll();
	gPlayer.BltGrp.SetPowerAll(1);
	LoadImg(gPlayer.Particle.imgCommon, "img\\player_particle.bmp");

	gEnemy.SetPlayerPtr(&gPlayer);
	gEnemy.SetParticlePtr(&gParticle);
	gEnemy.SetBulletPtr(&gEnemyBullet);
	gEnemy.SetSE("snd\\enemy_dead_small.wav", "snd\\enemy_dead_middle.wav");
	LoadImg(gImg["Enemy1"], "img\\enemy1.bmp");
	LoadImg(gImg["BigEnemy1"], "img\\bigenemy1.bmp");

	gEnemyBullet.SetPlayerPtr(&gPlayer);
	gEnemyBullet.SetRankPtr(&gRank);
	LoadImg(gEnemyBullet.imgCommon,"img\\enemyblt.bmp");

	LoadImg(gParticle.imgCommon, "img\\enemy_particle.bmp");

	gBGround.Set(10,MV1LoadModel("img\\background.mv1"),true);
	LoadImg(parent._imgGameOver, "img\\gameover.png");
	//gDrawScr = MakeScreen(SCR_WIDTH,SCR_HEIGHT);
	//終了
	parent.Set(&LoadGameSt1);
}

void GameManager::LoadGameSt1(GameManager& parent, int frame){
	parent.Set(&GameSt1);
}
void GameManager::UnloadGameMain(GameManager& parent, int frame){
	parent.Set(&LoadMainMenu);
}

void GameManager::GameSt1(GameManager& parent, int frame){
	static const int gEnmPtnCap = 9; //パターンの数
	static const int gEnmBltPtnCap=9;

	static int gEnmPtn = 0;
	static int gEnmBltPtn = 0;
	static int gEnmX=0;
	static int gEnmY=0;
	static double gEnmRad=0;
	static int gIdx = 0;
	static Enemy::CreateInfo enm;
	static const int formation = 12;
	static int waitFrm =0;
	//雑魚敵生成
	if(waitFrm==0){
		if(gIdx == 0){
			waitFrm=5;
			gEnmPtn = GetRand(gEnmPtnCap - 1);
			gEnmBltPtn = GetRand(gEnmBltPtnCap - 1);
		}else if(gIdx == formation-1){
			waitFrm=gRank.GetInvLiner(60);
		}else{
			waitFrm=5;
		}
		switch(gEnmPtn){
			//右から一直線で回転
		case 0:
			if(gIdx ==0){
				gEnmX = SCR_WIDTH+GetRand(64);
				gEnmY = GetRand(SCR_HEIGHT/4)+64;
				gEnmRad = (170+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX;
			enm.y =gEnmY;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::CircleLikeMinus;

			break;
		//左から一直線で回転
		case 1:
			if(gIdx ==0){
				gEnmX = -GetRand(64);
				gEnmY = GetRand(SCR_HEIGHT/4)+64;
				gEnmRad = (-10+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX;
			enm.y =gEnmY;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::CircleLike;

			break;
			//上から一直線で止まる
		case 2:
			if(gIdx ==0){
				gEnmX = 128+GetRand(SCR_WIDTH-256);
				gEnmY = -GetRand(64);
				gEnmRad = (80+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX;
			enm.y =gEnmY;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::BecomeSlow;

			break;
		//右から止まる
		case 3:
			if(gIdx ==0){
				gEnmX = SCR_WIDTH+GetRand(64);
				gEnmY = GetRand(SCR_HEIGHT/4)+64;
				gEnmRad = (170+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX;
			enm.y =gEnmY+gIdx*16;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::BecomeSlow;

			break;
		//左から止まる
		case 4:
			if(gIdx ==0){
				gEnmX = -GetRand(64);
				gEnmY = GetRand(SCR_HEIGHT/4)+64;
				gEnmRad = (-10+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX;
			enm.y =gEnmY+gIdx*16;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::BecomeSlow;

			break;
		//上から止まる
		case 5:
			if(gIdx ==0){
				gEnmX = GetRand(SCR_WIDTH-380);
				gEnmY = -GetRand(64);
				gEnmRad = (80+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX+gIdx*32;
			enm.y =gEnmY;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::BecomeSlow;

			break;
		//上から反転して帰ってく
		case 6:
			if(gIdx ==0){
				gEnmX = SCR_WIDTH-GetRand(SCR_WIDTH-380);
				gEnmY = -GetRand(64);
				gEnmRad = (80+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX-gIdx*32;
			enm.y =gEnmY;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::Retreat;

			break;
			//上から反転して横へ
		case 7:
			if(gIdx ==0){
				gEnmX = GetRand(SCR_WIDTH-380);
				gEnmY = -GetRand(64);
				gEnmRad = (80+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX+gIdx*32;
			enm.y =gEnmY;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::Retreat2;

			break;

			//上から反転して横へ2
		case 8:
			if(gIdx ==0){
				gEnmX = SCR_WIDTH-GetRand(SCR_WIDTH-380);
				gEnmY = -GetRand(64);
				gEnmRad = (80+GetRand(200)*0.1)*RAD ;
			}
			enm.speed=10;
			enm.x=gEnmX-gIdx*32;
			enm.y =gEnmY;
			enm.angle = gEnmRad;
			enm.MoveFunc=&Enemy::Retreat3;

			break;
		}
		switch (gEnmBltPtn){
		case 0:
			enm.ShotFunc=&EnemyBullet::PlayerOriented;
			break;
		case 1:
			enm.ShotFunc=&EnemyBullet::Fall;
			break;
		case 2:
			enm.ShotFunc = &EnemyBullet::Fountain;
			break;
		case 3:
			enm.ShotFunc = &EnemyBullet::Random;
			break;
		case 4:
			enm.ShotFunc = &EnemyBullet::Spiral10way;
			break;
		case 5:
			enm.ShotFunc = &EnemyBullet::RestrictedRandom;
			break;
		case 6:
			enm.ShotFunc = &EnemyBullet::PlayerOrientedRandom;
			break;

		default:
			enm.ShotFunc=&EnemyBullet::PlayerOriented;
			break;
		}
			enm.BornFunc=nullptr;
			enm.DeadFunc=(GetRand(42)%2==0)?&Enemy::DeadParticle:&Enemy::DeadParticle2;
			enm.hitH=64;
			enm.hitW=64;
			enm.hp=5;
			enm.image=gImg["Enemy1"];
			enm.bulletImage=gEnemyBullet.imgCommon;
			enm.rotateWhenDraw = true;
			++gIdx%=formation;
			if(gPlayer.GetState() == PlayerShip::Exist){gEnemy.Create(enm);}
		}else{
			waitFrm--;
		}

		//レベルが上昇していたら大型敵登場
		if (gRank.GetIsIncreased()){
			gRank.ResetIsIncreased();
			Enemy::CreateInfo bigEnm;
			bigEnm.hitH = 96;
			bigEnm.hitW = 96;
			bigEnm.hp = 50;
			bigEnm.image = gImg["BigEnemy1"];
			bigEnm.BornFunc = nullptr;
			bigEnm.DeadFunc = &Enemy::DeadParticle3 ;
			bigEnm.bulletImage = gEnemyBullet.imgCommon;
			bigEnm.rotateWhenDraw = false;

			static const int bigEnmPtnCap = 1;
			int bigEnmPtn = GetRand(bigEnmPtnCap - 1);
			switch (bigEnmPtn){
			case 0:
				bigEnm.x = 64 + GetRand(SCR_WIDTH - 128);
				bigEnm.y = -64;
				bigEnm.angle= 90*RAD;
				bigEnm.speed = 10;
				bigEnm.MoveFunc = &Enemy::BecomeSlow4BigEnm;
				break;
			default:
				bigEnm.x = 64 + GetRand(SCR_WIDTH - 128);
				bigEnm.y = -64;
				bigEnm.angle = 90 * RAD;
				bigEnm.speed = 10;
				bigEnm.MoveFunc = &Enemy::BecomeSlow4BigEnm;
				break;
			}

			static const int bigEnmBltPtnCap = 4;
			int bigEnmBltPtn = GetRand(bigEnmBltPtnCap - 1);
			switch (bigEnmBltPtn){
			case 0:
				bigEnm.ShotFunc = &EnemyBullet::Circle20way;
				break;
			case 1:
				bigEnm.ShotFunc = &EnemyBullet::Rotate20way;
				break;
			case 2:
				bigEnm.ShotFunc = &EnemyBullet::Circle72way;
				break;
			case 3:
				bigEnm.ShotFunc = &EnemyBullet::Circle20way2Plyr;
				break;

			default:
				bigEnm.ShotFunc = &EnemyBullet::Circle20way;
				break;
			}

			if (gPlayer.GetState() == PlayerShip::Exist){ gEnemy.Create(bigEnm); }
		}

		GameMain(parent,frame);
}

void GameManager::GameMain(GameManager& parent, int frame){
	gBGround.Move();
	gParticle.Move();

	gPlayer.Particle.Move();
	gPlayer.Move();
	gPlayer.BltGrp.Move();
	if(gPlayer.GetState()==gPlayer.Exist){
		gRank.Exec();
	}
	gEnemy.Move();
	gEnemy.HitCheckAll2Player();
	gEnemyBullet.Move();
	gEnemyBullet.HitCheckAll2Player();

	gBGround.Draw();
	gPlayer.Particle.Draw();
	gParticle.Draw();
	gPlayer.Draw();
	gEnemy.Draw();

	gPlayer.BltGrp.Draw();

	gEnemyBullet.Draw();
	GameMainStatus(parent,frame);

	if(gPlayer.gameOver==true){
		if(gPlayer.GetScore()>gConfig.get("HighScore.1",10000)){
			gConfig.put("HighScore.1",gPlayer.GetScore());
		}

		parent.Set(&GameManager::GameOver);
		gPlayer.gameOver=false;
	}
}
void GameManager::GameMainStatus(GameManager& parent, int frame){
	int hscr=gConfig.get("HighScore.1",10000);
	if(gPlayer.GetScore()>hscr){hscr=gPlayer.GetScore();}
	DrawFormatString(0,0,GetColor(255,255,255),"Score: %09ld",gPlayer.GetScore());
	DrawFormatString(SCR_WIDTH/2,0,GetColor(255,255,255),"High Score:");
	DrawFormatString(SCR_WIDTH / 2+192, 12, GetColor(255, 255, 255), "%09ld",hscr);
	DrawFormatString(0,12,GetColor(255,255,255),"Rest: %02d",gPlayer.GetStock());
	DrawFormatString(0,24,GetColor(255,255,255),"Depth: %03d",gRank.Get());
}
void GameManager::GameOver(GameManager& parent, int frame){
	gBGround.Move();
	gParticle.Move();

	gPlayer.Particle.Move();
	gPlayer.BltGrp.Move();

	gEnemy.Move();
	gEnemyBullet.Move();

	gBGround.Draw();
	gPlayer.Particle.Draw();
	gParticle.Draw();
	gEnemy.Draw();

	gPlayer.BltGrp.Draw();

	gEnemyBullet.Draw();
	GameMainStatus(parent,frame);
	//ゲームオーバー画像のサイズ
	static const int imgW=256;
	static const int imgH=64;

	static const int allFrm=60*5;
	static const int fadeFrm=30; //フェードのフレーム数

	static const int xPerFrm=static_cast<int>((SCR_WIDTH-imgW)/2 / fadeFrm);
	static const int yPerFrm=static_cast<int>((SCR_HEIGHT-imgH)/2 / fadeFrm);
	SetDrawMode(1);
	if(frame>=allFrm){
		parent.Set(&GameManager::Init);
	}else if(frame<fadeFrm){ //フェードイン
		int lfrm=frame;
		SetDrawBlendMode(DX_BLENDMODE_ADD,static_cast<int>(255/fadeFrm*lfrm));
		DrawModiGraph(xPerFrm*lfrm,SCR_HEIGHT/2-yPerFrm*lfrm,
			SCR_WIDTH - xPerFrm * lfrm, SCR_HEIGHT / 2 - yPerFrm * lfrm,
			SCR_WIDTH - xPerFrm * lfrm, SCR_HEIGHT / 2 + yPerFrm * lfrm,
			xPerFrm*lfrm,SCR_HEIGHT/2+yPerFrm*lfrm,parent._imgGameOver,TRUE);
	}else if(frame>=allFrm-fadeFrm){ //フェードアウト
		int lfrm=allFrm-frame;
		SetDrawBlendMode(DX_BLENDMODE_ADD,static_cast<int>(255/fadeFrm*lfrm));
		DrawModiGraph(xPerFrm*lfrm,SCR_HEIGHT/2-yPerFrm*lfrm,
			SCR_WIDTH - xPerFrm * lfrm, SCR_HEIGHT / 2 - yPerFrm * lfrm,
			SCR_WIDTH - xPerFrm * lfrm, SCR_HEIGHT / 2 + yPerFrm * lfrm,
			xPerFrm*lfrm,SCR_HEIGHT/2+yPerFrm*lfrm,parent._imgGameOver,TRUE);
	}else{ //通常描画
		SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		DrawRotaGraph(SCR_WIDTH/2,SCR_HEIGHT/2,1.0,0,parent._imgGameOver,TRUE);
		if(gPlayer.GetScore()>=gConfig.get("HighScore.1",10000)){
			std::string c = "You've got the highest score!";
			int x = static_cast<int>((SCR_WIDTH-GetDrawStringWidth(c.c_str(),c.size()))/2);
			int y = (SCR_HEIGHT+imgH)/2+10;
			DrawString(x,y,c.c_str(),GetColor(255,255,255));
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawMode(0);
}