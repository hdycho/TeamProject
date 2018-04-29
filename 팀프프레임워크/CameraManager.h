#pragma once
#include "singletonBase.h"

enum CAMERASET
{
	CENTER_CAMERA,		//	ī�޶� �߽ɱ���
	RECTRANGE_CAMERA,	//	ī�޶� ��Ʈ���� ����
	DYNAMIC_CAMERA		//	�ɸ��� �̵��Ҷ� �и��� ī�޶�
};


class CameraManager :public singletonBase<CameraManager>
{
private:
	image * camBuffer;		//	ī�޶�DC����

	RECT camRc;				//	ī�޶� RECT
	int camWidth;			//	ī�޶� �ʺ�
	int camHeight;			//	ī�޶� ����

	RECT subCamRc;			//	������ ī�޶� RECT
	int subCamWidth;		//	������ ī�޶� �ʺ�
	int subCamHeight;		//	������ ī�޶� ����

	int setX, setY;			//	ī�޶� ������ġ	
	int camSpeed;

	CAMERASET	camState;	//	ī�޶� ����
public:
	CameraManager();
	~CameraManager();

	HRESULT init();

	//�ʱ� ī�޶���ġ,ī�޶� ��Ʈ �ʱ�ȭ
	void CamInit(CAMERASET camState, int x, int y, int w, int h, int speed);

	//ī�޶�Ʈ�� ����������� �̵���Ű�°�
	void CamUpdate(RECT&rc, int LeftX, int rightX, int topY, int bottomY);

	//ī�޶���ۿ� �׷����� ���� ���ۿ��׸��� �Լ�
	void CamRender(HDC hdc);

	inline image*getCamBuffer() { return camBuffer; }
	inline RECT&getViewRc() { return camRc; }
	RECT getCamRc();
};

