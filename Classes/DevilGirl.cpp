#include "DevilGirl.h"
#include "define.h"
DevilGirl::DevilGirl(){
	CurrentState=RoleState::NONE;
}
DevilGirl::~DevilGirl(){
	body->release();
	unscheduleUpdate();
	AliveWeapon->clear();
	delete AliveWeapon;
}
bool DevilGirl::init(){
	if (!Layer::init())
	{
		return false;
	}
	AliveWeapon=new std::vector<Item*>;
	Entity=Sprite::createWithSpriteFrameName("Devil0sideways.png");
	Entity->setTag(DEVILGIRLTAG);
	body=PhysicsBody::create();
	body->addShape(PhysicsShapeBox::create(Entity->getContentSize()));
	body->setDynamic(true);
	body->setLinearDamping(0.7f);
	body->setGravityEnable(false);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(-1);
	body->setContactTestBitmask(-1);
	body->getFirstShape()->setRestitution(0);
	body->setRotationEnable(false);
	body->retain();
	Entity->setPhysicsBody(body);

	this->addChild(Entity);
	MyRegion=SAFEREGION*Entity->getContentSize().width*2;
	SetDistance();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	BloodFuller_BG_sprite=Sprite::createWithSpriteFrameName("Blood_Fuller_BG.png");
	BloodFuller_BG_sprite->setAnchorPoint(Vec2(1,1));
	BloodFuller_BG_sprite->setPosition(origin.x+visibleSize.width-10,origin.y+visibleSize.height-10);
	this->addChild(BloodFuller_BG_sprite);
	BloodFuller=ProgressTimer::create(Sprite::createWithSpriteFrameName("BossBlood_Fuller.png"));
	BloodFuller->setAnchorPoint(Vec2(1,1));
	BloodFuller->setPosition(BloodFuller_BG_sprite->getPosition());
	BloodFuller->setType(ProgressTimer::Type::BAR);
	BloodFuller->setMidpoint(Vec2(0,1));
	BloodFuller->setBarChangeRate(Vec2(1, 0));
	BloodFuller->setPercentage(Blood);
	this->addChild(BloodFuller);
	Blood_Fuller_YFixed=Entity->getContentSize().height*2/3;
	
	auto HeadSprite=Sprite::createWithSpriteFrameName("devilgirlhead.png");
	HeadSprite->setAnchorPoint(Vec2(1,1));
	auto Fixed=BloodFuller_BG_sprite->getContentSize().width+10;
	HeadSprite->setPosition(origin.x+visibleSize.width-Fixed,origin.y+visibleSize.height-10);
	this->addChild(HeadSprite);
	return true;
}

void DevilGirl::SetRegion(const Point& Begin,const Point& End){
	Moveable_Begin=Point(Begin.x,Begin.y+Entity->getContentSize().height);
	Moveable_End=Point(End.x-Entity->getContentSize().width,End.y-Entity->getContentSize().height/2);
	SetCurrent_Position();
	Entity->setPosition(Current_Position);
}
void DevilGirl::SetCurrent_Position(){
	auto temp=CCRANDOM_0_1()*9;
	if (temp<0)
	{
		Current_Position.x=Moveable_Begin.x;
		LeftOrRight=TURNRIGHT;
	}else{
		Current_Position.x=Moveable_End.x*0.8;
		LeftOrRight=TURNLEFT;
	}
	Current_Position.y=Moveable_End.y*0.8;
}

void DevilGirl::SetSkin(int SkinType){
	this->SkinType=SkinType;
}
void DevilGirl::SetDistance(){
	Distance=WALKDISTANCE*(Entity->getContentSize().width);
}

int DevilGirl::GetCurrentState(){
	return CurrentState;
}

