#ifndef _ITEM_
#define _ITEM_
#include "cocos2d.h"
USING_NS_CC;
class Item :public Sprite
{
public:
	Item();
	~Item();
	void SetBlood(int Blood);
	void SetAlive(bool state);
	int GetItemTpye()const;
	int GetItemNO()const;
	int GetBlood()const;
	bool GetAlive()const;
	void Picked();
	static Item* CreateItems(int ItemType);
	static Item* CreateItems(int ItemType,int ItemNo);
protected:
	int Blood;//Ѫ
	bool Alive;
	int ItemType;
	int ItemNO;
	void Life(float dt);
};


#endif