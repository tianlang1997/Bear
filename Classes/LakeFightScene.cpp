#include "LakeFightScene.h"
#include "define.h"
#include "Header.h"
USING_NS_CC;
Scene* LakeFight::createScene()
{
	//// 'scene' is an autorelease object
	//auto scene = Scene::create();

	//// 'layer' is an autorelease object
	//auto layer = LakeFight::create();

	//// add layer as a child to scene
	//scene->addChild(layer);
	//// return the scene
	//return scene;

	//注意我们这边创造的是物理场景
	auto scene=Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//加入了重力，GRAVITY的值为（0，-980）
	//跟我们的世界重力加速度是一样的，比较真实
	scene->getPhysicsWorld()->setGravity(Point(0,-980));
	auto layer=LakeFight::create();
	scene->addChild(layer);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(-1);
	body->setContactTestBitmask(-1);
	body->setDynamic(false);
	auto edgeNode = Sprite::create();
	edgeNode->setTag(EDGETAG);
	edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

	return scene;
}

// on "init" you need to initialize your instance
bool LakeFight::init()
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
	AliveRole=new std::vector<Role*>;
	AliveItem=new std::vector<Item*>;
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(LakeFight::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(LakeFight::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(LakeFight::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LakeFight::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//背景
	auto Background=Sprite::createWithSpriteFrameName("LakeFight_Wall.png");
	Background->setAnchorPoint(Vec2(0,1));
	Background->setPosition(Vec2(origin.x,origin.y+visibleSize.height));
	this->addChild(Background,1);
	//地板
	auto Floot=Sprite::create();
	Floot->setContentSize(Size(Background->getContentSize().width,Background->getContentSize().height*0.2));
	Floot->setTag(FLOOTTAG);
	auto body=PhysicsBody::create();
	//给body一个框架（外壳？？？），这里我们就是草地的对应的长方形
	//把这个外壳给那个物理body
	body->addShape(PhysicsShapeBox::create(Floot->getContentSize()));
	//把刚体设为静态的
	//如果是动态刚体，它会受到力的作用
	//如果用另个刚体碰撞它的话，这个动态刚体就会运动或者旋转什么的
	//做为草地，它只能是一个安静的美男子......所以我们设为静态的
	body->setDynamic(false);
	//这个是把重力取消掉，草地时没有重力的
	body->setGravityEnable(true);
	//下面三个函数很复杂，我也是不怎么懂，网上的资料也不多
	//就是说要添加上去，貌似是碰撞检测要用到的
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(-1);
	body->setContactTestBitmask(-1);
	//下面的叫线性阻尼，我把它理解成摩擦力吧
	body->setLinearDamping(0.7f);
	//把刚体付给草地
	Floot->setPhysicsBody(body);
	Floot->setPosition(origin.x+Floot->getContentSize().width/2,origin.y+Floot->getContentSize().height/2);
	this->addChild(Floot,1);
	Moveable_Begin = Point(origin.x,origin.y+Floot->getContentSize().height);
	Moveable_End = Point(origin.x+Floot->getContentSize().width,origin.y+Background->getContentSize().height);
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
	//投石攻击
	ThrowBeatButton=Sprite::createWithSpriteFrameName("throwbeat.png");
	ThrowBeatButton->setPosition(Vec2(origin.x+visibleSize.width-100-Fixed,BasePositin.y));
	this->addChild(ThrowBeatButton,CZOrder);

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
	this->addChild(menulayer,CZOrder+10);

	DevilSprite=DevilGirl::create();
	DevilSprite->SetRegion(Moveable_Begin,Moveable_End);
	DevilSprite->SetGameModel(GameModel);
	DevilSprite->Run();
	AliveRole->push_back(DevilSprite);
	this->addChild(DevilSprite,10);


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Lake Fight", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	scheduleUpdate();
	return true;
}

LakeFight::~LakeFight(){
	AliveItem->clear();
	AliveRole->clear();
	this->cleanup();
	delete AliveRole;
	delete AliveItem;
	_eventDispatcher->removeEventListener(listener);
}

bool LakeFight::onTouchBegan(Touch* touch,Event *event)
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
	if(ThrowBeatButton->getBoundingBox().containsPoint(touch->getLocation())){
		//CCLOG("ThrowBeat0");	
		CurrentState=RoleState::THROWBEAT;
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

void LakeFight::onTouchMoved(Touch* touch,Event *event)
{

}

void LakeFight::onTouchEnded(Touch* touch,Event *eventt)
{
	if (CurrentState==RoleState::MOVEUP)
	{
		HeroSprite->JumpUp();
	}

	if (CurrentState==RoleState::MOVEDOWN)
	{
		HeroSprite->SitDown();
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
	if (CurrentState==RoleState::THROWBEAT)
	{
		HeroSprite->ThrowAttack();
	}
	if(CurrentState==RoleState::SHOWMENU){
		ShowMenu();
	}
}
void LakeFight::update(float dt){
	UpdateHeroPosition();
	GenerateStone();
	DetecCover();
	DetectCollision();
	DetectAttack();
	DetectDead();
}
void LakeFight::DetecCover(){	
	QuickSort(AliveRole,0,AliveRole->size()-1);
	auto ZOrder=1;
	for (auto itor=AliveRole->begin();itor!=AliveRole->end();itor++)
	{
		(*itor)->setLocalZOrder(ZOrder++);
	}
}

void LakeFight::QuickSort(std::vector<Role*>* vData,int Left,int Right){
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
void LakeFight::DetectAttack(){
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
void LakeFight::CheckAttack(Role& Attacker,Role& Victim){
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
void LakeFight::DetectCollision(){
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
				HeroSprite->AddWeaponList((*itor)->GetItemNO());
			}
			(*itor)->Picked();
		}
	}

}
bool LakeFight::CheckCollision(Rect& RectA,Rect& RectB){
	auto rect_A = Rect(RectA.origin.x+RectA.size.width*0.08, RectA.origin.y,RectA.size.width*0.84, RectA.size.height*0.1);
	auto rect_B = Rect(RectB.origin.x+RectB.size.width*0.08, RectB.origin.y,RectB.size.width*0.84, RectB.size.height*0.1);
	return rect_A.intersectsRect(rect_B);
}

void LakeFight::DetectDead(){
	/*for (auto itor=AliveRole->begin();itor!=AliveRole->end();)
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
	}*/
	if (HeroSprite->GetBlood()<=DEATH)
	{
		GameOver(LOSE);
		return;
	}
	if (DevilSprite->GetBlood()<=DEATH)
	{
		GameOver(WIN);
		return;
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

}
void LakeFight::GameOver(bool Result){
	unscheduleUpdate();
	_eventDispatcher->removeEventListener(listener);
	_eventDispatcher->removeEventListener(contactListener);
	this->removeAllChildren();
	AliveRole->clear();
	AliveItem->clear();
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
	MenuButton->addTouchEventListener(CC_CALLBACK_2(LakeFight::MainMenu,this));
	MenuButton->setPressedActionEnabled(true);
	MenuButton->setPosition(Vec2(origin.x+visibleSize.width/2-200,origin.y+visibleSize.height*0.3));
	colorlayer->addChild(MenuButton);

	auto RestartButton = ui::Button::create();
	RestartButton->setTitleText("Restart");
	RestartButton->setTitleFontName("fonts/Marker Felt.ttf");
	RestartButton->setTitleColor(Color3B::BLACK);
	RestartButton->setTitleFontSize(30);
	RestartButton->setZoomScale(0.3f);
	RestartButton->addTouchEventListener(CC_CALLBACK_2(LakeFight::Restart,this));
	RestartButton->setPressedActionEnabled(true);
	RestartButton->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height*0.3));
	colorlayer->addChild(RestartButton);

	auto NextButton = ui::Button::create();
	NextButton->setTitleText("Next");
	NextButton->setTitleFontName("fonts/Marker Felt.ttf");
	NextButton->setTitleColor(Color3B::BLACK);
	NextButton->setTitleFontSize(30);
	NextButton->setZoomScale(0.3f);
	NextButton->addTouchEventListener(CC_CALLBACK_2(LakeFight::NextChapter,this));
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
void LakeFight::GenerateFood(Vec2& Position){
	auto item=Item::CreateItems(ITEMS::FOOD);
	this->addChild(item,100);
	item->setPosition(Position);
	AliveItem->push_back(item);
}

void LakeFight::Restart(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(LakeFight::createScene());
	}

}
void LakeFight::MainMenu(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(MainMenu::createScene());
	}

}
void LakeFight::NextChapter(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(LakeFight::createScene());
	}
}

void LakeFight::GenerateStone(){
	if (AliveItem->size()<3)
	{
		auto item=Item::CreateItems(ITEMS::WEAPON,WEAPONS::STONE);
		item->setScale(0.5);
		item->setRotation(CCRANDOM_0_1()*180);
		this->addChild(item,100);
		auto width=Moveable_End.x-Moveable_Begin.x;
		auto x=CCRANDOM_0_1()*width;
		auto y=Moveable_Begin.y;
		item->setPosition(Vec2(x,y));
		AliveItem->push_back(item);
	}	
}

bool LakeFight::onContactBegin(const PhysicsContact& contact)
{
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	if (tagA==STONETAG && tagB == DEVILGIRLTAG)
	{
		auto A_Direction=TURNLEFT;
		if(spriteA->getPosition().x-DevilSprite->getPosition().x>0){
			A_Direction=TURNRIGHT;
		}
		DevilSprite->BeAttacked(A_Direction,RoleState::NONE,(Item*)spriteA);
	}else if (tagB==STONETAG && tagA == DEVILGIRLTAG)
	{
		auto A_Direction=TURNLEFT;
		if(spriteB->getPosition().x-DevilSprite->getPosition().x>0){
			A_Direction=TURNRIGHT;
		}
		DevilSprite->BeAttacked(A_Direction,RoleState::NONE,(Item*)spriteB);
	}else if (tagA==FIRETAG && tagB == HEROTAG)
	{
		auto A_Direction=TURNLEFT;
		if(spriteA->getPosition().x-HeroSprite->getPosition().x>0){
			A_Direction=TURNRIGHT;
		}
		HeroSprite->BeAttacked(A_Direction,RoleState::NONE,(Item*)spriteA);
	}else if (tagB==FIRETAG && tagA == HEROTAG)
	{
		auto A_Direction=TURNLEFT;
		if(spriteB->getPosition().x-HeroSprite->getPosition().x>0){
			A_Direction=TURNRIGHT;
		}
		HeroSprite->BeAttacked(A_Direction,RoleState::NONE,(Item*)spriteB);
	}	

	if (tagA == STONETAG)
	{
		auto AliveWeapon=HeroSprite->GetAliveWeapon();
		//RemoveAliveWeapon((Item*)spriteA,AliveWeapon);
		for (auto itor=AliveWeapon->begin();itor!=AliveWeapon->end();itor++)
		{
			if ((*itor)==spriteA)
			{   
				spriteA->removeFromParent();
				AliveWeapon->erase(itor);
				break;
			}
		}

	}else if(tagA == FIRETAG)
	{
		auto AliveWeapon=DevilSprite->GetAliveWeapon();
		//RemoveAliveWeapon((Item*)spriteA,AliveWeapon);
		for (auto itor=AliveWeapon->begin();itor!=AliveWeapon->end();itor++)
		{
			if ((*itor)==spriteA)
			{   
				spriteA->removeFromParent();
				AliveWeapon->erase(itor);
				break;
			}
		}
	}
		
	if (tagB == STONETAG)
	{
		auto AliveWeapon=HeroSprite->GetAliveWeapon();
		//RemoveAliveWeapon((Item*)spriteB,AliveWeapon);	
		for (auto itor=AliveWeapon->begin();itor!=AliveWeapon->end();itor++)
		{
			if ((*itor)==spriteB)
			{   
				spriteB->removeFromParent();
				AliveWeapon->erase(itor);
				break;
			}
		}
					
	}else if(tagB == FIRETAG)
	{
		auto AliveWeapon=DevilSprite->GetAliveWeapon();
		//RemoveAliveWeapon((Item*)spriteB,AliveWeapon);	
		for (auto itor=AliveWeapon->begin();itor!=AliveWeapon->end();itor++)
		{
			if ((*itor)==spriteB)
			{   
				spriteB->removeFromParent();
				AliveWeapon->erase(itor);
				break;
			}
		}
	}
		
	
	return true;
}

void LakeFight::RemoveAliveWeapon(Item* Weapon,std::vector<Item*>* AliveWeapon){
	/*for (auto itor=AliveWeapon->begin();itor!=AliveWeapon->end();itor++)
	{
		if ((*itor)==Weapon)
		{   
			Weapon->removeFromParent();
			AliveWeapon->erase(itor);
			break;
		}
	}*/
}

void LakeFight::UpdateHeroPosition(){
	for (auto itor=AliveRole->begin();itor!=AliveRole->end();itor++)
	{
		if ((*itor)==HeroSprite)
		{
			continue;
		}
		((DevilGirl*)(*itor))->SetHeroPosition(Vec2(HeroSprite->GetEntity()->getPosition()));		
	}
}
void LakeFight::ShowMenu(){
	Director::getInstance()->pause();
	menulayer->setVisible(true);
}