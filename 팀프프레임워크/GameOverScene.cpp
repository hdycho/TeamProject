#include "stdafx.h"
#include "GameOverScene.h"


GameOverScene::GameOverScene()
{
	IMAGEMANAGER->addFrameImage("���ӿ���ȭ��", PathFile("image", "���ӿ���ȭ��").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
}


GameOverScene::~GameOverScene()
{
}

HRESULT GameOverScene::init()
{
	//===============ī�޶� ����===============//
	CAM->CamInit(DYNAMIC_CAMERA, 0, 0, 300, 150, 4);
	//========================================//
	alpha = 0;
	fadeout= IMAGEMANAGER->findImage("����ȭ��");

	Loby = new button;
	Loby->Init(IMAGEMANAGER->findImage("��ư"), "LOBY", WINSIZEX / 2 - 240, WINSIZEY / 2 + 160, "�޸յձ�������");

	Quit = new button;
	Quit->Init(IMAGEMANAGER->findImage("��ư"), "QUIT", WINSIZEX / 2 - 240, WINSIZEY / 2 + 240, "�޸յձ�������");
	sceneChange = false;
	metaData = 2;
	LoadTime();
	return S_OK;
}

void GameOverScene::release()
{
}

void GameOverScene::update()
{
	Loby->Update(VK_LBUTTON, true);
	Quit->Update(VK_LBUTTON, true);
	if (Loby->IsClick())
	{
		sceneChange = true;
		metaData = 0;
	}

	if (Quit->IsClick())
	{
		sceneChange = true;
		metaData = 1;
	}

	if (sceneChange)
	{
		alpha += 3;
		
		if (alpha > 254)
		{
			if (metaData == 0)
			{
				SCENEMANAGER->changeScene("���۾�");
				alpha = 0;
			}
			else if (metaData == 1)
			{
				PostQuitMessage(0);
			}
		}
	}
}

void GameOverScene::render()
{
	IMAGEMANAGER->render("���ӿ���ȭ��", getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top);
	Quit->Render();
	Loby->Render();
	
	HFONT font, oldFont;
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "�޸յձ�������");
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	TextOut(getMemDC(), CAM->getCamRc().left+490, CAM->getCamRc().top+470, time.c_str(), time.size());
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	fadeout->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top,alpha);
}

void GameOverScene::LoadTime()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "�ӽ������.txt", "r");

	if (!fp)return;

	char temp[256];
	int minute;
	int second;
	while (true)
	{
		fscanf_s(fp,"%s" ,temp, sizeof(temp));
		if (string(temp).find("Time", 0) != string::npos)//������ã����
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", temp, sizeof(temp));
		if (temp[0] == '@')break;

		fscanf_s(fp, "%d%d", &minute, &second);
	}
	
	if (minute < 10)
	{
		if (second < 10)
		{
			time = '0' + to_string(minute)+':' + '0' + to_string(second);
		}
		else
		{
			time = '0' + to_string(minute) + ':' + to_string(second);
		}
	}
	else
	{
		if (second < 10)
		{
			time = to_string(minute) + ':' + '0' + to_string(second);
		}
		else
		{
			time = to_string(minute) + ':' + to_string(second);
		}
	}
}
