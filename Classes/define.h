//define.h
#pragma once

#define HERO_WALK		"hero_walk"		//英雄走路
#define HERO_JUMP		"hero_jump"		//英雄跳跃
#define HERO_DOWN		"hero_down"		//英雄蹲下
#define HERO_THROW		"hero_throw"	//英雄投掷
#define HAND_BEAT		"hand_beat"		//手攻击
#define FOOT_BEAT		"foot_beat"		//脚攻击
#define HERO_RUN		"hero_run"		//英雄奔跑
#define HERO_ROLL		"hero_roll"     //英雄翻滚
#define BEAT_EFFECT		"beat_effect"	//攻击效果
#define ATTACKED		"hero_attacked" //被攻击

#define SITDOWN_PNG		"Herodown0.png" //下蹲
#define ROLL_PNG		"Heroroll0.png" //翻滚
#define SIDEWAYS_PNG	"Herosideways.png"//侧身

#define DEVIL_FLY		"devil_fly"		//恶魔走路
#define FIRE_BEAT		"fire_beat"		//手攻击
#define DEVIL_ATTACKED	"devil_attacked" //被攻击

#define NONETAG			0				//无标签
#define STONETAG		1				//石头标签
#define FIRETAG			2				//火球标签
#define EDGETAG			3				//边框标签
#define HEROTAG			4				//英雄标签
#define FLOOTTAG		5				//地板标签
#define DEVILGIRLTAG	6				//魔女标签
#define ACTIONTO		7				//移动行为标签

#define WALKDISTANCE	2				//行动距离=自身大小*WALKDISTANCE
#define FULLBLOOD		100				//满血
#define DEATH			0				//死亡
#define TURNLEFT		true			//向左
#define TURNRIGHT		false			//向右
#define WIN				true			//赢
#define LOSE			false			//输
#define ALIVE			true			//活着
#define DEAD			false			//死亡
#define STATE_COUNT		RoleState::laststate				//状态总数
#define GRAY_BEAR		0				//灰色小熊
#define WHITE_BEAR		1				//白色小熊
#define BEAR_SKIN_COUNT	2				//皮肤数量
#define SAFEREGION		2				//安全区域=自身大小*SAFEREGION				
#define ENEMY_TOTAL		0				//敌人总数
#define ENEMY_ACTIVE	1				//活跃的敌人
#define AGGRESIVITY		2				//攻击性
#define COMBATIVE		100				//最好战的
enum GameModel{SIMPLEMODEL,NORMALMODEL,HARDMODEL};//简单模式//普通模式//困难模式
const static int GAME_MODEL[][3]={{15,5,10},{20,7,30},{30,9,60}};		//简单模式 Enemy总数，场景中敌人数,攻击概率
const static std::string EnemySideways[]={"Enemy0sideways.png","Enemy1sideways.png"};
const static std::string EnemyWalk[]={"Enemy0Walk","Enemy1Walk"};
const static std::string EnemyHandBeat[]={"Enemy0HandBeat","Enemy1HandBeat"};
const static std::string EnemyFootBeat[]={"Enemy0FootBeat","Enemy1FootBeat"};
const static std::string EnemyBeatEffect[]={"Enemy0BeatEffect","Enemy1BeatEffect"};
const static std::string EnemyHandBullet[]={"Enemy0hand_bullet0.png","Enemy1hand_bullet0.png"};
const static std::string EnemyAttacked[]={"Enemy0Attacked","Enemy1Attacked"};
const static std::string EnemyWander[]={"Enemy0Wander","Enemy1Wander"};
enum ITEMS{FOOD,WEAPON,lastitem};			//物品
enum FOODS{CLAW,APPLE,lastfood};			//食物
enum WEAPONS{STONE,FIRE,lastweapon};		//武器
#define FOODS_COUNT		FOODS::lastfood		//食物总数
#define WEAPONS_COUNT	WEAPONS::lastweapon	//武器总数
#define ITEMS_COUNT	ITEMS::lastitem			//物品总数
#define	CHAPTER_COUNT	10					//章节数	
enum Charpter{FORETFIGHT,LAKEFIGHT};		//章节
enum RoleState{HANDBEAT,FOOTBEAT,THROWBEAT,BEATTACKED,MOVEUP,MOVEDOWN,MOVELEFT,MOVERIGHT,JUMPUP,SITDOWN,ROLL,WANDER,SHOWMENU,NONE,laststate};//状态
const int HurtBlood[]={10,5,20};//HANDBEAT 伤害值 ，FOOTBEAT 伤害值
const static std::string Items_Name[][3]={{"claw.png","apple.png"},{"stone.png","fire.png"}};		//简单模式 Enemy总数，场景中敌人数,攻击概率
const static int Items_Blood[][3]={{10,5},{10,15}};
const static int Items_Count[ITEMS_COUNT]={FOODS_COUNT,WEAPONS_COUNT};