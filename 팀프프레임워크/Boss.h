#pragma once
#include "gameNode.h"

#define BULLET_MAX 30  
#define BOSS_SPEED 5   
#define BOSS_BACK  5   
//#define PI         3.14

enum BOSSSTATE
{

	//===========================//
	/*좌우 기본 상태*/
	R_IDLE, L_IDLE,
	//===========================//
	/*좌우 아플 떄 기본 상태*/
	R_HURT_IDLE, L_HURT_IDLE,
	//===========================//
	/*좌우로 움직이는 모션*/
	R_MOVE, L_MOVE,
	//===========================//
	/*좌우로 후방이동하는 모션*/
	R_BACK_MOVE, L_BACK_MOVE,
	//===========================//
	/*S는 검 G는 총을 이용한 공격*/
	R_SATK, L_SATK,
	R_GATK, L_GATK,
	//===========================//
	/*좌우 특수 공격기*/
	R_JATK, L_JATK,
	R_JUMP, L_JUMP,
	R_STAY, L_STAY,
	R_FALL, L_FALL,

	/*좌우 죽음*/
	R_DEAD, L_DEAD
	//===========================//
};

enum GRAVITY
{
	GROUND,
	JUMP,
	AIR,
	FALL
};

class PixelCol;
class player;
class Boss : public gameNode
{


private:
	//===========================//
	/*플레이어 할당*/
	player * _ply;
	int         _plyCenterX;
	int         _plyCenterY;
	//===========================//
	/*플레이어 할당을 위한 것*/
	PixelCol*   _bossPixelCol;
	//===========================//
private:
	//===========================//
	/*보스가 가지고 있는 것들 - 애니, 상태, 중력상태, 이미지, 이펙트, 렉트, 충돌 렉트*/
	animation * _bossAni;
	animation*  _bossHurtAni;
	BOSSSTATE   _bossState;
	image*      _bossImg;
	image*		_bossHurtImg;
	effect*     _bossSwordEf;
	RECT	    _bossRc;
	RECT		_swordBox;
	//===========================//
	/*특수 패턴 카운트*/
	int         _swAtkCount;
	int			_gunAtkCount;
	int         _specialAtkCount;
	/*기본 패턴 카운트*/
	int         _count;
	int			_leftMoveCount;
	int         _rightMoveCount;
	/*랜덤수 구하는 변수*/
	int			_rand;
	int         _firstPattern;
	//===========================//
	/*보스의 체력, 마력*/
	int         _bossHp;
	int         _bossMp;
	//===========================//	
	/*보스의 중점, 어택박스의 중점, 보스의 픽셀 탐사 좌표*/
	float       _centerX;
	float       _centerY;
	float       _atkBoxCenterX;
	float       _atkBoxCenterY;
	float	    _bossProbeX;
	float       _bossProbeY;
	//===========================//
	/*플레이어 및 보스가 가지고 있을 앵글*/
	float       _angle;
	float       _bossAngle;
	//===========================//
	/*보스의 퍼렁 픽셀 시간 제한 변수*/
	float       _time;
	//===========================//
	/*충돌박스가 사라지는 카운트*/
	int         _boxCount;
	//===========================//
	/*보스의 점프를 위한 변수*/
	float       _bossJumpPower;
	float       _bossGravityPower;
	//===========================//
	/*불값 - 점프 유무, 보스 1페이지 여부, 2페이지 여부, 다쳤는지 여부*/
	BOOL        _isBossJumping;
	BOOL        _isMotion1;
	BOOL        _isMotion2;
	BOOL		_isHurt;
	BOOL		_isRs;
	BOOL		_isLs;
	//===========================//


public:
	Boss();
	~Boss();
	//===========================//
	HRESULT     init();
	void        release();
	void        update();
	void        render();
	//===========================//
	/*보스의 중점 좌표*/
	float		GetCenterPosX() { return _centerX; }
	float		GetCenterPosY() { return _centerY; }
	//===========================//	               
	/*보스의 상태, 애니메이션, 렉트*/
	BOSSSTATE   GetState() { return _bossState; }
	animation*	GetAni() { return _bossAni; }
	RECT        &GetBossRc() { return _bossRc; }
	RECT        &GetSwordBox() { return _swordBox; }
	void        SetState(BOSSSTATE state) { _bossState = state; }
	void        SetAni(animation*  ani) { _bossAni = ani; }
	void        SetRc(RECT         rc) { _bossRc = rc; }
	//===========================//		
	/*겟 셋을 통한 보스의 체력*/
	int         &GetHp() { return _bossHp; }
	int         GetMp() { return _bossMp; }
	void        SetHp(int hp) { _bossHp = hp; }
	void        SetMp(int mp) { _bossMp = mp; }
	//===========================//	
	/*각종 업데이터 및 랜더에 들어갈 것들*/
	void        GetCenterUpdate();
	void        GetImageInit();
	void        BossMoveUpdate();
	void        OtherRender();
	void        SpecialAtk();
	void		PixelColUpdate();
	//===========================//		
	/*공격시에 생기는 충돌 박스(근거리)*/
	void        CreateAtkBox();
	//===========================//	
	/*링크*/
	void	    SetPlayerLink(player* ply) { _ply = ply; }
};