#include "ForestFightScene.h"
#include "define.h"
#include "LakeFightScene.h"
USING_NS_CC;
Scene* ForestFight::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ForestFight::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ForestFight::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    GameModel=UserDefault::getInstance()->getIntegerForKey("GameModel",0);//游戏模式（困难度）

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CZOrder=100;//控件深度
	Enemy_Count=0;
	AliveRole=new std::vector<Role*>;
	AliveItem=new std::vector<Item*>;
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(ForestFight::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ForestFight::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ForestFight::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
	//背景
	auto Background=Sprite::createWithSpriteFrameName("ForestFight_Wall.png");
	Background->setAnchorPoint(Vec2(0,1));
	Background->setPosition(Vec2(origin.x,origin.y+visibleSize.height));
	this->addChild(Background,1);



	Moveable_Begin = Point(origin);
	Moveable_End = Point(origin.x+Background->getContentSize().width,origin.y+Background->getContentSize().height*0.5);
	//控制按钮
	UpButton=Sprite::createWithSpriteFrameName("direction.png");
	UpButton->setRotation(-90);
	DownButton=Sprite::createWithSpriteFrameName("direction.png");
	DownButton->setRotation(90);
	LeftButton=Sprite::createWithSpriteFrameName("direction.png");
	LeftButton->setFlippedX(true);
	RightButton=Sprite::createWithSpriteFrameName("direction.png");
	auto BasePositin=Point(120,120);
	auto Fixed=70;
	UpButton->setPosition(Vec2(BasePositin.x,BasePositin.y+Fixed));
	DownButton->setPosition(Vec2(BasePositin.x,BasePositin.y-Fixed));
	LeftButton->setPosition(Vec2(BasePositin.x-Fixed,BasePositin.y));
	RightButton->setPosition(Vec2(BasePositin.x+Fixed,BasePositin.y));
	this->addChild(UpButton,CZOrder);
	this->addChild(DownButton,CZOrder);
	this->addChild(LeftButton,CZOrder);
	this->addChild(RightButton,CZOrder);

	//手攻击按钮
	HandBeatButton=Sprite::createWithSpriteFrameName("handbeat.png");
	HandBeatButton->setPosition(Vec2(origin.x+visibleSize.width-100,BasePositin.y+Fixed));
	this->addChild(HandBeatButton,CZOrder);
	//脚攻击
	FootBeatButton=Sprite::createWithSpriteFrameName("footbeat.png");
	FootBeatButton->setPosition(Vec2(origin.x+visibleSize.width-100,BasePositin.y-Fixed));
	this->addChild(FootBeatButton,CZOrder);

	//主角
	HeroSprite=Hero::create();
	HeroSprite->SetRegion(Moveable_Begin,Moveable_End);	
	AliveRole->push_back(HeroSprite);
	this->addChild(HeroSprite,10);
	//菜单按钮
	MenuShowButton=Sprite::create();
	MenuShowButton->setContentSize(visibleSize*0.4f);
	MenuShowButton->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	this->addChild(MenuShowButton,CZOrder);
	menulayer=MenuOptionLayer::create();
	this->addChild(menulayer,CZOrder);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    scheduleUpdate();
    return true;
}

ForestFight::~ForestFight(){
	AliveItem->clear();
	AliveRole->clear();
	this->cleanup();
	delete AliveRole;
	delete AliveItem;
	_eventDispatcher->removeEventListener(listener);
}

bool ForestFight::onTouchBegan(Touch* touch,Event *event)
{
	if(HandBeatButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("HandBeat0");	
		CurrentState=RoleState::HANDBEAT;
		return true;
	}
	if(FootBeatButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("HandBeat0");	
		CurrentState=RoleState::FOOTBEAT;
		return true;
	}
	if(UpButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("Controler");
		CurrentState=RoleState::MOVEUP;
		return true;
	}
	if(DownButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("Controler");
		CurrentState=RoleState::MOVEDOWN;
		return true;
	}
	if(LeftButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("Controler");
		CurrentState=RoleState::MOVELEFT;
		return true;
	}
	if(RightButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("Controler");
		CurrentState=RoleState::MOVERIGHT;
		return true;
	}
	if(MenuShowButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("Controler");
		CurrentState=RoleState::SHOWMENU;
		return true;
	}
	return false;
}

void ForestFight::onTouchMoved(Touch* touch,Event *event)
{

}

