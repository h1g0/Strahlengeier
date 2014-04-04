#include "Screen.h"
#include "Common.h"
#include <DxLib.h>
#include<sstream>



void CaptureScreen(){
	DATEDATA Date;
	if((GetJoypadInputState( DX_INPUT_KEY_PAD1 ) & PAD_INPUT_10) !=0){
		GetDateTime( &Date );
		std::stringstream fname;
		fname <<"ScreenShot\\img" << Date.Year <<"_"<< Date.Mon <<"_"<< Date.Day <<"_"<<Date.Hour <<"_"<< Date.Min <<"_"<<GetNowCount()%1000 << ".png";
		SaveDrawScreenToPNG( 0 , 0 , SCR_WIDTH , SCR_HEIGHT ,fname.str().c_str()) ;
	}
}