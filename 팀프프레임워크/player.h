#pragma once
#include "gameNode.h"
#include "PixelCol.h"
#include "Skill.h"

#define KNIGHTSPEED 4;

enum KNIGHTDIRECTION
{
	RIGHT_STAND,
	LEFT_STAND,
	RIGHT_RUN,
	LEFT_RUN,
	RIGHT_JUMP,
	LEFT_JUMP,
	RIGHT_ATTACK,
	LEFT_ATTACK,
	RIGHT_ATTACKUP,
	LEFT_ATTACKUP,

	RIGHT_SKILL1,
	LEFT_SKILL1,

	KNIGHT_SKILL2,
	KNIGHT_SPIN,
	KNIGHT_TORNADO,

	KNIGHT_CLIMB
};
struct KNIGHTPOSITION
{
	image* img;
	RECT rc;
	RECT playerColRect;
	float x, y;
	float angle;
};

class Skill;
class Store;
class PlayerUI;
class player : public gameNode
{
private:
	Skill * _skill;
	Store* _store;
	PlayerUI* _Ui;

	KNIGHTDIRECTION _knightDirection;
	KNIGHTPOSITION _knight;
		
	image* _run;
	image* _stand;
	image* _jump;
	image* _climb;
	image* _attack;
	image* _attackUp;

	// for Skill_1 (Q)
	image* _skill_1;
	image* _bulletSwordRight;
	image* _bulletSwordLeft;

	// for Skill_Heal (W)
	KNIGHTPOSITION _knightHeal;
	bool _isSkillHeal;
	bool _isAvailableHeal;

	// for Skill_2 (E)
	KNIGHTPOSITION _skill_2_Right;
	KNIGHTPOSITION _skill_2_Left;
	image* _spin;
	image* _tornado;
	bool _isSkill2;
	bool _isAvailable2;
	bool _skill2Rect;
	
	// for Jump
	float _jumpPower;
	float _gravity;
	bool _isJump;

	// for Attack
	KNIGHTPOSITION _attackRange;
	bool _isAttack;
	bool _isAttack2;		// 렉트 삭제용 변수

	// for HP/MP
	float _playerHP;
	float _playerMP;

	// for PixelCollision
	PixelCol*pCol;
	float _playerX, _playerY;
	bool _isCollision;

	int _speed, _speedDamaged;
	int _count, _index, _indexExtra, _indexHeal, _indexJump;
	int _countAttack; // attack speed
	int _countSkill;  // count used in skill
	int _countSkill2; // count used in Skill_2;
	int _countHeal;

	// ladder
	KNIGHTPOSITION _ladder;
	bool _isClimb;
	bool _climbFrame;

public:
	player();
	~player();

	int	_money;

	HRESULT init();
	void release();
	void update(HDC hdc);
	void render();

	void knightJump();
	void knightClimb();
	void knightAttack();

	void knightSkill_Heal();
	void knightSkill_2();
	void knightSkill_1();

	void knightDamaged(RECT rc);

	void PlayerCollision(HDC hdc);

	//image* getPlayerImage() {return }
	KNIGHTPOSITION&getKnightImage() { return _knight; }
	KNIGHTPOSITION&getAttackRc() { return _attackRange; }
	KNIGHTPOSITION&getSkill2Left() { return _skill_2_Left; }
	KNIGHTPOSITION&getSkill2Right() { return _skill_2_Right; }
	void setKnightPosition(KNIGHTPOSITION position) { _knight = position; }

	// Skill_2 (bool) get,set
	void setSkill2Bool(bool value) { _isAvailable2 = value; }
	bool getSkill2Bool() { return _isAvailable2; }
	// Skill_Heal (bool) get,set
	void setSkillHealBool(bool valueH) { _isAvailableHeal = valueH; }
	bool getSkillHealBool() { return _isAvailableHeal; }

	// Store과의 링크함수
	void setStoreAddress(Store* str) { _store = str; }
	inline void InitGravity() { _gravity = 0;_jumpPower = 0; }
	// UI와의 링크함수
	void setUIAddress(PlayerUI* ui) { _Ui = ui; }

	// player (money) get
	int&getMoney() { return _money; }

	inline float&GetHp() { return _playerHP; }
	inline float&GetMp() { return _playerMP; }
	inline PixelCol*getPcol() { return pCol; }
	void setIsAttack2(bool isAttack2) { _isAttack2 = isAttack2; }
};