void ForestFight::onTouchEnded(Touch* touch,Event *eventt)
{
	if (CurrentState==RoleState::MOVEUP)
	{
		HeroSprite->MoveUp();
	}

	if (CurrentState==RoleState::MOVEDOWN)
	{
		HeroSprite->MoveDown();
	}

	if (CurrentState==RoleState::MOVELEFT)
	{
		HeroSprite->MoveLeft();
	}

	if (CurrentState==RoleState::MOVERIGHT)
	{
		HeroSprite->MoveRight();
	}
	if (CurrentState==RoleState::HANDBEAT)
	{
		HeroSprite->HandAttack();
	}
	if (CurrentState==RoleState::FOOTBEAT)
	{
		HeroSprite->FootAttack();
	}
	if(CurrentState==RoleState::SHOWMENU){
		ShowMenu();
	}


}
void ForestFight::update(float dt){
	GenerateEnemy();
	UpdateHeroPosition();
	DetecCover();
	DetectCollision();
	DetectAttack();
	DetectDead();
}
void ForestFight::GenerateEnemy(){
	if (Enemy_Count>GAME_MODEL[GameModel][ENEMY_TOTAL])
	{
		return;
	}	
	int EnemyNum=GAME_MODEL[GameModel][ENEMY_ACTIVE]-AliveRole->size()+1;	
	for (int i=0;i<EnemyNum;i++)
	{
		auto EnemyBear=Enemy::create();
		EnemyBear->SetRegion(Moveable_Begin,Moveable_End);
		EnemyBear->SetGameModel(GameModel);
		EnemyBear->Run();
		this->addChild(EnemyBear,10);
		AliveRole->push_back(EnemyBear);
	}
	Enemy_Count+=EnemyNum;
}
void ForestFight::DetecCover(){	
	QuickSort(AliveRole,0,AliveRole->size()-1);
	auto ZOrder=1;
	for (auto itor=AliveRole->begin();itor!=AliveRole->end();itor++)
	{
		(*itor)->setLocalZOrder(ZOrder++);
	}
}

