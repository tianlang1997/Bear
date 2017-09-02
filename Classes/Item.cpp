#include "Item.h"
#include "define.h"
Item::Item(){
	Blood=0;
	Alive=DEAD;
}
Item::~Item(){}

Item* Item::CreateItems(int ItemType){
	auto item=new Item;
	int ItemNO=CCRANDOM_0_1()*Items_Count[ItemType];
	item->ItemNO=ItemNO;
	item->ItemType=ItemType;
	item->initWithSpriteFrameName(Items_Name[ItemType][ItemNO]);
	item->SetBlood(Items_Blood[ItemNO][ItemType]);
	item->SetAlive(ALIVE);
	item->scheduleOnce(schedule_selector(Item::Life), 20.0f);
	item->autorelease();
	return item;
}

Item* Item::CreateItems(int ItemType,int ItemNO){
	auto item=new Item;	
	item->ItemNO=ItemNO;
	item->ItemType=ItemType;
	item->initWithSpriteFrameName(Items_Name[ItemType][ItemNO]);
	item->SetBlood(Items_Blood[ItemNO][ItemType]);
	item->SetAlive(ALIVE);
	item->scheduleOnce(schedule_selector(Item::Life), 20.0f);
	item->autorelease();
	return item;
}

void Item::SetBlood(int Blood){
	this->Blood=Blood;
}
int Item::GetBlood()const{
	return Blood;
}
void Item::Life(float dt){
	Alive=DEAD;
}
void Item::SetAlive(bool state){
	Alive=state;
}
bool Item::GetAlive()const{
	return Alive;
}
void Item::Picked(){
	Alive=DEAD;
	unschedule(schedule_selector(Item::Life));
}
int Item::GetItemNO()const{
	return ItemNO;
}

int Item::GetItemTpye()const{
	return ItemType;
}