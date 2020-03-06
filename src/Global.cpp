#include "Global.h"

GameManager gGameManager;
BackGround gBGround;
PlayerShip gPlayer;
ParticleGroup gParticle(1000);
EnmGroup gEnemy(50);
EBGroup gEnemyBullet;
InnerRank gRank;
int shotButton;
int subButton;

boost::property_tree::ptree gConfig; //İ’èƒtƒ@ƒCƒ‹
boost::unordered_map < std::string, int> gImg;