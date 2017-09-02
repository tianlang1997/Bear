#include "Hero.h"
#include "define.h"
Hero::Hero(){}
Hero::~Hero(){
	AliveWeapon->clear();
	delete AliveWeapon;
}

bool Hero::init(){
	if (!Layer::init())
	{
		return false;
	}
	AliveWeapon=new std::vector<Item*>;//活跃的物品

	this->setColor(Color3B::BLUE);
	CurrentState=RoleState::NONE;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();	
	Entity=Sprite::createWithSpriteFrameName("Herofront.png");
	InitEntity(NONE);
	Entity->setPosition(Point(origin.x+visibleSize.width*0.2,origin.y+visibleSize.height*0.4));
	SetDistance();

	auto HeadSprite=Sprite::createWithSpriteFrameName("head.png");
	HeadSprite->setAnchorPoint(Vec2(0,1));
	auto Fixed=10;
	HeadSprite->setPosition(origin.x+Fixed,origin.y+visibleSize.height-Fixed);
	this->addChild(HeadSprite);
	
	BloodFuller_BG_sprite=Sprite::createWithSpriteFrameName("Blood_Fuller_BG.png");
	BloodFuller_BG_sprite->setAnchorPoint(Vec2(0,1));
	BloodFuller_BG_sprite->setPosition(origin.x+(Fixed<<2)+HeadSprite->getContentSize().width,origin.y+visibleSize.height-10);
	this->addChild(BloodFuller_BG_sprite);
	BloodFuller=ProgressTimer::create(Sprite::createWithSpriteFrameName("Blood_Fuller.png"));
	BloodFuller->setType(ProgressTimer::Type::BAR);
	BloodFuller->setAnchorPoint(Vec2(0,1));
	BloodFuller->setMidpoint(Vec2(0,1));
	BloodFuller->setBarChangeRate(Vec2(1, 0));
	BloodFuller->setPercentage(Blood);
	BloodFuller->setPosition(BloodFuller_BG_sprite->getPosition());
	this->addChild(BloodFuller);

	auto Stone=Sprite::createWithSpriteFrameName("stone.png");
	Stone->setPosition(Point(HeadSprite->getPosition().x+20,HeadSprite->getPosition().y-Stone->getContentSize().height*(1.5)));
	Stone->setScale(0.3f);
	this->addChild(Stone);
	StoneCount = Label::createWithTTF(StringUtils::format("(%d)", WeaponList[WEAPONS::STONE]), "fonts/Marker Felt.ttf", 16);
	StoneCount->setPosition(Point(Stone->getPosition().x+20,Stone->getPosition().y));
	StoneCount->setColor(Color3B::BLACK);
	this->addChild(StoneCount);
	return true;
}

void Hero::SetRegion(const Point& Begin,const Point& End){
	Moveable_Begin=Point(Begin.x,Begin.y+Entity->getContentSize().height/2);
	Moveable_End=Point(End);
}
void Hero::SetDistance(){
	Distance=WALKDISTANCE*(Entity->getContentSize().width*4);
}

int Hero::GetCurrentState(){
	return CurrentState;
}
void Hero::MoveUp(){
	if (CurrentState==RoleState::MOVEUP || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	CurrentState=RoleState::MOVEUP;
	if (IsAttack)
	{
		IsAttack=false;
	}
	InitEntity(MOVEUP);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_WALK));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::MoveUpEnd,this));
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

void Hero::MoveUpEnd(){
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}

void Hero::MoveDown(){
	if (CurrentState==RoleState::MOVEDOWN || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	CurrentState=RoleState::MOVEDOWN;
	if (IsAttack)
	{
		IsAttack=false;
	}
	InitEntity(MOVEDOWN);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_WALK));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::MoveUpEnd,this));
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

void Hero::MoveDownEnd(){
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}

