//FPS����
#include "Fps.h"

//=================================================================================================
//�R���X�g���N�^
//=================================================================================================
FpsManager::FpsManager(bool FixFps, bool ShowFps, int FixedFPS){
	IsFixFPS = FixFps;
	IsShowFPS = ShowFps;
	DefaultFPS = FixedFPS;
}

//=================================================================================================
//�f�X�g���N�^
//=================================================================================================
FpsManager::~FpsManager(){}

//=================================================================================================
//FPS�������I�ɌŒ肷��
//=================================================================================================
void FpsManager::Fix(){
	//�t���O�������Ă��Ȃ���Δ�����
	if(IsFixFPS == false){return;}

	int nowtime = GetNowCount(); //����̎���
	static int oldtime = 0; //�O��̎���
	static int frametime = 1000 / DefaultFPS;	//�K�莞��

	//�P�t���[���̎��Ԃƌ��݂̌o�ߎ��Ԃ��r
	int diftime = nowtime - oldtime;	//����

	for(;;){
		
		if(diftime >= frametime){ //�K�莞�Ԃ𒴉߁H
			oldtime = nowtime;	//���̌v���̂��ߍ���̎��Ԃ�ۑ�
			return;
		}else{ //�ҋ@
			WaitTimer(1);
			nowtime = GetNowCount();
			diftime = nowtime - oldtime;
		}
	}
}

/*===============================================================
FPS���擾����
=================================================================*/
int FpsManager::Get(){
	//FPS��\�����Ȃ��H
	if(IsShowFPS == false){return -1;}

	static int oldtime = GetNowCount(); //�O��̎���
	static int counter = 0;  //�J�E���^
	static int fps = 0;
	int nowtime = GetNowCount();
	counter++;
	//1000ms�߂������H
	if((nowtime - oldtime) >= 1000){
		int differ = ((nowtime - oldtime) - 1000); //�덷����
		//�O��̎��Ԃ��X�V
		oldtime = nowtime - differ;	//�덷�C��
		//FPS��ۑ�
		fps = counter;	
		//�J�E���^��������
		counter = 0;
	}
	return fps;
}