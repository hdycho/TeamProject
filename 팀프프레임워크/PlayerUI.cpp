#include "stdafx.h"
#include "PlayerUI.h"


PlayerUI::PlayerUI()
{
}


PlayerUI::~PlayerUI()
{
}

HRESULT PlayerUI::init()
{
	_skillq.UION = false;
	_skillw.UION = false;
	_skille.UION = false;

	_skillq.img = new image;
	IMAGEMANAGER->addImage("SkillQ", PathFile("image", "Skill1").c_str(), 150, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SkillQON", PathFile("image", "SkillQON").c_str(), 750, 77, 5, 1, true, RGB(255, 0, 255));
	_skillw.img = new image;
	IMAGEMANAGER->addImage("SkillW", PathFile("image", "Skill2").c_str(), 150, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SkillWON", PathFile("image", "SkillWON").c_str(), 1200, 77, 8, 1, true, RGB(255, 0, 255));
	_skille.img = new image;
	IMAGEMANAGER->addImage("SkillE", PathFile("image", "Skill3").c_str(), 150, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SkillEON", PathFile("image", "SkillEON").c_str(), 1950, 77, 13, 1, true, RGB(255, 0, 255));

	_hpimage = new image;
	_hpimage = IMAGEMANAGER->addImage("HPUI", PathFile("image", "PlayerUi").c_str(), 200, 89, true, RGB(255, 0, 255));

	_hpline.img = new image;
	_hpline.img = IMAGEMANAGER->addImage("HpLine", PathFile("image", "HpUp").c_str(), 117, 17, true, RGB(255, 0, 255));
	_hpline.count = 0;

	_ptline.img = new image;
	_ptline.img = IMAGEMANAGER->addImage("Ptline", PathFile("image", "PtUp").c_str(), 109, 15, true, RGB(255, 0, 255));
	_ptline.count = 0;

	//shop
	_shopimage = new image;
	_shopimage = IMAGEMANAGER->addImage("Shop", PathFile("image", "상점유아이").c_str(), 130, 77, true, RGB(255, 0, 255));

	_skillq.UION = true;
	_skillw.UION = false;
	_skille.UION = false;

	_skillq.framex = 0;
	_skillw.framex = 0;
	_skille.framex = 0;


	SkillQImageChange();
	SkillWImageChange();
	SkillEImageChange();

	// SkillE bool
	_frameSkillQ = true;
	// SkillE bool
	!_isSkill2UI;
	_frameSkillW = false;
	// SkillW bool
	!_isSkillHealUI;
	_frameSkillE = false;

	_countSkillQ = _countSkillE = _countSkillW = 0;
	_indexQ = _index = _indexHeal = 0;

	return S_OK;
}

void PlayerUI::update()
{
	//HpUI 좌표
	//_hpimagerc = RectMake(CAM->getCamRc().left, CAM->getCamRc().top, 200, 89);

	//skillQ 좌표
	//_skillq.imagerc = RectMake(CAM->getCamRc().left + 350, CAM->getCamRc().top, 150, 77);

	//skillW 좌표
	//_skillw.imagerc = RectMake(CAM->getCamRc().left + 500, CAM->getCamRc().top, 150, 77);
	
	//skillE 좌표
	//_skille.imagerc = RectMake(CAM->getCamRc().left + 650, CAM->getCamRc().top, 150, 77);

	//HPLine 좌표
	//_hpline.imagerc = RectMake(CAM->getCamRc().left + 75, CAM->getCamRc().top + 11, _hpline.img->getFrameWidth(), _hpline.img->getFrameHeight());

	//PTLine 좌표
	//_ptline.imagerc = RectMake(CAM->getCamRc().left + 7, CAM->getCamRc().top + 70, _ptline.img->getFrameWidth(), _ptline.img->getFrameHeight());

	//shoprc
	//_shopimagerc = RectMake(CAM->getCamRc().left + 210, CAM->getCamRc().top, 130, 77);

	SkillQImageChange();
	SkillWImageChange();
	SkillEImageChange();

	// for SkillQ (frame)
	if (_frameSkillQ == true)
	{
		SkillQ();
	}
	// for SkillW (frame)
	if (_frameSkillW == true)
	{
		_countSkillW++;
		SkillW();
	}
	// for SkillE (frame)
	if (_frameSkillE == true)
	{
		_countSkillE++;
		SkillE();
	}

	// SkillW 샀을때
	if (_isSkillHealUI == true)
	{
		_skillw.UION = true;
	}
	// SkillE 샀을때
	if (_isSkill2UI == true)
	{
		_skille.UION = true;
	}
}

void PlayerUI::render()
{
	//Rectangle(getMemDC(), _hpimagerc.left, _hpimagerc.top, _hpimagerc.right, _hpimagerc.bottom);
	_hpimage->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top);//HPUI
																  //Rectangle(getMemDC(), _hpline.imagerc.left, _hpline.imagerc.top, _hpline.imagerc.right, _hpline.imagerc.bottom);
	_hpline.img->render(getMemDC(),CAM->getCamRc().left+75, CAM->getCamRc().top+11, 0, 0, _hpline.width, 17);//HPLine
																										//Rectangle(getMemDC(), _ptline.imagerc.left, _ptline.imagerc.top, _ptline.imagerc.right, _ptline.imagerc.bottom);
	_ptline.img->render(getMemDC(), CAM->getCamRc().left + 7, CAM->getCamRc().top + 70, 0, 0, _ptline.width, 15);//PtLine

	if (_skillq.UION == false)
	{
		//Rectangle(getMemDC(), _skillq.imagerc.left, _skillq.imagerc.top, _skillq.imagerc.right, _skillq.imagerc.bottom);
		_skillq.img->render(getMemDC(), CAM->getCamRc().left + 350, CAM->getCamRc().top);
	}
	if (_skillw.UION == false)
	{
		//Rectangle(getMemDC(), _skillw.imagerc.left, _skillw.imagerc.top, _skillw.imagerc.right, _skillw.imagerc.bottom);
		_skillw.img->render(getMemDC(), CAM->getCamRc().left + 500, CAM->getCamRc().top);
	}
	if (_skille.UION == false)
	{
		//Rectangle(getMemDC(), _skille.imagerc.left, _skille.imagerc.top, _skille.imagerc.right, _skille.imagerc.bottom);
		_skille.img->render(getMemDC(), CAM->getCamRc().left + 650, CAM->getCamRc().top);
	}
	if (_skillq.UION == true)
	{
		_skillq.img->frameRender(getMemDC(), CAM->getCamRc().left + 350, CAM->getCamRc().top);
	}
	if (_skillw.UION == true)
	{
		_skillw.img->frameRender(getMemDC(), CAM->getCamRc().left + 500, CAM->getCamRc().top);
	}
	if (_skille.UION == true)
	{
		_skille.img->frameRender(getMemDC(), CAM->getCamRc().left + 650, CAM->getCamRc().top);
	}

	//shop
	_shopimage->render(getMemDC(), CAM->getCamRc().left+210, CAM->getCamRc().top);
}

//_skillui->update() 안쓸때 쓰는거
void PlayerUI::SkillQImageChange()
{
	if (!_skillq.UION)
	{
		_skillq.img = IMAGEMANAGER->findImage("SkillQ");
	}
	if (_skillq.UION == true)
	{
		_skillq.img = IMAGEMANAGER->findImage("SkillQON");
	}
}

//_skillui->update() 안쓸때 쓰는거
void PlayerUI::SkillWImageChange()
{
	if (!_skillw.UION)
	{
		_skillw.img = IMAGEMANAGER->findImage("SkillW");
	}
	if (_skillw.UION == true)
	{
		_skillw.img = IMAGEMANAGER->findImage("SkillWON");
	}

}

//_skillui->update() 안쓸때 쓰는거
void PlayerUI::SkillEImageChange()
{
	if (!_skille.UION)
	{
		_skille.img = IMAGEMANAGER->findImage("SkillE");
	}
	if (_skille.UION == true)
	{
		_skille.img = IMAGEMANAGER->findImage("SkillEON");
	}
}

//이거 같이상희 하면서 고치는 거
void PlayerUI::SkillQ()
{
	_skillq.img->setFrameX(0);
}

//이거 같이상희 하면서 고치는 거
void PlayerUI::SkillW()
{
	if (_countSkillW >= 30)
	{
		_indexHeal++;
		if (_indexHeal > 12)
		{
			_frameSkillW = false;
			_indexHeal = 0;
		}
		_skillw.img->setFrameX(_indexHeal);
		_countSkillW = 0;
	}
}

//이거 같이상희 하면서 고치는 거
void PlayerUI::SkillE()
{
	if (_countSkillE >= 100)
	{
		_index++;
		if (_index > 12)
		{
			_frameSkillE = false;
			_index = 0;
		}
		_skille.img->setFrameX(_index);
		_countSkillE = 0;
	}
}

//HP 함수  CurrentHp=현재체력 MaxHp=전체 체력
void PlayerUI::SetHpLine(float CurrentHp, float MaxHp)
{
	_hpline.width = (CurrentHp / MaxHp)*_hpline.img->getWidth();
}

//PT 함수 CurrnetPt=현재 마나 MaxPt=전체 마나
void PlayerUI::SetPtLine(float CurrnetPt, float MaxPt)
{
	_ptline.width = (CurrnetPt / MaxPt)*_ptline.img->getWidth();
}