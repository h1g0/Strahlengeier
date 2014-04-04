#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include<string>
class GameManager{
	int _frame;
	void (*_ExecFunc)(GameManager& parent, int frame);
	int _nowBGM;
	int _imgGameOver;
public:
	void Set(void (*ExecFunc)(GameManager& parent, int frame)){
		_ExecFunc = ExecFunc;
		_frame = -1; //Setした後にインクリメントするので、その後0になるよう-1
	}
	void SetBGM(std::string filepath,bool playNow=true);
	void PlayBGM();
	void StopBGM();
	GameManager(): _ExecFunc(nullptr),_frame(0){
		//Set(&Init);
	}
	void Exec(){
		if(_ExecFunc==nullptr){return;}
		_ExecFunc(*this,_frame);
		_frame++;
	}
	static void Init(GameManager& parent, int frame);

	static void LoadMainMenu(GameManager& parent, int frame);
	static void FrontMenu(GameManager& parent, int frame);
	static void UnloadMainMenu(GameManager& parent, int frame);
	static void KeyConfig1(GameManager& parent, int frame);
	static void KeyConfig2(GameManager& parent, int frame);
	static void KeyConfig3(GameManager& parent, int frame);
	static void KeyConfig4(GameManager& parent, int frame);

	static void LoadGameMain(GameManager& parent, int frame);
	static void LoadGameSt1(GameManager& parent, int frame);

	static void GameMain(GameManager& parent, int frame);
	static void GameMainStatus(GameManager& parent, int frame);
	static void GameOver(GameManager& parent, int frame);

	static void GameSt1(GameManager& parent, int frame);

	static void UnloadGameMain(GameManager& parent, int frame);
	static void UnloadGameSt1(GameManager& parent, int frame);
};
#endif
