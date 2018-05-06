#include "stdafx.h"
#include "StartScene.h"

StartScene::StartScene()
{
	IMAGEMANAGER->addFrameImage("����ȭ��", PathFile("image", "����ȭ��").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȭ��", PathFile("image", "����ȭ��").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ư", PathFile("image", "��ư").c_str(), 250, 121, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", PathFile("image", "������").c_str(), 400, 500, 1, 1, true, RGB(255, 0, 255));
	isonce = false;
}


StartScene::~StartScene()
{
}

HRESULT StartScene::init()
{
	//===============ī�޶� ����===============//
	CAM->CamInit(DYNAMIC_CAMERA, 0, 0, 300, 150, 4);
	//========================================//

	start = new button;
	start->Init(IMAGEMANAGER->findImage("��ư"), "START", WINSIZEX / 2 + 200, WINSIZEY / 2 + 50, "�޸յձ�������");

	edit = new button;
	edit->Init(IMAGEMANAGER->findImage("��ư"), "EDIT", WINSIZEX / 2 + 200, WINSIZEY / 2 + 150, "�޸յձ�������");

	score = new button;
	score->Init(IMAGEMANAGER->findImage("��ư"), "SCORE", WINSIZEX / 2 + 200, WINSIZEY / 2 + 250, "�޸յձ�������");

	fadeout = IMAGEMANAGER->findImage("����ȭ��");
	alpha = 0;


	LoadAllScore();	//���� ��ü������ �ε��ϰ�
	LoadScore(); // �׵ڿ� ���ο���� �߰�
				 //�׸��� �ӽõ����� ��������Ѵ�
	remove("�ӽ������.txt");
	
	return S_OK;
}

void StartScene::release()
{
	SaveScore();
	scoreVec.clear();
	isonce = false;
}

void StartScene::update()
{
	ScoreUpdate();
	start->Update(VK_LBUTTON, true);
	edit->Update(VK_LBUTTON, true);
	score->Update(VK_LBUTTON, true);
	if (start->IsClick())
	{
		alpha += 4;
		if (alpha>254)
		{
			SCENEMANAGER->changeScene("���Ӿ�");
			alpha = 0;
		}
	}

	if (edit->IsClick())
	{
		alpha += 4;
		if (alpha>254)
		{
			SCENEMANAGER->changeScene("������");
			alpha = 0;
		}
	}

	static bool scoreShow = false;

	if (score->IsClick())
	{
		scoreShow = true;
		alpha = 100;
	}

	else if (!score->IsClick() && scoreShow)
	{
		scoreShow = false;
		alpha = 0;
	}

}

void StartScene::render()
{
	IMAGEMANAGER->findImage("����ȭ��")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
	start->Render();
	edit->Render();
	score->Render();
	fadeout->alphaRender(getMemDC(), 0, 0, alpha);
	if (score->IsClick())
	{
		IMAGEMANAGER->findImage("������")->render(getMemDC(), CAM->getCamRc().left + 200, CAM->getCamRc().top + 50, CAM->getCamRc().left, CAM->getCamRc().top, 400, 500);
		ScoreShow();
	}
}

void StartScene::ScoreUpdate()
{
	for (int i = 0; i < scoreVec.size(); i++)
	{
		scoreVec[i].time = scoreVec[i].min * 60 + scoreVec[i].sec;
	}


	for (int i = 0; i < scoreVec.size(); i++)
	{
		for (int j = 0; j < (scoreVec.size() - (i + 1)); j++)
		{
			if (scoreVec[j].time > scoreVec[j + 1].time)
			{
				ScoreData temp = scoreVec[j];
				scoreVec[j] = scoreVec[j + 1];
				scoreVec[j + 1] = temp;
			}
		}
	}
}

void StartScene::ScoreShow()
{
	char temp[256];

	HFONT font, oldFont;
	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "�޸յձ�������");
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	for (int i = 0; i < scoreVec.size(); i++)
	{
		if (scoreVec[i].min < 10)
		{
			if (scoreVec[i].sec < 10)
			{
				sprintf(temp, "[%dst].0%d:0%d", i + 1, scoreVec[i].min, scoreVec[i].sec);

			}
			else
			{
				sprintf(temp, "[%dst].0%d:%d", i + 1, scoreVec[i].min, scoreVec[i].sec);
			}
		}
		else
		{
			if (scoreVec[i].sec < 10)
			{
				sprintf(temp, "[%dst].%d:0%d", i + 1, scoreVec[i].min, scoreVec[i].sec);
			}
			else
			{
				sprintf(temp, "[%dst].%d:%d", i + 1, scoreVec[i].min, scoreVec[i].sec);
			}
		}
		TextOut(getMemDC(), CAM->getCamRc().left + 320, CAM->getCamRc().top + 200 + i * 50, temp, strlen(temp));
	}
}

void StartScene::LoadScore()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "�ӽ������.txt", "r");

	if (!fp)return;

	char name[256];

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (string(name).find("Time", 0) != string::npos)
			break;
	}

	while (true)
	{
		ScoreData sd;
		fscanf_s(fp, "%s", name, sizeof(name));
		if (name[0] == '@')break;

		fscanf_s(fp, "%d%d", &sd.min, &sd.sec);

		if (strcmp(name, "CLEAR") == 0)
		{
			scoreVec.push_back(sd);
		}
	}
	fclose(fp);
}

void StartScene::LoadAllScore()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "��ü�����.txt", "r");
	if (!fp)return;

	char name[256];

	while (true)
	{
		ScoreData sd;
		fscanf_s(fp, "%s", name, sizeof(name));
		if (name[0] == '@')break;
		fscanf_s(fp, "%d%d", &sd.min, &sd.sec);
		scoreVec.push_back(sd);
	}
	fclose(fp);
}


void StartScene::SaveScore()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "��ü�����.txt", "w+t");

	string temp;
	string name = "name";
	char end = '@';
	for (int i = 0; i < scoreVec.size(); i++)
	{
		temp = name + '\t' + to_string(scoreVec[i].min) + '\t' + to_string(scoreVec[i].sec) + '\n';
		fwrite(temp.c_str(), temp.size(), 1, fp);
	}
	fwrite(&end, sizeof(end), 1, fp);
	fclose(fp);
}