void Hero::MoveLeft(){
	if (CurrentState==MOVELEFT || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	LeftOrRight=TURNLEFT;	
	if (IsAttack)
	{
		IsAttack=false;
	}
	Animate* animate=nullptr;
	MoveTo* actionTo=nullptr;
	Vec2 Target_Positin;
	if (CurrentState==MOVEDOWN || CurrentState == MOVEUP || CurrentState==JUMPUP || CurrentState==SITDOWN )
	{
		InitEntity(ROLL);
		Target_Positin=Vec2(Current_Position.x-Distance*10,Current_Position.y);
	}else{
		InitEntity(MOVELEFT);
		Target_Positin=Vec2(Current_Position.x-Distance,Current_Position.y);	
	}

	if (Target_Positin.x<Moveable_Begin.x)
	{
		Target_Positin.x=Moveable_Begin.x;
	}

	if (CurrentState==MOVEDOWN || CurrentState == MOVEUP || CurrentState==JUMPUP || CurrentState==SITDOWN )
	{
		animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_ROLL));
		actionTo = MoveTo::create(2, Target_Positin);
	}else{
		animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_WALK));
		actionTo = MoveTo::create(2, Target_Positin);
	}
	CurrentState=RoleState::MOVELEFT;
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::MoveLeftEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	//执行动画
	Entity->runAction(actionTo);
	actionTo->setTag(ACTIONTO);
	Entity->runAction(sequence);
}

void Hero::MoveLeftEnd(){
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}

void Hero::MoveRight(){
	if (CurrentState==MOVERIGHT || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	LeftOrRight=TURNRIGHT;	
	if (IsAttack)
	{
		IsAttack=false;
	}
	Animate* animate=nullptr;
	MoveTo* actionTo=nullptr;
	Vec2 Target_Positin;
	if (CurrentState==MOVEDOWN || CurrentState == MOVEUP || CurrentState==JUMPUP || CurrentState==SITDOWN )
	{
		InitEntity(ROLL);
		Target_Positin=Vec2(Current_Position.x+Distance*10,Current_Position.y);
	}else{
		InitEntity(MOVERIGHT);
		Target_Positin=Vec2(Current_Position.x+Distance,Current_Position.y);	
	}

	if (Target_Positin.x>Moveable_End.x)
	{
		Target_Positin.x=Moveable_End.x;
	}

	if (CurrentState==MOVEDOWN || CurrentState == MOVEUP || CurrentState==JUMPUP || CurrentState==SITDOWN )
	{
		animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_ROLL));
		actionTo = MoveTo::create(2, Target_Positin);
	}else{
		animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_WALK));
		actionTo = MoveTo::create(2, Target_Positin);
	}
	CurrentState=RoleState::MOVERIGHT;
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::MoveRightEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	//执行动画
	Entity->runAction(actionTo);
	actionTo->setTag(ACTIONTO);
	Entity->runAction(sequence);
	
}

void Hero::MoveRightEnd(){
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}

void Hero::HandAttack(){	
	if (CurrentState==RoleState::HANDBEAT || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	IsAttack=true;
	CurrentState=RoleState::HANDBEAT;
	InitEntity(HANDBEAT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(HAND_BEAT));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::HandAttackEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);	
	AttackEffect=Sprite::createWithSpriteFrameName("hand_bullet0.png");
	auto Effect=Animate::create(AnimationCache::getInstance()->getAnimation(BEAT_EFFECT));
	AttackEffect->setPosition(Vec2(Current_Position.x+Entity->getContentSize().width,Current_Position.y+Entity->getContentSize().height*0.2));
	if (LeftOrRight)
	{
		AttackEffect->setPosition(Vec2(Current_Position.x-Entity->getContentSize().width,Current_Position.y+Entity->getContentSize().height*0.2));
	}
	
	//执行动画
	Entity->runAction(sequence);
	this->addChild(AttackEffect);
	AttackEffect->runAction(Effect);
}
void Hero::HandAttackEnd(){
	IsAttack=false;
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}

