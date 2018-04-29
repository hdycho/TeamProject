//������ �ϱ� ������ �̸� �� �� �޸𸮿� �ε��ϴ� ��
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

//	��ó���� ���ǹ�
#ifdef _DEBUG
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

using namespace std;

#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "txtData.h"
#include "iniDataManager.h"
#include "keyAniManager.h"
#include "utils.h"
#include "CameraManager.h"
#include "BulletManager.h"

using namespace NONA_UTIL;

//==============================
// ## Define ## 18.02.07 ##
//==============================

#define WINNAME (LPSTR)(TEXT("Nona API"))
#define WINSTARTX 400		//������ ������ǥ X
#define WINSTARTY 50		//������ ������ǥ Y
#define WINSIZEX 800		//������ ����ũ��
#define WINSIZEY 600		//������ ����ũ��
#define GAMESIZEX 6141		//���� ���Ӹ� ���λ�����
#define GAMESIZEY 1000		//���� ���Ӹ� ���λ�����
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define KEYMANAGER		keyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define KEYANIMANAGER	keyAniManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define CAM				CameraManager::getSingleton()	
#define BULLET			BulletManager::getSingleton()

//===================================
// ## Macro ## 2018.02.27 ##
//===================================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)= NULL;}}

//====================================
// ## 18.02.12 ## - Extern - ##
//====================================
extern POINT		_ptMouse;
extern HWND			_hWnd;
extern HINSTANCE	_hInstance;