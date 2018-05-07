#include "stdafx.h"
#include "ObstacleManager.h"


ObstacleManager::ObstacleManager()
{
}


ObstacleManager::~ObstacleManager()
{
}

HRESULT ObstacleManager::init()
{
	LoadObstacle();
	return S_OK;
}

void ObstacleManager::render()
{
	for (int i = 0; i < obsVec.size(); i++)
	{
		if (obsVec[i]->GetShowState())
			obsVec[i]->render();
	}
}

void ObstacleManager::update()
{
	for (int i = 0; i < obsVec.size(); i++)
	{
		RECT temp;
		if (!IntersectRect(&temp, &CAM->getCamRc(), &obsVec[i]->getRect()))continue;
		if (obsVec[i]->GetShowState())
		{
			obsVec[i]->update();
		}
	}
}

void ObstacleManager::release()
{
}

void ObstacleManager::LoadObstacle()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "������Ʈ������.txt", "r");

	if (!fp)return;

	char name[256];
	int x, y;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (string(name).find("PosY", 0) != string::npos)
			break;
		//���ڿ��� 0��°�ε������� PosY���� Ž�����ϴµ� ã���� �극��ũ
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (name[0] == '@')break;
		fscanf_s(fp, "%d%d", &x, &y);

		if (strcmp(name, "����") == 0)
		{
			Obstacle* wood = new Wood;
			wood->init(x, y, "������ֹ�");
			wood->GetShowState() = true;
			obsVec.push_back(wood);
		}
		else if (strcmp(name, "��") == 0)
		{
			Obstacle* iron = new Iron;
			iron->init(x, y, "����ֹ�");
			iron->GetShowState() = true;
			obsVec.push_back(iron);
		}
		else if (strcmp(name, "��ź") == 0)
		{
			Obstacle* bomb = new Bomb;
			bomb->init(x, y, "��ź��ֹ�");
			bomb->GetShowState() = true;
			obsVec.push_back(bomb);
		}
	}
	fclose(fp);
}