void ForestFight::QuickSort(std::vector<Role*>* vData,int Left,int Right){
	if (Left>Right)
	{
		return;
	}
	auto temp=(*vData)[Left]->GetEntityDepth();

	int l=Left;
	int r=Right;
	Role* TempRole;
	while (l!=r)
	{
		while ((*vData)[r]->GetEntityDepth()<temp && l<r)
		{
			r--;
		}
		while ((*vData)[r]->GetEntityDepth()>=temp && l<r)
		{
			l++;
		}
		if(l<r) 
		{ 
			auto TempRole=(*vData)[l]; 
			(*vData)[l]=(*vData)[r]; 
			(*vData)[r]=TempRole; 
		} 
	}
	TempRole=(*vData)[Left];
	(*vData)[Left]=(*vData)[l];
	(*vData)[l]=TempRole;

	QuickSort(vData,Left,l-1);
	QuickSort(vData,l+1,Right);
}
void ForestFight::DetectAttack(){
	if (HeroSprite->GetIsAttack())
	{
		for (auto itor=AliveRole->begin();itor!=AliveRole->end();itor++)
		{
			if (HeroSprite==(*itor))
			{
				continue;
			}			
			CheckAttack(*HeroSprite,*(*itor));
		}		
	}	
	std::vector<Role*>* FightingRole=new std::vector<Role*>;
	for (auto itor=AliveRole->begin();itor!=AliveRole->end();itor++)
	{
		if ((*itor)->GetIsAttack() && (*itor)!=HeroSprite)
		{
			FightingRole->push_back((*itor));
		}
	}
	if (FightingRole->size()>0)
	{
		for (auto itor=FightingRole->begin();itor!=FightingRole->end();itor++)
		{
			CheckAttack(*(*itor),*HeroSprite);
		}
	}	
	FightingRole->clear();
	delete FightingRole;
}
void ForestFight::CheckAttack(Role& Attacker,Role& Victim){
	int Blood=0;
	auto AttackerRect=Attacker.GetEntity()->getBoundingBox();
	auto VictimRect=Victim.GetEntity()->getBoundingBox();	
	
	auto ARect = Rect(AttackerRect.origin.x-AttackerRect.size.width*0.3, AttackerRect.origin.y,AttackerRect.size.width, AttackerRect.size.height*0.1);
	auto VRect = Rect(VictimRect.origin.x-VictimRect.size.width*0.2, VictimRect.origin.y,VictimRect.size.width, VictimRect.size.height*0.1);

	if (!ARect.intersectsRect(VRect))
	{
		return;
	}

	Rect rect_A;
	Rect rect_B;
	if (Attacker.GetDirection()==TURNLEFT)
	{
		rect_A = Rect(AttackerRect.origin.x, AttackerRect.origin.y,AttackerRect.size.width*0.5, AttackerRect.size.height);
		rect_B = Rect(VictimRect.origin.x+VictimRect.size.width*0.08, VictimRect.origin.y,VictimRect.size.width*0.84, VictimRect.size.height);
	}else
	{
		rect_A = Rect(AttackerRect.origin.x+AttackerRect.size.width*0.5, AttackerRect.origin.y,AttackerRect.size.width*0.5, AttackerRect.size.height);
		rect_B = Rect(VictimRect.origin.x+VictimRect.size.width*0.08, VictimRect.origin.y,VictimRect.size.width*0.84, VictimRect.size.height);
	}
	
	if (rect_A.intersectsRect(rect_B))
	{
		auto A_Direction=TURNLEFT;
		if(Attacker.getPosition().x-Victim.getPosition().x>0){
			A_Direction=TURNRIGHT;
		}
		Victim.BeAttacked(A_Direction,Attacker.GetCurrentState(),nullptr);
		//Blood=1;
		//Victim.SubBlood(Blood);
	}
}
void ForestFight::DetectCollision(){
	//for (auto itor=AliveRole->begin();itor!=AliveRole->end();itor++)
	//{
	//	for (auto itor1=AliveRole->begin();itor1!=AliveRole->end();itor1++)
	//	{
	//		if (itor!=itor1 && (*itor)->GetEntity()->getBoundingBox().intersectsRect((*itor1)->GetEntity()->getBoundingBox()))
	//		{	
	//			auto AttackerRect=(*itor)->GetEntity()->getBoundingBox();
	//			auto VictimRect=(*itor1)->GetEntity()->getBoundingBox();
	//			if (CheckCollision(AttackerRect,VictimRect))
	//			{
	//				(*itor)->StopMoving();
	//				(*itor1)->StopMoving();
	//			}			
	//		}			
	//	}
	//}
	auto BearRect=HeroSprite->GetEntity()->getBoundingBox();
	for (auto itor=AliveItem->begin();itor!=AliveItem->end();itor++)
	{		
		auto FoodRect=(*itor)->getBoundingBox();
		if (CheckCollision(BearRect,FoodRect))
		{
			if ((*itor)->GetItemTpye()==ITEMS::FOOD)
			{
				HeroSprite->AddBlood((*itor)->GetBlood());
			}else if ((*itor)->GetItemTpye()==ITEMS::WEAPON)
			{
				//HeroSprite->
			}
			(*itor)->Picked();
		}
	}
}
bool ForestFight::CheckCollision(Rect& RectA,Rect& RectB){
	auto rect_A = Rect(RectA.origin.x+RectA.size.width*0.08, RectA.origin.y,RectA.size.width*0.84, RectA.size.height*0.1);
	auto rect_B = Rect(RectB.origin.x+RectB.size.width*0.08, RectB.origin.y,RectB.size.width*0.84, RectB.size.height*0.1);
	return rect_A.intersectsRect(rect_B);
}