void Hero::FootAttack(){
	if (CurrentState==RoleState::FOOTBEAT || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	IsAttack=true;
	CurrentState=RoleState::FOOTBEAT;
	InitEntity(FOOTBEAT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(FOOT_BEAT));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::FootAttackEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	Vec2 Target_Positin;
	auto actionTo = MoveTo::create(2, Target_Positin);
	if (LeftOrRight)
	{
		Target_Positin=Vec2(Current_Position.x-Distance/5,Current_Position.y);
		if (Target_Positin.x<Moveable_Begin.x)
		{
			Target_Positin.x=Moveable_Begin.x+Entity->getContentSize().width;
		}
	}else
	{
		Target_Positin=Vec2(Current_Position.x+Distance/5,Current_Position.y);
		if (Target_Positin.x>Moveable_End.x)
		{
			Target_Positin.x=Moveable_End.x-Entity->getContentSize().width;
		}
	}
	Entity->setPosition(Target_Positin);
	AttackEffect=Sprite::createWithSpriteFrameName("hand_bullet0.png");
	auto Effect=Animate::create(AnimationCache::getInstance()->getAnimation(BEAT_EFFECT));
	AttackEffect->setPosition(Vec2(Target_Positin.x+Entity->getContentSize().width,Target_Positin.y+Entity->getContentSize().width/2));
	if (LeftOrRight)
	{
		AttackEffect->setPosition(Vec2(Target_Positin.x-Entity->getContentSize().width,Target_Positin.y+Entity->getContentSize().width/2));
	}
	//执行动画
	Entity->runAction(sequence);
	this->addChild(AttackEffect);
	AttackEffect->runAction(Effect);
}

void Hero::FootAttackEnd(){
	IsAttack=false;
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}

void Hero::AddBlood(int Goods){
	Blood+=Goods;
	BloodFuller->setPercentage(Blood);
}

void Hero::SubBlood(int Hurt){

	Blood-=Hurt;
	BloodFuller->setPercentage(Blood);
}

int Hero::GetBlood(){
	return Blood;
}

Sprite* Hero::GetEntity(){
	return Entity;
}
float Hero::GetEntityDepth(){
	return Entity->getBoundingBox().origin.y;
}

Sprite* Hero::GetAttackEffect(){
	return AttackEffect;
}

void Hero::StopMoving(){
	if ((ForbidState==CurrentState || ForbidState==RoleState::NONE) && IsAttack==false)
	{			
		Entity->stopActionByTag(ACTIONTO);
		ForbidState=CurrentState;
	}else{
		ForbidState=RoleState::NONE;
		switch (CurrentState)
		{
		case RoleState::MOVELEFT:
			Entity->setPosition(Vec2(Entity->getPosition().x-40,Entity->getPosition().y));
			break;
		case RoleState::MOVERIGHT:
			Entity->setPosition(Vec2(Entity->getPosition().x+40,Entity->getPosition().y));
			break;
		case RoleState::MOVEUP:
			Entity->setPosition(Vec2(Entity->getPosition().x,Entity->getPosition().y+40));
			break;
		case RoleState::MOVEDOWN:
			Entity->setPosition(Vec2(Entity->getPosition().x,Entity->getPosition().y-40));
			break;
		default:
			break;
		}
	}
}
bool Hero::GetIsAttack(){
	return IsAttack;
}
void Hero::BeAttacked(bool A_Direction,int AttackType,const Item *Weapon){
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

	InitEntity(BEATTACKED);

	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(ATTACKED));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::BeAttackedEnd,this));
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
void Hero::BeAttackedEnd(){
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}
bool Hero::GetDirection(){
	return LeftOrRight;
}

void Hero::JumpUp(){
	if (CurrentState==RoleState::JUMPUP || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	CurrentState=RoleState::JUMPUP;	
	if (IsAttack)
	{
		IsAttack=false;
	}
	InitEntity(JUMPUP);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_JUMP));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::JumpUpEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);	
	//执行动画
	Entity->runAction(sequence);
	Entity->getPhysicsBody()->setVelocity(Vec2(0,700));
}

void Hero::JumpUpEnd(){
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}

void Hero::ThrowAttack(){
	if (CurrentState==RoleState::THROWBEAT || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	CurrentState=RoleState::THROWBEAT;
	if (IsAttack)
	{
		IsAttack=false;
	}	
	InitEntity(THROWBEAT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_THROW));
	auto repeat=Repeat::create(animate,1);
	auto callBack0=CallFuncN::create(CC_CALLBACK_0(Hero::LaunchStone,this));
	auto callBack1=CallFuncN::create(CC_CALLBACK_0(Hero::ThrowAttackEnd,this));
	Sequence* sequence;
	if (GotWeapon(STONE))
	{
		sequence=Sequence::create(repeat,callBack0,callBack1,NULL);
	}else{
		sequence=Sequence::create(repeat,callBack1,NULL);
	}
	Entity->runAction(sequence);
}

