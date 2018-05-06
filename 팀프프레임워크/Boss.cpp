#include "stdafx.h"
#include "Boss.h"
#include "player.h"
#include  "PixelCol.h"

		/*��� �̴ϼȶ����� - �ʱ�ȭ�ϴ� �κ�*/
Boss:: Boss()
	://======================//
		/*������ ���� �� ���� �ޱ۰� �⺻ ����*/
	  _angle           (0)    ,
	 //======================//
		/*������ ü�°� ��ųȽ���� ���� ����*/
	  _bossHp          (250)  ,
	  _bossMp          (100)  ,
	 //======================//
		/*������ Ư�� ������ �ҷ��������� ī��Ʈ ����*/
	  _swAtkCount      (0)    ,
	  _gunAtkCount     (0)    ,
	  _specialAtkCount (0)    ,
	//=======================//
		/*�⺻ ������ ���� ī��Ʈ*/
	  _count		   (0)    ,
	  _leftMoveCount   (0)    ,
	  _rightMoveCount  (0)    ,
	//=======================//
		/*�ٰŸ� ���������� ���� �Һ���*/
	  _boxCount        (0)    ,
	//========================//
		/*�ٰŸ� ���� �浹 �ڽ�*/
	  _atkBoxCenterX   (0)    ,
   	  _atkBoxCenterY   (0)    ,
	//========================//
	  _isBossJumping   (false),
	  _isMotion1       (true ),
	  _isMotion2       (false),
	  _isHurt          (false),
	  _bossJumpPower   (0)    ,
	  _bossGravityPower(0)    ,
	//========================//
	  _rand            (0)    ,
	  _firstPattern    (0)    ,
	  _bossProbeX      (0)    ,
	  _bossProbeY      (0)    ,
	  _time            (0)

{}
Boss::~Boss        (){}

HRESULT Boss::init ()
{
	//=======================//
		/*�÷��̾� �Ҵ�*/
	_ply          = new player   ;
	_ply->init     ()            ;
	//=======================//
	_bossPixelCol = new PixelCol ;
	_bossPixelCol->init(10, 10);
	//=======================//
		/*������ �̹��� �ʱ�ȭ*/
	GetImageInit   ()            ;
	//=======================//
		/*���� ������ ������ ��Ʈ �ʱ�ȭ*/
	_centerX   = 800            ;
	_centerY   = 500             ;

	_bossProbeX = _centerX + _bossImg->getFrameWidth()  / 2;
	_bossProbeY = _centerY + _bossImg->getFrameHeight() / 2;


	_bossRc    = RectMakeCenter(_centerX, _centerY, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	//=======================//
	return S_OK;
}
//===========================//
void Boss::release () 
{ 
	SAFE_DELETE(_ply         )   ;
	SAFE_DELETE(_bossPixelCol)   ;
}
//===========================//
void Boss::update  ()
{
	//=======================//
		/*������ ��Ʈ�� ������ǥ ��� ������Ʈ*/
	GetCenterUpdate();
	//=======================//
		/*������ �ȼ� �ݸ���*/
	_bossPixelCol->UpdatePosition(_bossProbeX, _bossProbeY);
	PixelColUpdate ();
		/*������ ������ �κ�*/
	BossMoveUpdate ();
	//=======================//
		/*���� ���� ���� ����Ʈ �浹 �ڽ�*/
	CreateAtkBox   ();
	SpecialAtk     ();
	//=======================//
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
	//=======================//
}

void Boss::render()
{
	//cout << _specialAtkCount << endl;
	//cout << _plyCenterX << "..." << _plyCenterY << endl;
	cout << _bossState << "..." << endl;
	//=======================//
		/*���� ���¿� ���� ���� ���� ó��*/
	if (_isHurt == true)
	{
		_bossHurtImg->aniRender(getMemDC(), _bossRc.left - 10, _bossRc.top, _bossHurtAni);
	}
	
	OtherRender();
	//=======================//
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		Rectangle(getMemDC(), _bossRc.left,   _bossRc.top,   _bossRc.right,   _bossRc.bottom);
		Rectangle(getMemDC(), _swordBox.left, _swordBox.top, _swordBox.right, _swordBox.bottom);
		Rectangle(getMemDC(), _swordBox.left, _swordBox.top, _swordBox.right, _swordBox.bottom);
	}
	//=======================//
	EFFECTMANAGER->render();
	//=======================//
}

/*������ ������ ����ؼ� ������Ʈ ���ֱ� ���� ��.*/
void Boss::GetCenterUpdate()
{
	/*���� ���� ��ǥ*/
	_centerX = _bossRc.left + (_bossRc.right  - _bossRc.left)  / 2;
	_centerY = _bossRc.top  + (_bossRc.bottom - _bossRc.top)   / 2;

	/*�÷��̾� ���� ��ǥ*/
	_plyCenterX = GetCenterPos(_ply->getKnightImage().rc).x       ; 
	_plyCenterY = GetCenterPos(_ply->getKnightImage().rc).y       ;

	/*���� �ȼ� ���� ��ǥ*/
	_bossProbeX = _centerX + _bossImg->getFrameWidth()  / 2;
	_bossProbeY = _centerY + _bossImg->getFrameHeight() / 2;

	/*������ �÷��̾� �ޱ۰� */
	_angle = getAngle(_centerX, _centerY, _plyCenterX, _plyCenterY);
}
