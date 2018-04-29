#pragma once
#include "singletonBase.h"

enum CAMERASET
{
	CENTER_CAMERA,		//	카메라 중심기준
	RECTRANGE_CAMERA,	//	카메라 렉트범위 기준
	DYNAMIC_CAMERA		//	케릭터 이동할때 밀리는 카메라
};


class CameraManager :public singletonBase<CameraManager>
{
private:
	image * camBuffer;		//	카메라DC영역

	RECT camRc;				//	카메라 RECT
	int camWidth;			//	카메라 너비
	int camHeight;			//	카메라 높이

	RECT subCamRc;			//	여분의 카메라 RECT
	int subCamWidth;		//	여분의 카메라 너비
	int subCamHeight;		//	여분의 카메라 높이

	int setX, setY;			//	카메라 셋팅위치	
	int camSpeed;

	CAMERASET	camState;	//	카메라 종류
public:
	CameraManager();
	~CameraManager();

	HRESULT init();

	//초기 카메라위치,카메라 렉트 초기화
	void CamInit(CAMERASET camState, int x, int y, int w, int h, int speed);

	//카메라렉트가 기준점을잡고 이동시키는것
	void CamUpdate(RECT&rc, int LeftX, int rightX, int topY, int bottomY);

	//카메라버퍼에 그려진걸 실제 버퍼에그리는 함수
	void CamRender(HDC hdc);

	inline image*getCamBuffer() { return camBuffer; }
	inline RECT&getViewRc() { return camRc; }
	RECT getCamRc();
};