void Hero::LaunchStone(){
	auto FixedPosition=Entity->getContentSize().width*0.6;
	int VelFixed=600;
	if (LeftOrRight)
	{
		FixedPosition=-FixedPosition;
		VelFixed=-VelFixed;
	}
	auto Position=Point(Entity->getPosition().x+FixedPosition,Entity->getPosition().y+Entity->getContentSize().height*0.6);
	auto Velocity=Vec2(VelFixed,300);
	auto stone=Item::CreateItems(ITEMS::WEAPON,WEAPONS::STONE);
	stone->setScale(0.3f);
	auto stone_body=PhysicsBody::create();
	stone_body->addShape(PhysicsShapeBox::create(stone->getContentSize()*0.3f));
	stone_body->setDynamic(true);
	stone_body->setLinearDamping(0.7f);
	stone_body->setGravityEnable(true);
	stone_body->setCategoryBitmask(1);
	stone_body->setCollisionBitmask(-1);
	stone_body->setContactTestBitmask(-1);
	stone->setPhysicsBody(stone_body);
	stone->setPosition(Position);
	stone_body->setVelocity(Velocity);
	auto pRotate = RotateBy::create(0.1f, 360);
	auto pRepeatRotate = RepeatForever::create(pRotate);
	stone->runAction(pRepeatRotate);
	this->addChild(stone);	
	stone->setTag(STONETAG);
	AliveWeapon->push_back(stone);
	SubWeaponList(STONE);
}
void Hero::ThrowAttackEnd(){
	InitEntity(NONE);
	CurrentState=RoleState::NONE;
}
void Hero::SitDown(){
	if (CurrentState==RoleState::SITDOWN || CurrentState==RoleState::BEATTACKED)
	{
		return;
	}
	CurrentState=RoleState::SITDOWN;
	if (IsAttack)
	{
		IsAttack=false;
	}	
	InitEntity(SITDOWN);
	Entity->setPosition(Vec2(Current_Position.x,Current_Position.y-50));	
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_DOWN));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Hero::SitDownEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);	
	//执行动画
	Entity->runAction(sequence);
}
void Hero::SitDownEnd(){
	InitEntity(NONE);
	Entity->setPosition(Vec2(Current_Position.x,Current_Position.y+50));
	CurrentState=RoleState::NONE;
}

void Hero::AddWeaponList(int WeaponNo){
	WeaponList[WeaponNo]+=1;
	Label* templabel;
	if (WeaponNo==WEAPONS::STONE)
	{
		templabel=StoneCount;
	}
	templabel->setString(StringUtils::format("(%d)", WeaponList[WeaponNo]));


}
void Hero::SubWeaponList(int WeaponNo){
	WeaponList[WeaponNo]-=1;
	Label* templabel;
	if (WeaponNo==WEAPONS::STONE)
	{
		templabel=StoneCount;
	}
	templabel->setString(StringUtils::format("(%d)", WeaponList[WeaponNo]));
}
bool Hero::GotWeapon(int WeaponNo){
	if (WeaponList[WeaponNo]>0)
	{
		return true;
	}
	return false;
}

const std::map<int,int>& Hero::GetWeaponList(){
	return WeaponList;
}
std::vector<Item*>* Hero::GetAliveWeapon(){
	return AliveWeapon;
}
void Hero::InitEntity(int HeroState){
	Current_Position=Entity->getPosition();
	this->removeChild(Entity,true);
	this->removeChild(AttackEffect,true);
	auto Herobody=PhysicsBody::create();
	if (HeroState==SITDOWN)
	{		
		Entity=Sprite::createWithSpriteFrameName(SITDOWN_PNG);
		auto HeroShape=PhysicsShapeBox::create(Size(Entity->getContentSize().width,Entity->getContentSize().height*0.5));
		Herobody->addShape(HeroShape);
	}else if (HeroState==ROLL)
	{
		Entity=Sprite::createWithSpriteFrameName(ROLL_PNG);
		auto HeroShape=PhysicsShapeCircle::create(Entity->getContentSize().width/2);
		Herobody->addShape(HeroShape);

	}else{
		Entity=Sprite::createWithSpriteFrameName(SIDEWAYS_PNG);		
		auto HeroShape=PhysicsShapeBox::create(Entity->getContentSize());
		Herobody->addShape(HeroShape);
	}		
	Herobody->setDynamic(true);
	Herobody->setLinearDamping(0.7f);
	Herobody->setGravityEnable(true);
	Herobody->setCategoryBitmask(1);
	Herobody->setCollisionBitmask(-1);
	Herobody->setContactTestBitmask(-1);
	Herobody->getFirstShape()->setRestitution(0);
	Entity->setPhysicsBody(Herobody);
	Entity->setPosition(Current_Position);
	Entity->setTag(HEROTAG);
	if (LeftOrRight)
	{
		Entity->setFlippedX(true);
	}
	this->addChild(Entity);
}