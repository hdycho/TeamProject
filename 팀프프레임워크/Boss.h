#pragma once
#include "gameNode.h"

#define BULLET_MAX 30  
#define BOSS_SPEED 5   
#define BOSS_BACK  5   
//#define PI         3.14

enum BOSSSTATE
{

	//===========================//
	/*�¿� �⺻ ����*/
	R_IDLE, L_IDLE,
	//===========================//
	/*�¿� ���� �� �⺻ ����*/
	R_HURT_IDLE, L_HURT_IDLE,
	//===========================//
	/*�¿�� �����̴� ���*/
	R_MOVE, L_MOVE,
	//===========================//
	/*�¿�� �Ĺ��̵��ϴ� ���*/
	R_BACK_MOVE, L_BACK_MOVE,
	//===========================//
	/*S�� �� G�� ���� �̿��� ����*/
	R_SATK, L_SATK,
	R_GATK, L_GATK,
	//===========================//
	/*�¿� Ư�� ���ݱ�*/
	R_JATK, L_JATK,
	R_JUMP, L_JUMP,
	R_STAY, L_STAY,
	R_FALL, L_FALL,

	/*�¿� ����*/
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
	/*�÷��̾� �Ҵ�*/
	player * _ply;
	int         _plyCenterX;
	int         _plyCenterY;
	//===========================//
	/*�÷��̾� �Ҵ��� ���� ��*/
	PixelCol*   _bossPixelCol;
	//===========================//
private:
	//===========================//
	/*������ ������ �ִ� �͵� - �ִ�, ����, �߷»���, �̹���, ����Ʈ, ��Ʈ, �浹 ��Ʈ*/
	animation * _bossAni;
	animation*  _bossHurtAni;
	BOSSSTATE   _bossState;
	image*      _bossImg;
	image*		_bossHurtImg;
	effect*     _bossSwordEf;
	RECT	    _bossRc;
	RECT		_swordBox;
	//===========================//
	/*Ư�� ���� ī��Ʈ*/
	int         _swAtkCount;
	int			_gunAtkCount;
	int         _specialAtkCount;
	/*�⺻ ���� ī��Ʈ*/
	int         _count;
	int			_leftMoveCount;
	int         _rightMoveCount;
	/*������ ���ϴ� ����*/
	int			_rand;
	int         _firstPattern;
	//===========================//
	/*������ ü��, ����*/
	int         _bossHp;
	int         _bossMp;
	//===========================//	
	/*������ ����, ���ùڽ��� ����, ������ �ȼ� Ž�� ��ǥ*/
	float       _centerX;
	float       _centerY;
	float       _atkBoxCenterX;
	float       _atkBoxCenterY;
	float	    _bossProbeX;
	float       _bossProbeY;
	//===========================//
	/*�÷��̾� �� ������ ������ ���� �ޱ�*/
	float       _angle;
	float       _bossAngle;
	//===========================//
	/*������ �۷� �ȼ� �ð� ���� ����*/
	float       _time;
	//===========================//
	/*�浹�ڽ��� ������� ī��Ʈ*/
	int         _boxCount;
	//===========================//
	/*������ ������ ���� ����*/
	float       _bossJumpPower;
	float       _bossGravityPower;
	//===========================//
	/*�Ұ� - ���� ����, ���� 1������ ����, 2������ ����, ���ƴ��� ����*/
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
	/*������ ���� ��ǥ*/
	float		GetCenterPosX() { return _centerX; }
	float		GetCenterPosY() { return _centerY; }
	//===========================//	               
	/*������ ����, �ִϸ��̼�, ��Ʈ*/
	BOSSSTATE   GetState() { return _bossState; }
	animation*	GetAni() { return _bossAni; }
	RECT        &GetBossRc() { return _bossRc; }
	RECT        &GetSwordBox() { return _swordBox; }
	void        SetState(BOSSSTATE state) { _bossState = state; }
	void        SetAni(animation*  ani) { _bossAni = ani; }
	void        SetRc(RECT         rc) { _bossRc = rc; }
	//===========================//		
	/*�� ���� ���� ������ ü��*/
	int         &GetHp() { return _bossHp; }
	int         GetMp() { return _bossMp; }
	void        SetHp(int hp) { _bossHp = hp; }
	void        SetMp(int mp) { _bossMp = mp; }
	//===========================//	
	/*���� �������� �� ������ �� �͵�*/
	void        GetCenterUpdate();
	void        GetImageInit();
	void        BossMoveUpdate();
	void        OtherRender();
	void        SpecialAtk();
	void		PixelColUpdate();
	//===========================//		
	/*���ݽÿ� ����� �浹 �ڽ�(�ٰŸ�)*/
	void        CreateAtkBox();
	//===========================//	
	/*��ũ*/
	void	    SetPlayerLink(player* ply) { _ply = ply; }
};