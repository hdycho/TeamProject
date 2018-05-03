#include "stdafx.h"
#include "ItemManager.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init()
{
	IMAGEMANAGER->addImage("tomato", "./image/tomato.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("banana", "./image/banana.bmp", 30, 30, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("gold", "./image/gold.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("AniGold", "./image/AniGold.bmp", 210, 30, 7, 1, true, RGB(255, 0, 255));

	index = 0;
	LoadItem();
	//==============================//
	//Item* tomato1 = new Item;
	//tomato1->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 1556, 300);
	//tomato1->GetShowState() = true;
	//_vMapItem.push_back(tomato1);

	//Item* tomato2 = new Item;
	//tomato2->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 3260, 225);
	//tomato2->GetShowState() = true;
	//_vMapItem.push_back(tomato2);

	//Item* tomato3 = new Item;
	//tomato3->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 6592, 652);
	//tomato3->GetShowState() = true;
	//_vMapItem.push_back(tomato3);

	//Item* tomato4 = new Item;
	//tomato4->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 7950, 650);
	//tomato4->GetShowState() = true;
	//_vMapItem.push_back(tomato4);

	//Item* tomato5 = new Item;
	//tomato5->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 8390, 865);
	//tomato5->GetShowState() = true;
	//_vMapItem.push_back(tomato5);

	//Item* tomato6 = new Item;
	//tomato6->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 9010, 795);
	//tomato6->GetShowState() = true;
	//_vMapItem.push_back(tomato6);

	//Item* tomato7 = new Item;
	//tomato7->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 10720, 438);
	//tomato7->GetShowState() = true;
	//_vMapItem.push_back(tomato7);

	//Item* tomato8 = new Item;
	//tomato8->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 10870, 865);
	//tomato8->GetShowState() = true;
	//_vMapItem.push_back(tomato8);

	//Item* tomato9 = new Item;
	//tomato9->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 13340, 370);
	//tomato9->GetShowState() = true;
	//_vMapItem.push_back(tomato9);

	//Item* tomato10 = new Item;
	//tomato10->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, 13940, 370);
	//tomato10->GetShowState() = true;
	//_vMapItem.push_back(tomato10);

	////==============================//

	//Item* banana1 = new Item;
	//banana1->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 1972, 368);
	//banana1->GetShowState() = true;
	//_vMapItem.push_back(banana1);

	//Item* banana2 = new Item;
	//banana2->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 2452, 440);
	//banana2->GetShowState() = true;
	//_vMapItem.push_back(banana2);

	//Item* banana3 = new Item;
	//banana3->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 4896, 652);
	//banana3->GetShowState() = true;
	//_vMapItem.push_back(banana3);

	//Item* banana4 = new Item;
	//banana4->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 6292, 832);
	//banana4->GetShowState() = true;
	//_vMapItem.push_back(banana4);

	//Item* banana5 = new Item;
	//banana5->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 6622, 652);
	//banana5->GetShowState() = true;
	//_vMapItem.push_back(banana5);

	//Item* banana6 = new Item;
	//banana6->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 7840, 650);
	//banana6->GetShowState() = true;
	//_vMapItem.push_back(banana6);

	//Item* banana7 = new Item;
	//banana7->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 7340, 935);
	//banana7->GetShowState() = true;
	//_vMapItem.push_back(banana7);

	//Item* banana8 = new Item;
	//banana8->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 9070, 795);
	//banana8->GetShowState() = true;
	//_vMapItem.push_back(banana8);

	//Item* banana9 = new Item;
	//banana9->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 10990, 438);
	//banana9->GetShowState() = true;
	//_vMapItem.push_back(banana9);

	//Item* banana10 = new Item;
	//banana10->init(IMAGEMANAGER->findImage("banana"), POTION_MP, 13390, 370);
	//banana10->GetShowState() = true;
	//_vMapItem.push_back(banana10);

	for (int i = 0; i < 30; i++)
	{
		Item* gold = new Item; 
			gold->init(IMAGEMANAGER->findImage("AniGold"), GOLD_ITEM, 0, 0);
		gold->GetShowState() = false;
		_vGold.push_back(gold);
	}

	return S_OK;
}

void ItemManager::release()
{

}

void ItemManager::update()
{
	for (int i = 0; i < _vGold.size(); ++i)
	{
		if (_vGold[i]->GetShowState())
		{
			_vGold[i]->update();
		}
	}
	GroundCollision();
}

void ItemManager::render()
{
	for (int i = 0; i < _vMapItem.size(); ++i)
	{
		if (_vMapItem[i]->GetShowState())
		{
			_vMapItem[i]->render();
		}
	}

	for (int i = 0; i < _vGold.size(); ++i)
	{
		if (_vGold[i]->GetShowState())
		{
			_vGold[i]->render();
			if (!_vGold[i]->GetCollision())
			{
				_vGold[i]->GetRect().top -= GoldUp[i];
				_vGold[i]->GetRect().bottom -= GoldUp[i];
				GoldUp[i] -= GoldDown[i];
			}
		}
	}
}

void ItemManager::LoadItem()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "오브젝트데이터.txt", "r");

	if (!fp)return;
	
	char name[256];
	int x, y;
	
	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (string(name).find("PosY", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", &name, sizeof(name));
		if (name[0] == '@')break;
		fscanf_s(fp, "%d%d", &x, &y);
		
		if (strcmp(name,"토마토")==0) 
		{
			Item* tomato = new Item;
			tomato->init(IMAGEMANAGER->findImage("tomato"), POTION_HP, x, y);
			tomato->GetShowState() = true;
			_vMapItem.push_back(tomato);
		}
		else if (strcmp(name, "바나나") == 0)
		{
			Item* banana = new Item;
			banana->init(IMAGEMANAGER->findImage("banana"), POTION_MP, x, y);
			banana->GetShowState() = true;
			_vMapItem.push_back(banana);
		}
	}
	fclose(fp);
}

void ItemManager::DropGold(int x, int y, int goldUp, int goldDown)
{
	GoldUp[index] = goldUp;
	GoldDown[index] = goldDown;
	_vGold[index]->GetRect() = RectMakeCenter(x, y, 30, 30);
	_vGold[index]->GetShowState() = true;
	_vGold[index]->GetCollision() = false;
	index++;

	if (index > _vGold.size() - 1)
	{
		index = 0;
	}
}

void ItemManager::GroundCollision()
{
	for (int i = 0; i < _vGold.size(); i++)
	{
		if (_vGold[i]->GetCollision())
		{
			GoldUp[i] = 0;
			GoldDown[i] = 0;
		}
	}
}
