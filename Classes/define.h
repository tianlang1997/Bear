//define.h
#pragma once

#define HERO_WALK		"hero_walk"		//Ӣ����·
#define HERO_JUMP		"hero_jump"		//Ӣ����Ծ
#define HERO_DOWN		"hero_down"		//Ӣ�۶���
#define HERO_THROW		"hero_throw"	//Ӣ��Ͷ��
#define HAND_BEAT		"hand_beat"		//�ֹ���
#define FOOT_BEAT		"foot_beat"		//�Ź���
#define HERO_RUN		"hero_run"		//Ӣ�۱���
#define HERO_ROLL		"hero_roll"     //Ӣ�۷���
#define BEAT_EFFECT		"beat_effect"	//����Ч��
#define ATTACKED		"hero_attacked" //������

#define SITDOWN_PNG		"Herodown0.png" //�¶�
#define ROLL_PNG		"Heroroll0.png" //����
#define SIDEWAYS_PNG	"Herosideways.png"//����

#define DEVIL_FLY		"devil_fly"		//��ħ��·
#define FIRE_BEAT		"fire_beat"		//�ֹ���
#define DEVIL_ATTACKED	"devil_attacked" //������

#define NONETAG			0				//�ޱ�ǩ
#define STONETAG		1				//ʯͷ��ǩ
#define FIRETAG			2				//�����ǩ
#define EDGETAG			3				//�߿��ǩ
#define HEROTAG			4				//Ӣ�۱�ǩ
#define FLOOTTAG		5				//�ذ��ǩ
#define DEVILGIRLTAG	6				//ħŮ��ǩ
#define ACTIONTO		7				//�ƶ���Ϊ��ǩ

#define WALKDISTANCE	2				//�ж�����=�����С*WALKDISTANCE
#define FULLBLOOD		100				//��Ѫ
#define DEATH			0				//����
#define TURNLEFT		true			//����
#define TURNRIGHT		false			//����
#define WIN				true			//Ӯ
#define LOSE			false			//��
#define ALIVE			true			//����
#define DEAD			false			//����
#define STATE_COUNT		RoleState::laststate				//״̬����
#define GRAY_BEAR		0				//��ɫС��
#define WHITE_BEAR		1				//��ɫС��
#define BEAR_SKIN_COUNT	2				//Ƥ������
#define SAFEREGION		2				//��ȫ����=�����С*SAFEREGION				
#define ENEMY_TOTAL		0				//��������
#define ENEMY_ACTIVE	1				//��Ծ�ĵ���
#define AGGRESIVITY		2				//������
#define COMBATIVE		100				//���ս��
enum GameModel{SIMPLEMODEL,NORMALMODEL,HARDMODEL};//��ģʽ//��ͨģʽ//����ģʽ
const static int GAME_MODEL[][3]={{15,5,10},{20,7,30},{30,9,60}};		//��ģʽ Enemy�����������е�����,��������
const static std::string EnemySideways[]={"Enemy0sideways.png","Enemy1sideways.png"};
const static std::string EnemyWalk[]={"Enemy0Walk","Enemy1Walk"};
const static std::string EnemyHandBeat[]={"Enemy0HandBeat","Enemy1HandBeat"};
const static std::string EnemyFootBeat[]={"Enemy0FootBeat","Enemy1FootBeat"};
const static std::string EnemyBeatEffect[]={"Enemy0BeatEffect","Enemy1BeatEffect"};
const static std::string EnemyHandBullet[]={"Enemy0hand_bullet0.png","Enemy1hand_bullet0.png"};
const static std::string EnemyAttacked[]={"Enemy0Attacked","Enemy1Attacked"};
const static std::string EnemyWander[]={"Enemy0Wander","Enemy1Wander"};
enum ITEMS{FOOD,WEAPON,lastitem};			//��Ʒ
enum FOODS{CLAW,APPLE,lastfood};			//ʳ��
enum WEAPONS{STONE,FIRE,lastweapon};		//����
#define FOODS_COUNT		FOODS::lastfood		//ʳ������
#define WEAPONS_COUNT	WEAPONS::lastweapon	//��������
#define ITEMS_COUNT	ITEMS::lastitem			//��Ʒ����
#define	CHAPTER_COUNT	10					//�½���	
enum Charpter{FORETFIGHT,LAKEFIGHT};		//�½�
enum RoleState{HANDBEAT,FOOTBEAT,THROWBEAT,BEATTACKED,MOVEUP,MOVEDOWN,MOVELEFT,MOVERIGHT,JUMPUP,SITDOWN,ROLL,WANDER,SHOWMENU,NONE,laststate};//״̬
const int HurtBlood[]={10,5,20};//HANDBEAT �˺�ֵ ��FOOTBEAT �˺�ֵ
const static std::string Items_Name[][3]={{"claw.png","apple.png"},{"stone.png","fire.png"}};		//��ģʽ Enemy�����������е�����,��������
const static int Items_Blood[][3]={{10,5},{10,15}};
const static int Items_Count[ITEMS_COUNT]={FOODS_COUNT,WEAPONS_COUNT};