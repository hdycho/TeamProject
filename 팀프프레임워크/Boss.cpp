#include "stdafx.h"
#include "Boss.h"
#include "player.h"
#include  "PixelCol.h"

		/*멤버 이니셜라이즈 - 초기화하는 부분*/
Boss:: Boss()
	://======================//
		/*보스가 총을 쏠 떄의 앵글값 기본 설정*/
	  _angle           (0)    ,
	 //======================//
		/*보스의 체력과 스킬횟수를 위한 변수*/
	  _bossHp          (250)  ,
	  _bossMp          (100)  ,
	 //======================//
		/*보스의 특수 패턴을 불러오기위한 카운트 변수*/
	  _swAtkCount      (0)    ,
	  _gunAtkCount     (0)    ,
	  _specialAtkCount (0)    ,
	//=======================//
		/*기본 패턴을 위한 카운트*/
	  _count		   (0)    ,
	  _leftMoveCount   (0)    ,
	  _rightMoveCount  (0)    ,
	//=======================//
		/*근거리 공격판정을 위한 불변수*/
	  _boxCount        (0)    ,
	//========================//
		/*근거리 공격 충돌 박스*/
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
		/*플레이어 할당*/
	_ply          = new player   ;
	_ply->init     ()            ;
	//=======================//
	_bossPixelCol = new PixelCol ;
	_bossPixelCol->init(10, 10);
	//=======================//
		/*보스의 이미지 초기화*/
	GetImageInit   ()            ;
	//=======================//
		/*보스 중점과 보스의 렉트 초기화*/
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
		/*보스의 렉트의 중점좌표 계속 업데이트*/
	GetCenterUpdate();
	//=======================//
		/*보스의 픽셀 콜리전*/
	_bossPixelCol->UpdatePosition(_bossProbeX, _bossProbeY);
	PixelColUpdate ();
		/*보스의 움직임 부분*/
	BossMoveUpdate ();
	//=======================//
		/*보스 근접 공격 이펙트 충돌 박스*/
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
		/*보스 상태에 따른 랜더 예외 처리*/
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

/*보스의 중점을 계속해서 업데이트 해주기 위한 것.*/
void Boss::GetCenterUpdate()
{
	/*보스 중점 좌표*/
	_centerX = _bossRc.left + (_bossRc.right  - _bossRc.left)  / 2;
	_centerY = _bossRc.top  + (_bossRc.bottom - _bossRc.top)   / 2;

	/*플레이어 중점 좌표*/
	_plyCenterX = GetCenterPos(_ply->getKnightImage().rc).x       ; 
	_plyCenterY = GetCenterPos(_ply->getKnightImage().rc).y       ;

	/*보스 픽셀 감지 좌표*/
	_bossProbeX = _centerX + _bossImg->getFrameWidth()  / 2;
	_bossProbeY = _centerY + _bossImg->getFrameHeight() / 2;

	/*보스랑 플레이어 앵글값 */
	_angle = getAngle(_centerX, _centerY, _plyCenterX, _plyCenterY);
}
