//컴파일 하기 이전에 미리 한 번 메모리에 로드하는 곳
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

//	전처리기 조건문
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
#define WINSTARTX 400		//윈도우 시작좌표 X
#define WINSTARTY 50		//윈도우 시작좌표 Y
#define WINSIZEX 800		//윈도우 가로크기
#define WINSIZEY 600		//윈도우 세로크기
#define GAMESIZEX 6141		//실제 게임맵 가로사이즈
#define GAMESIZEY 1000		//실제 게임맵 세로사이즈
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