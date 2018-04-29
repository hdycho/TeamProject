#include "stdafx.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

HRESULT CameraManager::init()
{
	//����ũ�⸸�� ī�޶����
	camBuffer = IMAGEMANAGER->addImage("camBuffer", GAMESIZEX, GAMESIZEY);
	setX = 0;
	setY = 0;
	
	return S_OK;
}


void CameraManager::CamInit(CAMERASET camState, int x, int y, int w, int h, int speed)
{
	//���� �׷����ʿ��� ������ ī�޶�Ʈ
	//ȭ�鿡 ������ ũ�⸸ŭ �Ҵ�
	this->camState = camState;
	switch (camState)
	{
	case CENTER_CAMERA:
	{
		camRc = RectMakeCenter(x, y, w, h);
		camWidth = w;
		camHeight = h;
	}
	break;
	case RECTRANGE_CAMERA:
	{
		camRc = RectMakeCenter(x, y, w, h);
		camWidth = w;
		camHeight = h;

		subCamRc = RectMake(x, y, WINSIZEX, WINSIZEY);
		subCamWidth = WINSIZEX;
		subCamHeight = WINSIZEY;
	}
	break;
	case DYNAMIC_CAMERA:
	{
		camRc = RectMakeCenter(x, y, w, h);
		camWidth = w;
		camHeight = h;

		subCamRc = RectMake(x, y, WINSIZEX, WINSIZEY);
		subCamWidth = WINSIZEX;
		subCamHeight = WINSIZEY;

		camSpeed = speed;
	}
	break;
	}
}

