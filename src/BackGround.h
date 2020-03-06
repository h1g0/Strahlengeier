#ifndef __BACKGROUND_H
#define __BACKGROUND_H
/*#################################

	背景クラス

#################################*/
class BackGround{
private:
	static const int _height2d = 480; //スクロールするのに使う、2D画像の縦の長さ
	static const int _height3d = 1500; //スクロールするのに使う3D画像の縦の長さ
	int _speed;
	int _image; //画像(2Dと3Dを兼ねる)
	bool _is3d; //背景は3Dか？
	int _scrollCnt; //スクロールカウンタ

	void _Draw2d();
	void _Draw3d();
public:
	BackGround():
	  _speed(0),
	  _image(0),
	  _is3d(false),
	  _scrollCnt(0){}

	void Set(int speed, int image, bool is3d);
	void Move();
	void Draw();
};

#endif