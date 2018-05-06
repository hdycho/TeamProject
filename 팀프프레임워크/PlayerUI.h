#pragma once
#include "gameNode.h"

class PlayerUI : public gameNode
{

private:

	struct tagSKILL
	{
		image* img;
		RECT imagerc;
		int framex, count, frameupdatetime;
		bool UION;
	};

	struct tagLINE
	{
		image* img;
		RECT imagerc;
		int width;
		float x, y;
		int count;
	};

	tagSKILL _skillq;
	tagSKILL _skillw;
	tagSKILL _skille;
	tagLINE _hpline;
	tagLINE _ptline;

	image* _hpimage;
	RECT _hpimagerc;

	// SkillW bool
	bool _isSkillHealUI;
	// for loading
	bool _isSkillWUILoad;

	// SkillE bool
	bool _isSkill2UI;
	// for loading
	bool _isSkillEUILoad;

	int _countSkillQ;
	int _countSkillE;
	int _countSkillW;

	//shop
	image* _shopimage;
	RECT _shopimagerc;


public:
	// SkillW bool (frame)
	bool _frameSkillQ;
	// SkillW bool (frame)
	bool _frameSkillW;
	// SkillE bool (frame)
	bool _frameSkillE;

	int _indexQ, _index, _indexHeal;

	PlayerUI();
	~PlayerUI();

	virtual HRESULT init();
	virtual void update();
	virtual void render();


	//스킬 이미지 변화 함수
	void SkillQImageChange();
	void SkillWImageChange();
	void SkillEImageChange();

	//스킬 입력 함수 
	void SkillQ();//스킬Q
	void SkillW();//스킬W
	void SkillE();//스킬E

				  //HP,PT
	void SetHpLine(float CurrentHp, float MaxHp);//체력줄
	void SetPtLine(float CurrnetPt, float MaxPt);//기력줄


												 //========================접근자============================
												 //구조체는 포인터값으로
	tagSKILL* GetSkillQ() { return &_skillq; }//Q 구조체 접근자
	tagSKILL* GetSkillW() { return &_skillw; }//W 구조체 접근자
	tagSKILL* GetSkillE() { return &_skille; }//E 구조체 접근자

	tagLINE* GetHpLine() { return &_hpline; }//hp 구조체 접근자
	tagLINE* GetPtLine() { return &_ptline; }//Pt 구조체 접그자

											 // SkillW (bool)
	void setSkillHealUIBool(bool skblh) { _isSkillHealUI = skblh; }
	bool getSkillHealUIBool() { return _isSkillHealUI; }
	// for SkillW (UI) loading
	void setSkillHealUILoad(bool skhl) { _isSkillWUILoad = skhl; }
	bool getSkillHealUILoad() { return _isSkillWUILoad; }

	// SkillE (bool)
	void setSkill2UIBool(bool skbl) { _isSkill2UI = skbl; }
	bool getSkill2UIBool() { return _isSkill2UI; }
	// for SkillE (UI) loading
	void setSkill2UILoad(bool skel) { _isSkillEUILoad = skel; }
	bool getSkill2UILoad() { return _isSkillEUILoad; }
};