void CameraManager::CamUpdate(RECT & rc, int LeftX, int rightX, int topY, int bottomY)
{
	//ī�޶� ���� ����,������,�Ʒ�,���� ���������� ���̻� �ö󰡸� �ȵȴ�

	//���� ���ڷ� ���޹��� rc�� ������ ��������

	switch (camState)
	{
	case CENTER_CAMERA:
	{
		if (GetCenterPos(rc).y + camHeight / 2 > bottomY || GetCenterPos(rc).y - camHeight / 2 < topY)
		{
			if (GetCenterPos(rc).y + camHeight / 2 > bottomY)
				setY = bottomY - camHeight / 2;
			else if (GetCenterPos(rc).y - camHeight / 2 < topY)
				setY = topY + camHeight / 2;
		}
		else
		{
			setY = GetCenterPos(rc).y;
		}
		if (GetCenterPos(rc).x - camWidth / 2 < LeftX || GetCenterPos(rc).x + camWidth / 2>rightX)
		{
			if (GetCenterPos(rc).x - camWidth / 2 < LeftX)
				setX = camWidth / 2;
			else if (GetCenterPos(rc).x + camWidth / 2>rightX)
				setX = rightX - camWidth / 2;
		}
		else
		{
			setX = GetCenterPos(rc).x;
		}
		camRc = RectMakeCenter(setX, setY, camWidth, camHeight);
	}
	break;
	case RECTRANGE_CAMERA:
	{
		//���޷�Ʈ�� ���ι����� ī�޶�Ʈ�� ������ ������
		if (rc.left < camRc.left || rc.right>camRc.right)
		{
			if (rc.left < camRc.left)
			{
				if (GetCenterPos(camRc).y < GetCenterPos(rc).y || GetCenterPos(camRc).y >= GetCenterPos(rc).y)
					setY = GetCenterPos(camRc).y;
				camRc = RectMakeCenter(GetCenterPos(rc).x + camWidth / 2 - (rc.right - rc.left) / 2, setY, camWidth, camHeight);
			}
			if (rc.right > camRc.right)
			{
				if (GetCenterPos(camRc).y < GetCenterPos(rc).y || GetCenterPos(camRc).y >= GetCenterPos(rc).y)
					setY = GetCenterPos(camRc).y;
				camRc = RectMakeCenter(GetCenterPos(rc).x - camWidth / 2 + (rc.right - rc.left) / 2, setY, camWidth, camHeight);
			}
		}
		//���޷�Ʈ�� ���ι����� ī�޶�Ʈ�� ������ ������
		if (rc.top<camRc.top || rc.bottom>camRc.bottom)
		{
			if (rc.top < camRc.top)
			{
				if (GetCenterPos(camRc).x < GetCenterPos(rc).x || GetCenterPos(camRc).x >= GetCenterPos(rc).x)
					setX = GetCenterPos(camRc).x;
				camRc = RectMakeCenter(setX, GetCenterPos(rc).y + camHeight / 2 - (rc.bottom - rc.top) / 2, camWidth, camHeight);
			}
			if (rc.bottom > camRc.bottom)
			{
				if (GetCenterPos(camRc).x < GetCenterPos(rc).x || GetCenterPos(camRc).x >= GetCenterPos(rc).x)
					setX = GetCenterPos(camRc).x;
				camRc = RectMakeCenter(setX, GetCenterPos(rc).y - camHeight / 2 + (rc.bottom - rc.top) / 2, camWidth, camHeight);
			}
		}

		//ī�޶� ��Ʈ�� �������� ū��Ʈ�� ������ش�
		if (GetCenterPos(camRc).x >= WINSIZEX / 2 - LeftX && GetCenterPos(camRc).x < rightX - WINSIZEX / 2)
		{
			static int resetY = 0;
			if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2 || GetCenterPos(camRc).y < topY + WINSIZEY / 2)
			{
				if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2)
				{
					resetY = bottomY - WINSIZEY / 2;
					subCamRc = RectMakeCenter(GetCenterPos(camRc).x, resetY, subCamWidth, subCamHeight);
				}
				else if (GetCenterPos(camRc).y < topY + WINSIZEY / 2)
				{
					resetY = topY + WINSIZEY / 2;
					subCamRc = RectMakeCenter(GetCenterPos(camRc).x, resetY, subCamWidth, subCamHeight);
				}
			}
			else
				subCamRc = RectMakeCenter(GetCenterPos(camRc).x, GetCenterPos(camRc).y, subCamWidth, subCamHeight);
		}
		else
		{
			if (GetCenterPos(camRc).x < WINSIZEX / 2 - LeftX)
			{
				static int resetY = 0;
				if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2)
				{
					resetY = bottomY - WINSIZEY / 2;
					subCamRc = RectMakeCenter(WINSIZEX / 2 - LeftX, resetY, subCamWidth, subCamHeight);
				}
				else if (GetCenterPos(camRc).y < topY + WINSIZEY / 2)
				{
					resetY = topY + WINSIZEY / 2;
					subCamRc = RectMakeCenter(WINSIZEX / 2 - LeftX, resetY, subCamWidth, subCamHeight);
				}
				else
				{
					subCamRc = RectMakeCenter(WINSIZEX / 2 - LeftX, GetCenterPos(camRc).y, subCamWidth, subCamHeight);
				}
			}
			else if (GetCenterPos(camRc).x >= rightX - WINSIZEX / 2)
			{
				static int resetY = 0;
				if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2)
				{
					resetY = bottomY - WINSIZEY / 2;
					subCamRc = RectMakeCenter(rightX - WINSIZEX / 2, resetY, subCamWidth, subCamHeight);
				}
				else if (GetCenterPos(camRc).y < topY + WINSIZEY / 2)
				{
					resetY = topY + WINSIZEY / 2;
					subCamRc = RectMakeCenter(rightX - WINSIZEX / 2, resetY, subCamWidth, subCamHeight);
				}
				else
				{
					subCamRc = RectMakeCenter(rightX - WINSIZEX / 2, GetCenterPos(camRc).y, subCamWidth, subCamHeight);
				}
			}
		}
	}
	break;
	case DYNAMIC_CAMERA:
	{
		//ī�޶�Ʈ�� �и��� �����ؾ���
		//ī�޶� ������ �������� �¿�������� ����
		
		//�����̴� ��Ʈ�� ī�޶�Ʈ �ȿ�������
		if (camRc.left<rc.left&&camRc.right>=rc.right&&camRc.top<rc.top&&camRc.bottom>rc.bottom)
		{
			if (GetCenterPos(rc).x + 5 < GetCenterPos(camRc).x)
			{
				camRc.left -= (camSpeed - (camSpeed-2));
				camRc.right -= (camSpeed - (camSpeed-2));
			}
			else if (GetCenterPos(rc).x - 5 > GetCenterPos(camRc).x)
			{
				camRc.left += (camSpeed - (camSpeed - 2));
				camRc.right += (camSpeed - (camSpeed - 2));
			}

			if (GetCenterPos(rc).y + 5 < GetCenterPos(camRc).y)
			{
				camRc.top -= (camSpeed - (camSpeed - 2));
				camRc.bottom -= (camSpeed - (camSpeed - 2));
			}
			else if (GetCenterPos(rc).y - 5 > GetCenterPos(camRc).y)
			{
				camRc.top += (camSpeed - (camSpeed - 2));
				camRc.bottom += (camSpeed - (camSpeed - 2));
			}
		}
		else
		{
			if (rc.left < camRc.left+10)
			{
				camRc.left -= camSpeed;
				camRc.right -= camSpeed;
			}
			if (rc.right > camRc.right - 10)
			{
				camRc.left += camSpeed;
				camRc.right += camSpeed;
			}
			if (rc.top < camRc.top + 10)
			{
				camRc.top -= camSpeed;
				camRc.bottom -= camSpeed;
			}
			if (rc.bottom > camRc.bottom - 10)
			{
				camRc.top += camSpeed;
				camRc.bottom += camSpeed;
			}
		}
		//ī�޶� ��Ʈ�� �������� ū��Ʈ�� ������ش�
		if (GetCenterPos(camRc).x >= WINSIZEX / 2 - LeftX && GetCenterPos(camRc).x < rightX - WINSIZEX / 2)
		{
			static int resetY = 0;
			if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2 || GetCenterPos(camRc).y < topY + WINSIZEY / 2)
			{
				if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2)
				{
					resetY = bottomY - WINSIZEY / 2;
					subCamRc = RectMakeCenter(GetCenterPos(camRc).x, resetY, subCamWidth, subCamHeight);
				}
				else if (GetCenterPos(camRc).y < topY + WINSIZEY / 2)
				{
					resetY = topY + WINSIZEY / 2;
					subCamRc = RectMakeCenter(GetCenterPos(camRc).x, resetY, subCamWidth, subCamHeight);
				}
			}
			else
				subCamRc = RectMakeCenter(GetCenterPos(camRc).x, GetCenterPos(camRc).y, subCamWidth, subCamHeight);
		}
		else
		{
			if (GetCenterPos(camRc).x < WINSIZEX / 2 - LeftX)
			{
				static int resetY = 0;
				if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2)
				{
					resetY = bottomY - WINSIZEY / 2;
					subCamRc = RectMakeCenter(WINSIZEX / 2 - LeftX, resetY, subCamWidth, subCamHeight);
				}
				else if (GetCenterPos(camRc).y < topY + WINSIZEY / 2)
				{
					resetY = topY + WINSIZEY / 2;
					subCamRc = RectMakeCenter(WINSIZEX / 2 - LeftX, resetY, subCamWidth, subCamHeight);
				}
				else
				{
					subCamRc = RectMakeCenter(WINSIZEX / 2 - LeftX, GetCenterPos(camRc).y, subCamWidth, subCamHeight);
				}
			}
			else if (GetCenterPos(camRc).x >= rightX - WINSIZEX / 2)
			{
				static int resetY = 0;
				if (GetCenterPos(camRc).y > bottomY - WINSIZEY / 2)
				{
					resetY = bottomY - WINSIZEY / 2;
					subCamRc = RectMakeCenter(rightX - WINSIZEX / 2, resetY, subCamWidth, subCamHeight);
				}
				else if (GetCenterPos(camRc).y < topY + WINSIZEY / 2)
				{
					resetY = topY + WINSIZEY / 2;
					subCamRc = RectMakeCenter(rightX - WINSIZEX / 2, resetY, subCamWidth, subCamHeight);
				}
				else
				{
					subCamRc = RectMakeCenter(rightX - WINSIZEX / 2, GetCenterPos(camRc).y, subCamWidth, subCamHeight);
				}
			}
		}
	}
	break;
	}
}

void CameraManager::CamRender(HDC hdc)
{
	switch (camState)
	{
	case CENTER_CAMERA:
	{
		camBuffer->render(hdc, 0, 0, camRc.left, camRc.top, camWidth, camHeight);
	}
	break;
	case RECTRANGE_CAMERA:
	case DYNAMIC_CAMERA:
	{
		camBuffer->render(hdc, 0, 0, subCamRc.left, subCamRc.top, subCamWidth, subCamHeight);
	}
	break;
	}
}

RECT CameraManager::getCamRc()
{
	if (camState == CENTER_CAMERA)
		return camRc;
	else
		return subCamRc;
}
