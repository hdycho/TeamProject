#pragma once
#include "singletonBase.h"
#include "PixelCol.h"
#include <vector>
#include <map>

struct Bullet
{
	RECT		rc;				//�Ѿ� �浹�ڽ�
	image*		img;			//�Ѿ� �̹���
	animation*	anim;			//�Ѿ� ���ϸ��̼�
	string		bulletName;		//�Ѿ� �̸�
	PixelCol*	pcol;

	int			speed;			//�Ѿ� ���ǵ�

	float		x, y;			//�Ѿ� ������
	float		initX, initY;	//�Ѿ� ����������
	float		gravity;		//�Ѿ� �߷�
	float		addGravity;		//�������� �Ѿ� �߷�
	float		angle;			//�Ѿ� ����

	bool		isShot;			//�Ѿ� �߻翩��
	bool		isAnimation;	//���ϸ��̼��� �ִ� �Ѿ����� ����
	bool		useCollision;	//�浹����ϴ��� ����
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
	bulletMap bMap;			//	�Ѿ˸�
	bulletIdxMap bIdxMap;	//	�Ѿ��ε�����
public:
	BulletManager();
	~BulletManager();

	//�Ѿ� �����Լ�
	void BulletSetting(string bulletName,image*img, int bulletNum, bool isAnim = false,int animSpeed=60);
	
	//�Ѿ� ������Ʈ �Լ�
	void BulletUpdate();

	//�Ѿ� �����Լ�
	void BulletRender(HDC hdc);

	//�Ѿ� �߻��Լ�
	void Shot(string bulletName, float x, float y, float angle, float gravity, int speed);

	//�Ѿ� �ı��Լ�
	void Destroy(string bulletName,int bulletIdx);

	//�Ѿ��� �ٴڰ� �浹�ߴ��� ����
	void UseCollision(string bulletName,int proveX,int proveY);
	bool IsCollision(string bulletName,int*bulletPosX,int*bulletPosY,bool isMapCollision, HDC hdc,RECT rc);

	//�Ѿ� ������
	inline bulletVec&GetBulletVec(string bulletName) {
		return bMap.find(bulletName)->second;
	}
};

