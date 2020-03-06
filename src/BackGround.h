#ifndef __BACKGROUND_H
#define __BACKGROUND_H
/*#################################

	�w�i�N���X

#################################*/
class BackGround{
private:
	static const int _height2d = 480; //�X�N���[������̂Ɏg���A2D�摜�̏c�̒���
	static const int _height3d = 1500; //�X�N���[������̂Ɏg��3D�摜�̏c�̒���
	int _speed;
	int _image; //�摜(2D��3D�����˂�)
	bool _is3d; //�w�i��3D���H
	int _scrollCnt; //�X�N���[���J�E���^

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