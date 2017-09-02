#include "Enemy.h"
#include "define.h"
Enemy::Enemy(){
	CurrentState=RoleState::NONE;
}
Enemy::~Enemy(){
	unscheduleUpdate();
}
bool Enemy::init(){
	if (!Layer::init())
	{
		return false;
	}
	SkinType=CCRANDOM_0_1()*BEAR_SKIN_COUNT;	
	Entity=Sprite::createWithSpriteFrameName(EnemySideways[SkinType]);
	this->addChild(Entity);
	MyRegion=SAFEREGION*Entity->getContentSize().width;
	SetDistance();

	BloodFuller_BG_sprite=Sprite::createWithSpriteFrameName("Enemy0_Blood_Fuller_BG.png");
	this->addChild(BloodFuller_BG_sprite);
	BloodFuller=ProgressTimer::create(Sprite::createWithSpriteFrameName("Enemy0_Blood_Fuller.png"));
	BloodFuller->setType(ProgressTimer::Type::BAR);
	BloodFuller->setMidpoint(Vec2(0,1));
	BloodFuller->setBarChangeRate(Vec2(1, 0));
	BloodFuller->setPercentage(Blood);
	this->addChild(BloodFuller);
	Blood_Fuller_YFixed=Entity->getContentSize().height*2/3;
	BloodFuller_BG_sprite->setVisible(false);
	BloodFuller->setVisible(false);
	return true;
}

void Enemy::SetRegion(const Point& Begin,const Point& End){
	Moveable_Begin=Point(Begin.x,Begin.y+Entity->getContentSize().height/2);
	Moveable_End=Point(End);
	SetCurrent_Position();
	Entity->setPosition(Current_Position);
}
void Enemy::SetCurrent_Position(){
	auto temp=CCRANDOM_0_1()*9;
	if (temp<5.0f)
	{
		Current_Position.x=Moveable_Begin.x;
		LeftOrRight=TURNRIGHT;
	}else{
		Current_Position.x=Moveable_End.x;
		LeftOrRight=TURNLEFT;
	}
	Current_Position.y=CCRANDOM_0_1()*Moveable_End.y;
}

void Enemy::SetSkin(int SkinType){
	this->SkinType=SkinType;
}
void Enemy::SetDistance(){
	Distance=WALKDISTANCE*(Entity->getContentSize().width);
}
int Enemy::GetCurrentState(){
	return CurrentState;
}
void Enemy::MoveUp(){
	CurrentState=RoleState::MOVEUP;
	InitEntity(RoleState::MOVEUP);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyWalk[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::MoveUpEnd,this));
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

void Enemy::MoveUpEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void Enemy::MoveDown(){
	CurrentState=RoleState::MOVEDOWN;
	InitEntity(RoleState::MOVEDOWN);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyWalk[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::MoveUpEnd,this));
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

