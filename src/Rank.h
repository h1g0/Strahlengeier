#ifndef __RANK_H
#define __RANK_H

//“à•”ƒ‰ƒ“ƒNƒNƒ‰ƒX
class InnerRank{
	int _rank;
	int _frame;
	bool _increased;
public:
	static const int RankMin = 1;
	static const int RankMax = 42;
	const double RankInv;
	static const int IncreaseFrm = 60 * 10;
	void Init(){
		_rank=RankMin;
		_frame=0;
		_increased = false;
	}
	InnerRank(): RankInv(1/static_cast<double>(RankMax)){
		Init();
	}
	int Get()const{
		return _rank;
	}
	int GetInv()const{
		return RankMax - _rank;
	}
	double GetLiner()const{ //0 < return <=1.0
		return Get() * RankInv;
	}
	int GetLiner(int val)const{
		return static_cast<int>(val * GetLiner());
	}
	double GetInvLiner()const{
		return GetInv() * RankInv;
	}
	int GetInvLiner(int val)const{
		return static_cast<int>(val * GetInvLiner());
	}
	bool GetIsIncreased()const{
		return _increased;
	}
	void ResetIsIncreased(){
		_increased = false;
	}
	void Set(int rank){
		if(rank<RankMin){
			rank=RankMin;
		}else if(rank>RankMax){
			rank=RankMax;
		}
		_rank=rank;
		_frame=0;
	}
	void Add(int rank){
		Set(Get()+rank);
		_increased = true;
	}
	void Increase(){
		Add(1);
	}
	void Exec(){
		if(_frame++>=IncreaseFrm){
			Increase();
		}
	}
};

#endif