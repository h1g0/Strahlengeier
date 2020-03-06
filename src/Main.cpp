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
int gDrawScr; //一時的な描画先

/*################################################################
/*
/*    Strahlengeier << シュトラーレンガイアー >> (仮)
/*
/*##############################################################*/

int GameMain(){
	//Escキーで終了
	if(( GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_START ) != 0 ){return 1;}
	///*===================ここにゲーム本体の処理=====================================
	gGameManager.Exec();
	//==============================================================================*/
	return 0;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ){
	read_xml(CONFIG_FILE_NAME, gConfig);
	ChangeWindowMode(gConfig.get("WindowMode",true));
	SetMainWindowText( PJTITLE );
	if( DxLib_Init() == -1 ){
		 return -1;	// エラーが起きたら直ちに終了
	}
	LPCSTR font_path = "img\\font.ttf"; // 読み込むフォントファイルのパス
	AddFontResourceEx(font_path, FR_PRIVATE, NULL);
	ChangeFont("Neuropol",DX_CHARSET_DEFAULT);
	ChangeFontType( DX_FONTTYPE_ANTIALIASING_EDGE );
	shotButton = gConfig.get("Pad.Shot",PAD_INPUT_1);
	subButton = gConfig.get("Pad.Sub",PAD_INPUT_2);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, shotButton, gConfig.get("Key.Shot", KEY_INPUT_Z), -1, -1, -1 ) ;
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, subButton, gConfig.get("Key.Sub", KEY_INPUT_X), -1, -1, -1 ) ;

	gGameManager.Set(&GameManager::Init);
	for(;;){ //メインループ
		//SetDrawScreen(DX_SCREEN_BACK);
		SetDrawScreen(gDrawScr);
		ClearDrawScreen();
		if(ProcessMessage()==-1 || GameMain()==1){break;} //ゲーム本体を実行
		SetDrawScreen( DX_SCREEN_BACK ) ; //裏スクリーンに描画対象を移す
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawGraph(0,0,gDrawScr,FALSE); //実際に描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

		//FPS描画
		{
			int NowFPS = gFPS.Get();
			int Col = (int)(255 * NowFPS / gFPS.GetDefaultFPS());
			DrawFormatString(SCR_WIDTH-80,SCR_HEIGHT-20,GetColor(255,Col,Col),"%02dFPS",NowFPS);
		}
		ScreenFlip();
		CaptureScreen();
		gFPS.Fix();
	}

	DxLib_End() ;		// ＤＸライブラリ使用の終了処理
	write_xml(CONFIG_FILE_NAME,gConfig);

	return 0 ;		// ソフトの終了
}