void Enemy::MoveDownEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void Enemy::MoveLeft(){
	LeftOrRight=TURNLEFT;
	CurrentState=RoleState::MOVELEFT;
	InitEntity(RoleState::MOVELEFT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyWalk[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::MoveUpEnd,this));
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

void Enemy::MoveLeftEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void Enemy::MoveRight(){
	LeftOrRight=TURNRIGHT;
	CurrentState=RoleState::MOVERIGHT;
	InitEntity(RoleState::MOVERIGHT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyWalk[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::MoveUpEnd,this));
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

void Enemy::MoveRightEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void Enemy::Wander(){
	CurrentState=RoleState::WANDER;
	InitEntity(RoleState::WANDER);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyWander[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::WanderEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	//执行动画
	Entity->runAction(sequence);
}

void Enemy::WanderEnd(){
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void Enemy::HandAttack(){
	IsAttack=true;
	CurrentState=RoleState::HANDBEAT;
	InitEntity(RoleState::HANDBEAT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyHandBeat[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::HandAttackEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);
	AttackEffect=Sprite::createWithSpriteFrameName(EnemyHandBullet[SkinType]);
	auto Effect=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyBeatEffect[SkinType]));
	AttackEffect->setPosition(Vec2(Current_Position.x+Entity->getContentSize().width*0.6,Current_Position.y));
	if (LeftOrRight)
	{
		AttackEffect->setPosition(Vec2(Current_Position.x-Entity->getContentSize().width*0.6,Current_Position.y));
	}
	//执行动画
	Entity->runAction(sequence);
	this->addChild(AttackEffect);
	AttackEffect->runAction(Effect);
}
void Enemy::HandAttackEnd(){
	IsAttack=false;
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void Enemy::FootAttack(){
	IsAttack=true;
	CurrentState=RoleState::FOOTBEAT;
	InitEntity(RoleState::FOOTBEAT);
	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyFootBeat[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::HandAttackEnd,this));
	auto sequence=Sequence::create(repeat,callBack,NULL);	
	AttackEffect=Sprite::createWithSpriteFrameName(EnemyHandBullet[SkinType]);
	auto Effect=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyBeatEffect[SkinType]));
	AttackEffect->setPosition(Vec2(Current_Position.x+Entity->getContentSize().width*0.6,Current_Position.y*0.8));
	if (LeftOrRight)
	{
		AttackEffect->setPosition(Vec2(Current_Position.x-Entity->getContentSize().width*0.6,Current_Position.y*0.8));
	}
	
	//执行动画
	Entity->runAction(sequence);
	this->addChild(AttackEffect);
	AttackEffect->runAction(Effect);
}

void Enemy::FootAttackEnd(){
	IsAttack=false;
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}

void Enemy::AddBlood(int Goods){
	Blood+=Goods;
	BloodFuller->setPercentage(Blood);
}

void Enemy::SubBlood(int Hurt){
	Hurt=Hurt*2;
	Blood-=Hurt;
	BloodFuller->setPercentage(Blood);
}

int Enemy::GetBlood(){
	return Blood;
}

void Enemy::Run(){
	if (LeftOrRight==TURNLEFT)
	{
		MoveLeft();
	}else{
		MoveRight();
	}
	scheduleUpdate();
}
void Enemy::update(float dt){ 
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
				auto AttackType=CCRANDOM_0_1();
				if (AttackType==0)
				{
					HandAttack();
				}else{
					FootAttack();
				}
			}else{
				Wander();
			}

		}
		break;
	}
}
bool Enemy::IsAttackable(){
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
			if (GAME_MODEL[GameModel][AGGRESIVITY]>temp)
			{
				if (temp<COMBATIVE/2)
				{
					HandAttack();
				}else{
					FootAttack();
				}
			}else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Enemy::IsInMyRegion(){
	auto EntityRect=Entity->getBoundingBox();
	Rect RegionRect= Rect(EntityRect.origin.x-MyRegion/2, EntityRect.origin.y-MyRegion/2,EntityRect.size.width+MyRegion,EntityRect.size.height+MyRegion);
	if (RegionRect.containsPoint(Hero_Position))
	{
		return true;
	}
	return false;
}

Sprite* Enemy::GetEntity(){
	return Entity;
}
float Enemy::GetEntityDepth(){
	return Entity->getBoundingBox().origin.y;
}

Sprite* Enemy::GetAttackEffect(){
	return AttackEffect;
}

void Enemy::StopMoving(){
	if ((ForbidState==CurrentState || ForbidState==RoleState::NONE) && IsAttack!=true)
	{		
		Entity->stopActionByTag(ACTIONTO);
		ForbidState=CurrentState;
		CurrentState=RoleState::NONE;
	}else{
		ForbidState=RoleState::NONE;
	}	
}
bool Enemy::GetIsAttack(){
	return IsAttack;
}
void Enemy::SetGameModel(int Model){
	GameModel=Model;
}
void Enemy::BeAttacked(bool A_Direction,int AttackType,const Item* Weapon){
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

	auto animate=Animate::create(AnimationCache::getInstance()->getAnimation(EnemyAttacked[SkinType]));
	auto repeat=Repeat::create(animate,1);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Enemy::BeAttackedEnd,this));
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
	BloodFuller_BG_sprite->setVisible(true);
	BloodFuller->setVisible(true);
	BloodFuller_BG_sprite->setPosition(Vec2(Entity->getPosition().x,Entity->getPosition().y+Blood_Fuller_YFixed));
	BloodFuller->setPosition(BloodFuller_BG_sprite->getPosition());
}
void Enemy::BeAttackedEnd(){
	BloodFuller_BG_sprite->setVisible(false);
	BloodFuller->setVisible(false);
	InitEntity(RoleState::NONE);
	CurrentState=RoleState::NONE;
}
bool Enemy::GetDirection(){
	return LeftOrRight;
}
std::vector<Item*>* Enemy::GetAliveWeapon(){
	return NULL;
}
void Enemy::SetHeroPosition(Vec2 Position){
	Hero_Position=Position;
}
void Enemy::InitEntity(int EnemyState){
	Current_Position=Entity->getPosition();
	this->removeChild(Entity,true);
	this->removeChild(AttackEffect,true);
	Entity=Sprite::createWithSpriteFrameName(EnemySideways[SkinType]);
	Entity->setPosition(Current_Position);
	if (LeftOrRight)
	{
		Entity->setFlippedX(true);
	}
	this->addChild(Entity);
}