#include "BackGround.h"
#include <DxLib.h>
#include "Common.h"
#include "Global.h"
void BackGround::Set(int speed, int image, bool is3d){
	_speed = speed;
	_image = image;
	_is3d = is3d;

	if(is3d){
		//3D関係の設定
		SetupCamera_Perspective( PHI_F /4.0f );
		SetUseLighting( TRUE ) ;
		SetGlobalAmbientLight( GetColorF( 1.0f, 1.0f, 1.0f, 0.0f ) ) ;
		SetCameraNearFar( 400.0f, 1000.0f ) ;
		SetFogEnable( TRUE ) ;
		SetFogColor( 0, 0, 0 ) ;
		SetFogStartEnd( 600.0f, 900.0f ) ;
		SetLightEnable( TRUE ) ;
		ChangeLightTypeDir( VGet( -0.8f, 0.8f, 0.5f ) ) ;
		SetLightDifColor( GetColorF(  1.0f,  1.0f,  1.0f, 0.0f ) ) ;
		SetLightSpcColor( GetColorF(  1.0f,  1.0f,  1.0f, 0.0f ) ) ;
		SetLightAmbColor( GetColorF( 1.0f, 1.0f, 1.0f, 0.0f ) ) ;

		MV1SetScale(_image,VGet(1.0f,1.0f,1.5f)) ;
		MV1SetWireFrameDrawFlag(_image,TRUE);
		//MV1SetDifColorScale( _image, GetColorF(0.1f,1.0f,0.1f,0.5f) ) ; //色の設定、何故かアルファ値が効かない？
		//MV1SetOpacityRate(_image,0.5f); //透明度の設定
		int MatNum = MV1GetMaterialNum(_image);
		for(int i=0;i<MatNum;i++){
			MV1SetMaterialDrawBlendMode(_image,i,DX_BLENDMODE_ADD);
			MV1SetMaterialDrawBlendParam(_image,i,192);
		}
	}
}

void BackGround::Move(){
	_scrollCnt+=_speed;
	if(_is3d){
		_scrollCnt %= _height3d;
	}else{
		_scrollCnt %= _height2d;
	}
}

void BackGround::Draw(){
	if(_is3d){
		_Draw3d();
	}else{
		_Draw2d();
	}
}

void BackGround::_Draw2d(){
	//あとで書く
}

void BackGround::_Draw3d(){
	// カメラの位置と回転値をセット、カメラの位置は原点
	if (gConfig.get("LowEffect", false) == true){
		MV1SetDifColorScale(_image, GetColorF(0.25f, 1.0f, 0.25f, 0.3f));
		SetCameraPositionAndAngle(VGet(0.0f, 200.0f, 0.0f), PHI_F * 135.0f / -180.0f, 0.0f, 0.0f);
		MV1SetPosition(_image, VGet(0.0f, 400.0f, _scrollCnt + 0.0f));
		MV1DrawModel(_image);
		MV1SetPosition(_image, VGet(0.0f, 400.0f, (float)(_scrollCnt - _height3d))); //2枚目用に位置をセットしなおす
		MV1DrawModel(_image);
	}
	else{
		SetCameraPositionAndAngle(VGet(0.0f, 200.0f, 0.0f), PHI_F * 135.0f / -180.0f, 0.0f, 0.0f);
		MV1SetPosition(_image, VGet(0.0f, 400.0f, _scrollCnt + 0.0f));
		MV1DrawModel(_image);
		MV1SetPosition(_image, VGet(0.0f, 400.0f, (float)(_scrollCnt - _height3d))); //2枚目用に位置をセットしなおす
		MV1DrawModel(_image);
		static const int downScale = 8;
		int tempScr = MakeScreen(SCR_WIDTH / 8, SCR_HEIGHT / 8, TRUE); //ぼかし用の一時的な描画先
		GraphFilterBlt(gDrawScr, tempScr, DX_GRAPH_FILTER_DOWN_SCALE, downScale); //縮小
		GraphFilter(tempScr, DX_GRAPH_FILTER_GAUSS, 8, 10); //ガウスぼかし
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		//一旦半透明の黒で上書き
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		DrawBox(0, 0, SCR_WIDTH, SCR_HEIGHT, GetColor(0, 0, 0), TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 128);
		SetDrawBright(64, 255, 64);
		DrawExtendGraph(0, 0, SCR_WIDTH, SCR_HEIGHT, tempScr, FALSE);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawMode(DX_DRAWMODE_NEAREST);
		DeleteGraph(tempScr); //一時的な描画先の消去
	}
		
}