void DevilGirl::FireAttack(){
	if (CurrentState==RoleState::THROWBEAT || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	CurrentState=RoleState::THROWBEAT;
	if (IsAttack)
	{
		IsAttack=false;
	}
	InitEntity(RoleState::THROWBEAT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(FIRE_BEAT));
	auto repeat=Repeat::create(animate,1);
	auto callBack0=CallFuncN::create(CC_CALLBACK_0(DevilGirl::LaunchFire,this));
	auto callBack1=CallFuncN::create(CC_CALLBACK_0(DevilGirl::FireAttackEnd,this));	
	auto sequence=Sequence::create(repeat,callBack0,callBack1,NULL);
	Entity->runAction(sequence);
}

void DevilGirl::LaunchFire(){
	auto FixedPosition=Entity->getContentSize().width*0.8;
	int VelocityH=800;
	if (LeftOrRight)
	{
		FixedPosition=-FixedPosition;
		VelocityH=-VelocityH;
	}
	auto Position=Point(Entity->getPosition().x+FixedPosition,Entity->getPosition().y+Entity->getContentSize().height*0.2);
	if (Moveable_End.x<Position.x || Moveable_Begin.x>Position.x)
	{
		return;
	}
	float VelRate=(Entity->getPosition().y-Hero_Position.y)/(Entity->getPosition().x-Hero_Position.x);

	auto Velocity=Vec2(VelocityH,-abs(VelocityH*VelRate));
	auto fire=Item::CreateItems(ITEMS::WEAPON,WEAPONS::FIRE);
	fire->setTag(FIRETAG);
	fire->setScale(0.5f);
	auto fire_body=PhysicsBody::create();
	fire_body->addShape(PhysicsShapeBox::create(fire->getContentSize()*0.5f));
	fire_body->setDynamic(true);
	fire_body->setLinearDamping(0.7f);
	fire_body->setGravityEnable(false);
	fire_body->setCategoryBitmask(1);
	fire_body->setCollisionBitmask(-1);
	fire_body->setContactTestBitmask(-1);
	fire->setPhysicsBody(fire_body);
	fire->setPosition(Position);
	fire_body->setVelocity(Velocity);
	auto pRotate = RotateBy::create(1.0f, 360);
	auto pRepeatRotate = RepeatForever::create(pRotate);
	fire->runAction(pRepeatRotate);
	this->addChild(fire);	
	AliveWeapon->push_back(fire);
}
void DevilGirl::FireAttackEnd(){
	IsAttack=false;
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void DevilGirl::MoveUp(){
	CurrentState=RoleState::MOVEUP;
	InitEntity(RoleState::MOVEUP);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(DEVIL_FLY));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(DevilGirl::MoveUpEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	auto Target_Positin=Vec2(Current_Position.x,Current_Position.y+Distance);
	if (Target_Positin.y>Moveable_End.y)
	{
		Target_Positin.y=Moveable_End.y;
	}
	auto actionTo = MoveTo::create(2, Target_Positin);
	//执行动画
	Entity->runAction(actionTo);
	actionTo->setTag(ACTIONTO);
	Entity->runAction(sequence);
}

void DevilGirl::MoveUpEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void DevilGirl::MoveDown(){
	CurrentState=RoleState::MOVEDOWN;
	InitEntity(RoleState::MOVEDOWN);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(DEVIL_FLY));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(DevilGirl::MoveUpEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	auto Target_Positin=Vec2(Current_Position.x,Current_Position.y-Distance);
	if (Target_Positin.y<Moveable_Begin.y)
	{
		Target_Positin.y=Moveable_Begin.y;
	}
	auto actionTo = MoveTo::create(2, Target_Positin);
	//执行动画
	Entity->runAction(actionTo);
	actionTo->setTag(ACTIONTO);
	Entity->runAction(sequence);
}

void DevilGirl::MoveDownEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void DevilGirl::MoveLeft(){
	LeftOrRight=TURNLEFT;
	CurrentState=RoleState::MOVELEFT;
	InitEntity(RoleState::MOVELEFT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(DEVIL_FLY));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(DevilGirl::MoveUpEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	auto Target_Positin=Vec2(Current_Position.x-Distance,Current_Position.y);
	if (Target_Positin.x<Moveable_Begin.x)
	{
		Target_Positin.x=Moveable_Begin.x;
	}
	auto actionTo = MoveTo::create(2, Target_Positin);
	//执行动画
	Entity->runAction(actionTo);
	actionTo->setTag(ACTIONTO);
	Entity->runAction(sequence);
}

void DevilGirl::MoveLeftEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void DevilGirl::MoveRight(){
	LeftOrRight=TURNRIGHT;
	CurrentState=RoleState::MOVERIGHT;
	InitEntity(RoleState::MOVERIGHT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(DEVIL_FLY));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(DevilGirl::MoveUpEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	auto Target_Positin=Vec2(Current_Position.x+Distance,Current_Position.y);
	if (Target_Positin.x>Moveable_End.x)
	{
		Target_Positin.x=Moveable_End.x;
	}
	auto actionTo = MoveTo::create(2, Target_Positin);
	//执行动画
	Entity->runAction(actionTo);
	actionTo->setTag(ACTIONTO);
	Entity->runAction(sequence);
}

void DevilGirl::MoveRightEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void DevilGirl::Wander(){
	CurrentState=RoleState::WANDER;
	InitEntity(RoleState::WANDER);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(DEVIL_FLY));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(DevilGirl::WanderEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	Entity->runAction(sequence);
}

void DevilGirl::WanderEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void DevilGirl::AddBlood(int Goods){
	Blood+=Goods;
	BloodFuller->setPercentage(Blood);
}

void DevilGirl::SubBlood(int Hurt){
	Hurt=Hurt*2;
	Blood-=Hurt;
	BloodFuller->setPercentage(Blood);
}

int DevilGirl::GetBlood(){
	return Blood;
}

void DevilGirl::Run(){
	if (LeftOrRight==TURNLEFT)
	{
		MoveLeft();
	}else{
		MoveRight();
	}
	scheduleUpdate();
}
void DevilGirl::update(float dt){ 
	if (CurrentState!=RoleState::NONE || CurrentState==RoleState::BEATTACKED==true)
	{
		return;
	}
	if (IsAttackable())
	{
		return;
	}
	int StateTemp=CCRANDOM_0_1()*STATE_COUNT;

	switch (StateTemp)
	{
	case RoleState::MOVEUP:
		MoveUp();
		break;
	case RoleState::MOVEDOWN:
		MoveDown();
		break;
	case RoleState::MOVELEFT:
		MoveLeft();
		break;
	case RoleState::MOVERIGHT:
		MoveRight();
		break;
	default:
		if(StateTemp == RoleState::HANDBEAT || StateTemp == RoleState::FOOTBEAT)
		{
			auto temp=CCRANDOM_0_1()*COMBATIVE;
			if (GAME_MODEL[GameModel][AGGRESIVITY]>temp)
			{				
				FireAttack();
			}else{
				Wander();
			}
		}else{
			Wander();
		}		
		break;
	}
}
bool DevilGirl::IsAttackable(){
	if (IsInMyRegion())
	{
		auto tempX=Entity->getPosition().x-Hero_Position.x;
		auto tempY=Entity->getPosition().y-Hero_Position.y;
		if (tempX>0)
		{					
			LeftOrRight=TURNLEFT;
		}else{
			LeftOrRight=TURNRIGHT;
		}
		if (abs(tempX)<MyRegion/2 && abs(tempY)>MyRegion/2)
		{
			if (tempY>0)
			{
				MoveDown();
			}else{
				MoveUp();
			}
		}else if(abs(tempY)<MyRegion/2 && abs(tempX)>MyRegion/2){
			if (tempX>0)
			{
				MoveLeft();
			}else{
				MoveRight();
			}
		}else if(abs(tempY)<MyRegion/2 && abs(tempX)<MyRegion/2)
		{
			auto temp=CCRANDOM_0_1()*COMBATIVE;
			if (GAME_MODEL[GameModel][AGGRESIVITY]<temp)
			{
				FireAttack();
			}else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool DevilGirl::IsInMyRegion(){
	auto EntityRect=Entity->getBoundingBox();
	Rect RegionRect= Rect(EntityRect.origin.x-MyRegion/2, EntityRect.origin.y-MyRegion/2,EntityRect.size.width+MyRegion,EntityRect.size.height+MyRegion);
	if (RegionRect.containsPoint(Hero_Position))
	{
		return true;
	}
	return false;
}


Sprite* DevilGirl::GetEntity(){
	return Entity;
}
float DevilGirl::GetEntityDepth(){
	return Entity->getBoundingBox().origin.y;
}

Sprite* DevilGirl::GetAttackEffect(){
	return AttackEffect;
}

void DevilGirl::StopMoving(){
	if ((ForbidState==CurrentState || ForbidState==RoleState::NONE) && IsAttack!=true)
	{		
		Entity->stopActionByTag(ACTIONTO);
		ForbidState=CurrentState;
		CurrentState=RoleState::NONE;
	}else{
		ForbidState=RoleState::NONE;
	}	
}
bool DevilGirl::GetIsAttack(){
	return IsAttack;
}
void DevilGirl::SetGameModel(int Model){
	GameModel=Model;
}
void DevilGirl::BeAttacked(bool A_Direction,int AttackType,const Item* Weapon){
	if (CurrentState==RoleState::BEATTACKED||(AttackType==RoleState::NONE && Weapon==nullptr))
	{
		return;
	}
	if (IsAttack)
	{
		IsAttack=false;
	}
	CurrentState=RoleState::BEATTACKED;
	if (AttackType==RoleState::NONE)
	{
		SubBlood(Weapon->GetBlood());
	}else{
		SubBlood(HurtBlood[AttackType]);
	}
	InitEntity(RoleState::BEATTACKED);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(DEVIL_ATTACKED));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(DevilGirl::BeAttackedEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	auto Target_Positin=Vec2(Current_Position.x,Current_Position.y);
	if (A_Direction==TURNLEFT)
	{
		Target_Positin.x+=Distance;
	}else{
		Target_Positin.x-=Distance;
	}
	if (Target_Positin.x<Moveable_Begin.x)
	{
		Target_Positin.x=Moveable_Begin.x;
	}
	auto actionTo = MoveTo::create(2, Target_Positin);
	//执行动画
	Entity->runAction(actionTo);
	actionTo->setTag(ACTIONTO);
	Entity->runAction(sequence);
}
void DevilGirl::BeAttackedEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}
bool DevilGirl::GetDirection(){
	return LeftOrRight;
}
std::vector<Item*>* DevilGirl::GetAliveWeapon(){
	return AliveWeapon;
}
void DevilGirl::SetHeroPosition(Vec2 Position){
	Hero_Position=Position;
}
void DevilGirl::InitEntity(int EnemyState){
	Current_Position=Entity->getPosition();
	this->removeChild(Entity,true);
	this->removeChild(AttackEffect,true);
	Entity=Sprite::createWithSpriteFrameName("Devil0sideways.png");
	Entity->setTag(DEVILGIRLTAG);
	Entity->setPhysicsBody(body);
	Entity->setPosition(Current_Position);
	if (LeftOrRight)
	{
		Entity->setFlippedX(true);
	}
	this->addChild(Entity);
}