void ForestFight::DetectDead(){
	for (auto itor=AliveRole->begin();itor!=AliveRole->end();)
	{
		if ((*itor)->GetBlood()<=DEATH)
		{
			if ((*itor)==HeroSprite)
			{
				GameOver(LOSE);
				break;
			}else
			{
				auto Psotion=Vec2((*itor)->GetEntity()->getPosition().x,(*itor)->GetEntity()->getPosition().y-(*itor)->GetEntity()->getContentSize().height/2);
				GenerateFood(Psotion);
				this->removeChild((*itor));
				itor=AliveRole->erase(itor);
			}			
		}else{
			itor++;
		}		
	}
	for (auto itor=AliveItem->begin();itor!=AliveItem->end();)
	{
		if ((*itor)->GetAlive()==DEAD)
		{
			this->removeChild((*itor));
			itor=AliveItem->erase(itor);
		}else{
			itor++;
		}		
	}
	if (AliveRole->size()==1)
	{
		GameOver(WIN);
	}
}
void ForestFight::GameOver(bool Result){
	unscheduleUpdate();
	_eventDispatcher->removeEventListener(listener);
	this->removeAllChildren();
	AliveRole->clear();	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto colorlayer=LayerColor::create(Color4B(210,210,210,255));
	colorlayer->setContentSize(visibleSize);
	this->addChild(colorlayer);

	auto MenuButton = ui::Button::create();
	MenuButton->setTitleText("Menu");
	MenuButton->setTitleFontName("fonts/Marker Felt.ttf");
	MenuButton->setTitleColor(Color3B::BLACK);
	MenuButton->setTitleFontSize(30);
	MenuButton->setZoomScale(0.3f);
	MenuButton->addTouchEventListener(CC_CALLBACK_2(ForestFight::MainMenu,this));
	MenuButton->setPressedActionEnabled(true);
	MenuButton->setPosition(Vec2(origin.x+visibleSize.width/2-200,origin.y+visibleSize.height*0.3));
	colorlayer->addChild(MenuButton);

	auto RestartButton = ui::Button::create();
	RestartButton->setTitleText("Restart");
	RestartButton->setTitleFontName("fonts/Marker Felt.ttf");
	RestartButton->setTitleColor(Color3B::BLACK);
	RestartButton->setTitleFontSize(30);
	RestartButton->setZoomScale(0.3f);
	RestartButton->addTouchEventListener(CC_CALLBACK_2(ForestFight::Restart,this));
	RestartButton->setPressedActionEnabled(true);
	RestartButton->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.3));
	colorlayer->addChild(RestartButton);
	
	auto NextButton = ui::Button::create();
	NextButton->setTitleText("Next");
	NextButton->setTitleFontName("fonts/Marker Felt.ttf");
	NextButton->setTitleColor(Color3B::BLACK);
	NextButton->setTitleFontSize(30);
	NextButton->setZoomScale(0.3f);
	NextButton->addTouchEventListener(CC_CALLBACK_2(ForestFight::NextChapter,this));
	NextButton->setPressedActionEnabled(true);
	NextButton->setPosition(Vec2(origin.x+visibleSize.width/2+200,origin.y+visibleSize.height*0.3));
	colorlayer->addChild(NextButton);
	

	if (Result==WIN)
	{
		auto label = Label::createWithTTF("YOU ARE WIN", "fonts/Marker Felt.ttf", 50);
		label->setPosition(Vec2(origin.x + visibleSize.width/2,	origin.y + visibleSize.height*0.9));
		label->setColor(Color3B::BLACK);
		colorlayer->addChild(label);
		auto bear=Sprite::createWithSpriteFrameName("Herofront.png");
		bear->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y + visibleSize.height*0.6));
		colorlayer->addChild(bear);
	
	}else{
		auto label = Label::createWithTTF("YOU ARE LOSE", "fonts/Marker Felt.ttf", 50);
		label->setPosition(Vec2(origin.x + visibleSize.width/2,	origin.y + visibleSize.height*0.9));
		label->setColor(Color3B::BLACK);
		colorlayer->addChild(label);
		auto bear=Sprite::createWithSpriteFrameName("Heroback.png");
		bear->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y + visibleSize.height*0.6));
		colorlayer->addChild(bear);
		NextButton->setColor(Color3B::GRAY);
		NextButton->setEnabled(false);
	}
}
void ForestFight::GenerateFood(Vec2& Position){
	auto item=Item::CreateItems(ITEMS::FOOD);
	this->addChild(item,100);
	item->setPosition(Position);
	AliveItem->push_back(item);
}
void ForestFight::Restart(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(ForestFight::createScene());
	}

}
void ForestFight::MainMenu(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(MainMenu::createScene());
	}

}
void ForestFight::NextChapter(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(LakeFight::createScene());
	}

}
void ForestFight::UpdateHeroPosition(){
	for (auto itor=AliveRole->begin();itor!=AliveRole->end();itor++)
	{
		if ((*itor)==HeroSprite)
		{
			continue;
		}
		((Enemy*)(*itor))->SetHeroPosition(Vec2(HeroSprite->GetEntity()->getPosition()));		
	}
}
void ForestFight::ShowMenu(){
	Director::getInstance()->pause();
	menulayer->setVisible(true);
}