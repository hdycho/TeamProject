#pragma once
#include "singletonBase.h"
#include "PixelCol.h"
#include <vector>
#include <map>

struct Bullet
{
	RECT		rc;				//총알 충돌박스
	image*		img;			//총알 이미지
	animation*	anim;			//총알 에니메이션
	string		bulletName;		//총알 이름
	PixelCol*	pcol;

	int			speed;			//총알 스피드

	float		x, y;			//총알 포지션
	float		initX, initY;	//총알 시작포지션
	float		gravity;		//총알 중력
	float		addGravity;		//더해지는 총알 중력
	float		angle;			//총알 각도

	bool		isShot;			//총알 발사여부
	bool		isAnimation;	//에니메이션이 있는 총알인지 여부
	bool		useCollision;	//충돌사용하는지 여부
};
class BulletManager:public singletonBase<BulletManager>
{
private:
	typedef vector<Bullet*>				bulletVec;
	typedef vector<Bullet*>::iterator	bulletIter;
	
	typedef map<string, bulletVec>					bulletMap;
	typedef map<string, bulletVec>::iterator		bulletMapIter;

	typedef map<string, int>				bulletIdxMap;
	typedef map<string, int>::iterator		bulletIdxMapIter;
private:
	bulletMap bMap;			//	총알맵
	bulletIdxMap bIdxMap;	//	총알인덱스맵
public:
	BulletManager();
	~BulletManager();

	//총알 삽입함수
	void BulletSetting(string bulletName,image*img, int bulletNum, bool isAnim = false,int animSpeed=60);
	
	//총알 업데이트 함수
	void BulletUpdate();

	//총알 랜더함수
	void BulletRender(HDC hdc);

	//총알 발사함수
	void Shot(string bulletName, float x, float y, float angle, float gravity, int speed);

	//총알 파괴함수
	void Destroy(string bulletName,int bulletIdx);

	//총알이 바닥과 충돌했는지 여부
	void UseCollision(string bulletName,int proveX,int proveY);
	bool IsCollision(string bulletName,int*bulletPosX,int*bulletPosY,bool isMapCollision, HDC hdc,RECT rc);

	//총알 접근자
	inline bulletVec&GetBulletVec(string bulletName) {
		return bMap.find(bulletName)->second;
	}
};

