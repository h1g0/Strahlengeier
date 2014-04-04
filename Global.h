#ifndef __GLOBAL_H
#define __GLOBAL_H
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/unordered_map.hpp>

#include"Common.h"
#include "GameManager.h"
#include "BackGround.h"
#include "Particle.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Rank.h"
extern GameManager gGameManager;
extern BackGround gBGround;
extern PlayerShip gPlayer;
extern ParticleGroup gParticle;
extern EnmGroup gEnemy;
extern EBGroup gEnemyBullet;
extern InnerRank gRank;
extern int shotButton;
extern int subButton;
extern boost::property_tree::ptree gConfig; //ê›íËÉtÉ@ÉCÉã
extern boost::unordered_map < std::string, int> gImg;

#endif