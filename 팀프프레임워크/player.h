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
	LEFT_ATTACKUP
};
struct KNIGHTPOSITION
{
	image* img;
	RECT rc;
};

class player : public gameNode
{
private:
	KNIGHTDIRECTION _knightDirection;
	KNIGHTPOSITION _knight;

	image* _run;
	image* _stand;
	image* _jump;
	image* _attack;
	image* _attackUp;

	PixelCol*pCol;
	float _playerX, _playerY;

	int _count, _index;
	int _countAttack; // attack speed

	bool _isCollision;

	// for Jump
	float _jumpPower;
	float _gravity;
	bool _isJump;

	// for Attack
	bool _isAttack;

	Skill* _skill;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	void knightJump();
	void knightAttack();

	void PlayerCollision();

	//image* getPlayerImage() {return }
	KNIGHTPOSITION getKnightImage() { return _knight; }
	void setKnightPosition(KNIGHTPOSITION position) { _knight = position; }
};
