#pragma once
#include "gameNode.h"
#include "PixelCol.h"
#include "Skill.h"

#define KNIGHTSPEED 4;
class Skill;

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
	KNIGHT_TORNADO
};
struct KNIGHTPOSITION
{
	image* img;
	RECT rc;
	float x, y;
};

class Store;
class player : public gameNode
{
private:
	KNIGHTDIRECTION _knightDirection;
	KNIGHTPOSITION _knight;

	// for Skill_2
	KNIGHTPOSITION _skill_2_Right;
	KNIGHTPOSITION _skill_2_Left;

	image* _run;
	image* _stand;
	image* _jump;
	image* _attack;
	image* _attackUp;

	image* _skill_1;
	image* _bulletSwordRight;
	image* _bulletSwordLeft;

	// for Skill_2
	image* _spin;
	image* _tornado;
	bool _isSkill2;
	bool _isAvailable2;

	PixelCol*pCol;
	float _playerX, _playerY;

	int _count, _index, _indexExtra;
	int _countAttack; // attack speed
	int _countSkill;  // count used in skill
	int _countSkill2; // count used in Skill_2;

	bool _isCollision;

	int _speed; // player speed

	// for Jump
	float _jumpPower;
	float _gravity;
	bool _isJump;

	// for Attack
	KNIGHTPOSITION _attackRange;
	bool _isAttack;

	Skill* _skill;
	Store* _store;

public:
	player();
	~player();

	int	_money;

	HRESULT init();
	void release();
	void update();
	void render();

	void knightJump();
	void knightAttack();

	void knightSkill_1();
	void knightSkill_2();

	void PlayerCollision();

	//image* getPlayerImage() {return }
	KNIGHTPOSITION getKnightImage() { return _knight; }
	void setKnightPosition(KNIGHTPOSITION position) { _knight = position; }

	// Skill_2 (bool) get,set
	void setSkill2Bool(bool value) { _isAvailable2 = value; }
	bool getSkill2Bool() { return _isAvailable2; }

	// Store과의 링크함수
	void setStoreAddress(Store* str) { _store = str; }
};
