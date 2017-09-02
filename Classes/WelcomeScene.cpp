#include "WelcomeScene.h"
#include "define.h"
#include "Header.h"

USING_NS_CC;
Welcome::Welcome()
{
}

Welcome::~Welcome()
{
}
Scene* Welcome::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Welcome::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}
bool Welcome::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bear/Common/Common.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bear/Enemy/Enemy.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bear/Hero/Hero.plist");
	//走路
	//主角
	auto HeroWalk = Animation::create();
	HeroWalk->setDelayPerUnit(0.2f);
	HeroWalk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herowalk0.png"));
	HeroWalk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herowalk1.png"));
	HeroWalk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herowalk0.png"));
	HeroWalk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herosideways.png"));
	HeroWalk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herowalk2.png"));
	HeroWalk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herowalk3.png"));
	HeroWalk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herowalk2.png"));
	AnimationCache::getInstance()->addAnimation(HeroWalk,HERO_WALK);
	//小灰熊
	auto Enemy0Walk = Animation::create();
	Enemy0Walk->setDelayPerUnit(0.3f);
	Enemy0Walk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0walk_right.png"));
	Enemy0Walk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0sideways.png"));
	Enemy0Walk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0walk_left.png"));
	AnimationCache::getInstance()->addAnimation(Enemy0Walk,EnemyWalk[GRAY_BEAR]);
	//小白熊
	auto Enemy1Walk = Animation::create();
	Enemy1Walk->setDelayPerUnit(0.3f);
	Enemy1Walk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1walk_right.png"));
	Enemy1Walk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1sideways.png"));
	Enemy1Walk->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1walk_left.png"));
	AnimationCache::getInstance()->addAnimation(Enemy1Walk,EnemyWalk[WHITE_BEAR]);
	//奔跑
	//主角
	auto HeroRun = Animation::create();
	HeroRun->setDelayPerUnit(0.1f);
	HeroRun->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herorun0.png"));
	HeroRun->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herorun1.png"));
	HeroRun->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herorun2.png"));
	HeroRun->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herorun3.png"));
	HeroRun->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herorun4.png"));
	HeroRun->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herorun5.png"));
	AnimationCache::getInstance()->addAnimation(HeroRun,HERO_RUN);
	//手攻击
	//主角
	auto HandBeat = Animation::create();
	HandBeat->setDelayPerUnit(0.1f);
	HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohandfight0.png"));
	HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohandfight1.png"));
	HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohandfight0.png"));
	HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohandfight2.png"));
	HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohandfight0.png"));
	AnimationCache::getInstance()->addAnimation(HandBeat,HAND_BEAT);
	//小灰熊
	auto Enemy0HandBeat = Animation::create();
	Enemy0HandBeat->setDelayPerUnit(0.1f);
	Enemy0HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_fight0.png"));
	Enemy0HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_fight1.png"));
	Enemy0HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_fight0.png"));
	Enemy0HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_fight2.png"));
	Enemy0HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_fight0.png"));
	AnimationCache::getInstance()->addAnimation(Enemy0HandBeat,EnemyHandBeat[GRAY_BEAR]);
	//小白熊
	auto Enemy1HandBeat = Animation::create();
	Enemy1HandBeat->setDelayPerUnit(0.1f);
	Enemy1HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_fight0.png"));
	Enemy1HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_fight1.png"));
	Enemy1HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_fight0.png"));
	Enemy1HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_fight2.png"));
	Enemy1HandBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_fight0.png"));
	AnimationCache::getInstance()->addAnimation(Enemy1HandBeat,EnemyHandBeat[WHITE_BEAR]);
	//脚攻击
	//主角
	auto FootBeat = Animation::create();
	FootBeat->setDelayPerUnit(0.1f);
	FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herofootfight0.png"));
	FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herofootfight1.png"));
	FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herofootfight2.png"));
	FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herofootfight1.png"));
	FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herofootfight0.png"));
	AnimationCache::getInstance()->addAnimation(FootBeat,FOOT_BEAT);
	//小灰熊
	auto Enemy0FootBeat = Animation::create();
	Enemy0FootBeat->setDelayPerUnit(0.1f);
	Enemy0FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0foot_fight0.png"));
	Enemy0FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0foot_fight1.png"));
	Enemy0FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0foot_fight2.png"));
	Enemy0FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0foot_fight1.png"));
	AnimationCache::getInstance()->addAnimation(Enemy0FootBeat,EnemyFootBeat[GRAY_BEAR]);
	//小白熊
	auto Enemy1FootBeat = Animation::create();
	Enemy1FootBeat->setDelayPerUnit(0.1f);
	Enemy1FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1foot_fight0.png"));
	Enemy1FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1foot_fight1.png"));
	Enemy1FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1foot_fight2.png"));
	Enemy1FootBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1foot_fight1.png"));
	AnimationCache::getInstance()->addAnimation(Enemy1FootBeat,EnemyFootBeat[WHITE_BEAR]);
	//打击效果
	//主角
	auto BeatEffect = Animation::create();
	BeatEffect->setDelayPerUnit(0.1f);
	BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohand_bullet0.png"));
	BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohand_bullet1.png"));
	BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohand_bullet2.png"));
	BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herohand_bullet1.png"));
	AnimationCache::getInstance()->addAnimation(BeatEffect,BEAT_EFFECT);
	//小灰熊
	auto Enemy0BeatEffect = Animation::create();
	Enemy0BeatEffect->setDelayPerUnit(0.1f);
	Enemy0BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_bullet0.png"));
	Enemy0BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_bullet1.png"));
	Enemy0BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_bullet2.png"));
	Enemy0BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0hand_bullet1.png"));
	AnimationCache::getInstance()->addAnimation(Enemy0BeatEffect,EnemyBeatEffect[GRAY_BEAR]);
	//小白熊
	auto Enemy1BeatEffect = Animation::create();
	Enemy1BeatEffect->setDelayPerUnit(0.1f);
	Enemy1BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_bullet0.png"));
	Enemy1BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_bullet1.png"));
	Enemy1BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_bullet2.png"));
	Enemy1BeatEffect->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1hand_bullet1.png"));
	AnimationCache::getInstance()->addAnimation(Enemy1BeatEffect,EnemyBeatEffect[WHITE_BEAR]);
	//被打效果
	//主角
	auto BeatAttacked = Animation::create();
	BeatAttacked->setDelayPerUnit(0.1f);
	BeatAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroattacked0.png"));
	BeatAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroattacked1.png"));
	BeatAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroattacked2.png"));
	BeatAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroattacked3.png"));
	BeatAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroattacked2.png"));
	BeatAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroattacked1.png"));
	BeatAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroattacked0.png"));
	AnimationCache::getInstance()->addAnimation(BeatAttacked,ATTACKED);
	//小灰熊
	auto Enemy0Attacked = Animation::create();
	Enemy0Attacked->setDelayPerUnit(0.1f);
	Enemy0Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0attacked0.png"));
	Enemy0Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0attacked1.png"));
	Enemy0Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0attacked0.png"));
	Enemy0Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0attacked2.png"));
	AnimationCache::getInstance()->addAnimation(Enemy0Attacked,EnemyAttacked[GRAY_BEAR]);
	//小白熊
	auto Enemy1Attacked = Animation::create();
	Enemy1Attacked->setDelayPerUnit(0.1f);
	Enemy1Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1attacked0.png"));
	Enemy1Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1attacked1.png"));
	Enemy1Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1attacked0.png"));
	Enemy1Attacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1attacked2.png"));
	AnimationCache::getInstance()->addAnimation(Enemy1Attacked,EnemyAttacked[WHITE_BEAR]);
	//发呆
	//小灰熊
	auto Enemy0Wander = Animation::create();
	Enemy0Wander->setDelayPerUnit(0.2f);
	Enemy0Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0wander0.png"));
	Enemy0Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0wander1.png"));
	Enemy0Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0wander2.png"));
	Enemy0Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy0wander3.png"));
	AnimationCache::getInstance()->addAnimation(Enemy0Wander,EnemyWander[GRAY_BEAR]);
	//小白熊
	auto Enemy1Wander = Animation::create();
	Enemy1Wander->setDelayPerUnit(0.2f);
	Enemy1Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1wander0.png"));
	Enemy1Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1wander1.png"));
	Enemy1Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1wander2.png"));
	Enemy1Wander->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Enemy1wander3.png"));
	AnimationCache::getInstance()->addAnimation(Enemy1Wander,EnemyWander[WHITE_BEAR]);
	//英雄跳跃
	auto HeroJump = Animation::create();
	HeroJump->setDelayPerUnit(0.1f);
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump0.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump1.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump2.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump3.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump3.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump3.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump2.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump2.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump2.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump2.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump1.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump1.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump0.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump0.png"));
	HeroJump->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herojump0.png"));
	AnimationCache::getInstance()->addAnimation(HeroJump,HERO_JUMP);
	//英雄下蹲
	auto HeroDown = Animation::create();
	HeroDown->setDelayPerUnit(0.1f);
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown0.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown1.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown2.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown3.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown3.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown3.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown2.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown1.png"));
	HeroDown->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herodown0.png"));
	AnimationCache::getInstance()->addAnimation(HeroDown,HERO_DOWN);
	//英雄投石
	auto HeroThrow = Animation::create();
	HeroThrow->setDelayPerUnit(0.07f);
	HeroThrow->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herothrow0.png"));
	HeroThrow->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herothrow1.png"));
	HeroThrow->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herothrow2.png"));
	HeroThrow->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herothrow3.png"));
	HeroThrow->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Herothrow4.png"));
	AnimationCache::getInstance()->addAnimation(HeroThrow,HERO_THROW);
	//英雄翻滚
	auto HeroRoll = Animation::create();
	HeroRoll->setDelayPerUnit(0.1f);
	HeroRoll->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroroll0.png"));
	HeroRoll->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroroll1.png"));
	HeroRoll->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroroll2.png"));
	HeroRoll->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroroll3.png"));
	HeroRoll->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Heroroll4.png"));
	AnimationCache::getInstance()->addAnimation(HeroRoll,HERO_ROLL);

	//魔女飞行
	auto DevilFly=Animation::create();
	DevilFly->setDelayPerUnit(0.1f);
	DevilFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fly2.png"));
	DevilFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fly1.png"));
	DevilFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fly2.png"));
	DevilFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fly0.png"));
	DevilFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fly3.png"));
	DevilFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fly4.png"));
	DevilFly->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fly3.png"));
	AnimationCache::getInstance()->addAnimation(DevilFly,DEVIL_FLY);
	//魔女攻击
	auto DevilFireBeat=Animation::create();
	DevilFireBeat->setDelayPerUnit(0.1f);
	DevilFireBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fight3.png"));
	DevilFireBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fight2.png"));
	DevilFireBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fight3.png"));
	DevilFireBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fight1.png"));
	DevilFireBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fight4.png"));
	DevilFireBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fight5.png"));
	DevilFireBeat->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0fight4.png"));
	AnimationCache::getInstance()->addAnimation(DevilFireBeat,FIRE_BEAT);
	//魔女被攻击
	auto DevilAttacked=Animation::create();
	DevilAttacked->setDelayPerUnit(0.1f);
	DevilAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0attacked0.png"));
	DevilAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0attacked1.png"));
	DevilAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0attacked2.png"));
	DevilAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0attacked3.png"));
	DevilAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0attacked2.png"));
	DevilAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0attacked1.png"));
	DevilAttacked->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Devil0attacked0.png"));
	AnimationCache::getInstance()->addAnimation(DevilAttacked,DEVIL_ATTACKED);

	auto colorlayer=LayerColor::create(Color4B(230,230,230,255));
	this->addChild(colorlayer);
	colorlayer->setContentSize(visibleSize);
	auto label = Label::createWithTTF("Loading ...", "fonts/Marker Felt.ttf", 50);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,	origin.y + visibleSize.height*0.8));
	label->setColor(Color3B::BLACK);
	colorlayer->addChild(label);

	auto JumpSprite=Sprite::createWithSpriteFrameName("Herosideways.png");
	colorlayer->addChild(JumpSprite);
	JumpSprite->setPosition(Vec2(origin.x+visibleSize.width/2-200,origin.y+visibleSize.height/2));
	auto herojump=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_JUMP));
	auto runJum=RepeatForever::create(herojump);
	JumpSprite->runAction(runJum);

	auto DownSprite=Sprite::createWithSpriteFrameName("Herosideways.png");
	colorlayer->addChild(DownSprite);
	DownSprite->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	auto herodown=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_DOWN));
	auto runDown=RepeatForever::create(herodown);
	DownSprite->runAction(runDown);

	auto ThrowSprite=Sprite::createWithSpriteFrameName("Herosideways.png");
	colorlayer->addChild(ThrowSprite);
	ThrowSprite->setPosition(Vec2(origin.x+visibleSize.width/2+200,origin.y+visibleSize.height/2));
	auto herothrow=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_THROW));
	auto runThrow=RepeatForever::create(herothrow);
	ThrowSprite->runAction(runThrow);

	auto HeroSprite=Sprite::createWithSpriteFrameName("Herosideways.png");
	colorlayer->addChild(HeroSprite);
	HeroSprite->setPosition(Vec2(origin.x,origin.y+visibleSize.height/2));
	auto bearrun=Animate::create(AnimationCache::getInstance()->getAnimation(HERO_RUN));
	auto runAnimation=RepeatForever::create(bearrun);
	auto Target_Positin=Vec2(origin.x+visibleSize.width,origin.y+visibleSize.height/2);
	auto actionTo = MoveTo::create(5, Target_Positin);
	auto callBack=CallFuncN::create(CC_CALLBACK_0(Welcome::ShowGameModel,this));
	auto sequence=Sequence::create(actionTo,callBack,NULL);
	HeroSprite->runAction(sequence);
	HeroSprite->runAction(runAnimation);

	auto DevilSprite=Sprite::createWithSpriteFrameName("Devil0sideways.png");
	colorlayer->addChild(DevilSprite);
	DevilSprite->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2+100));
	auto devilfly=Animate::create(AnimationCache::getInstance()->getAnimation(DEVIL_FLY));
	auto flyAnimation=RepeatForever::create(devilfly);
	DevilSprite->runAction(flyAnimation);
	
	auto fightSprite=Sprite::createWithSpriteFrameName("Devil0sideways.png");
	colorlayer->addChild(fightSprite);
	fightSprite->setPosition(Vec2(origin.x+visibleSize.width/2-100,origin.y+visibleSize.height/2+100));
	auto devilfight=Animate::create(AnimationCache::getInstance()->getAnimation(FIRE_BEAT));
	auto fightAnimation=RepeatForever::create(devilfight);
	fightSprite->runAction(fightAnimation);


	return true;

}
void Welcome::ShowGameModel(){
	this->removeAllChildren();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto colorlayer=LayerColor::create(Color4B(230,230,230,255));
	this->addChild(colorlayer);
	colorlayer->setContentSize(visibleSize);
	auto label = Label::createWithTTF("Choose The GameModel", "fonts/Marker Felt.ttf", 50);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,	origin.y + visibleSize.height*0.8));
	label->setColor(Color3B::BLACK);
	colorlayer->addChild(label);
	auto IsNewGame=UserDefault::getInstance()->getBoolForKey("NewGame",true);//读取指定key的数据,如不存在该数据则返回指定的默认值"default value"
	if (IsNewGame)
	{
		auto SimpleButton = ui::Button::create();
		SimpleButton->setTitleText("SIMPLE MODEL");
		SimpleButton->setTitleFontName("fonts/Marker Felt.ttf");
		SimpleButton->setTitleColor(Color3B::BLACK);
		SimpleButton->setTitleFontSize(30);
		SimpleButton->setZoomScale(0.3f);
		SimpleButton->addTouchEventListener(CC_CALLBACK_2(Welcome::SimpleModel,this));
		SimpleButton->setPressedActionEnabled(true);
		SimpleButton->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2+50));
		colorlayer->addChild(SimpleButton);

		auto NormalButton = ui::Button::create();
		NormalButton->setTitleText("NORMAL MODEL");
		NormalButton->setTitleFontName("fonts/Marker Felt.ttf");
		NormalButton->setTitleColor(Color3B::BLACK);
		NormalButton->setTitleFontSize(30);
		NormalButton->setZoomScale(0.3f);
		NormalButton->addTouchEventListener(CC_CALLBACK_2(Welcome::NormalModel,this));
		NormalButton->setPressedActionEnabled(true);
		NormalButton->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
		colorlayer->addChild(NormalButton);
	
		auto HardButton = ui::Button::create();
		HardButton->setTitleText("HARD MODEL");
		HardButton->setTitleFontName("fonts/Marker Felt.ttf");
		HardButton->setTitleColor(Color3B::BLACK);
		HardButton->setTitleFontSize(30);
		HardButton->setZoomScale(0.3f);
		HardButton->addTouchEventListener(CC_CALLBACK_2(Welcome::HardModel,this));
		HardButton->setPressedActionEnabled(true);
		HardButton->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2-50));
		colorlayer->addChild(HardButton);
		UserDefault::getInstance()->setIntegerForKey("NewGame",false);
		UserDefault::getInstance()->flush();
	}else{
		ShowMainMenu();
	}
}

void Welcome::SimpleModel(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		UserDefault::getInstance()->setIntegerForKey("GameModel",GameModel::SIMPLEMODEL);
		UserDefault::getInstance()->flush();
		ShowMainMenu();
	}	
}
void Welcome::NormalModel(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		UserDefault::getInstance()->setIntegerForKey("GameModel",GameModel::NORMALMODEL);
		UserDefault::getInstance()->flush();
		ShowMainMenu();
	}
}
void Welcome::HardModel(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		UserDefault::getInstance()->setIntegerForKey("GameModel",GameModel::HARDMODEL);
		UserDefault::getInstance()->flush();
		ShowMainMenu();
	}
}
void Welcome::ShowMainMenu(){
	Director::getInstance()->replaceScene(MainMenu::createScene());
}