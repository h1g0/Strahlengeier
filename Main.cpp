#include <DxLib.h>
#include "Fps.h"
#include "Common.h"
#include "Screen.h"
#include "Player.h"
#include "BackGround.h"
#include "Global.h"
#include <boost/property_tree/xml_parser.hpp>

#define CONFIG_FILE_NAME "settings.xml"

FpsManager gFPS;
int gDrawScr; //�ꎞ�I�ȕ`���

/*################################################################
/*
/*    Strahlengeier << �V���g���[�����K�C�A�[ >> (��)
/*
/*##############################################################*/

int GameMain(){
	//Esc�L�[�ŏI��
	if(( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_START ) != 0 ){return 1;}
	///*===================�����ɃQ�[���{�̂̏���=====================================
	gGameManager.Exec();
	//==============================================================================*/
	return 0;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
	read_xml(CONFIG_FILE_NAME, gConfig);
	ChangeWindowMode(gConfig.get("WindowMode",true));
	SetMainWindowText( PJTITLE );
	if( DxLib_Init() == -1 ){
		 return -1;	// �G���[���N�����璼���ɏI��
	}
	LPCSTR font_path = "img\\font.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	AddFontResourceEx(font_path, FR_PRIVATE, NULL);
	ChangeFont("Neuropol",DX_CHARSET_DEFAULT);
	ChangeFontType( DX_FONTTYPE_ANTIALIASING_EDGE );
	shotButton = gConfig.get("Pad.Shot",PAD_INPUT_1);
	subButton = gConfig.get("Pad.Sub",PAD_INPUT_2);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, shotButton, gConfig.get("Key.Shot", KEY_INPUT_Z), -1, -1, -1 ) ;
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, subButton, gConfig.get("Key.Sub", KEY_INPUT_X), -1, -1, -1 ) ;

	gGameManager.Set(&GameManager::Init);
	for(;;){ //���C�����[�v
		//SetDrawScreen(DX_SCREEN_BACK);
		SetDrawScreen(gDrawScr);
		ClearDrawScreen();
		if(ProcessMessage()==-1 || GameMain()==1){break;} //�Q�[���{�̂����s
		SetDrawScreen( DX_SCREEN_BACK ) ; //���X�N���[���ɕ`��Ώۂ��ڂ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawGraph(0,0,gDrawScr,FALSE); //���ۂɕ`��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

		//FPS�`��
		{
			int NowFPS = gFPS.Get();
			int Col = (int)(255 * NowFPS / gFPS.GetDefaultFPS());
			DrawFormatString(SCR_WIDTH-80,SCR_HEIGHT-20,GetColor(255,Col,Col),"%02dFPS",NowFPS);
		}
		ScreenFlip();
		CaptureScreen();
		gFPS.Fix();
	}

	DxLib_End() ;		// �c�w���C�u�����g�p�̏I������
	write_xml(CONFIG_FILE_NAME,gConfig);

	return 0 ;		// �\�t�g�̏I��
}