#ifndef __FOREST_FIGHT_SCENE_H__
#define __FOREST_FIGHT_SCENE_H__

#include "cocos2d.h"
#include "Header.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class ForestFight : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();     
	// implement the "static create()" method manually
	CREATE_FUNC(ForestFight);
	~ForestFight();
private:    

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	Hero* HeroSprite;
	Sprite* HandBeatButton;
	Sprite* FootBeatButton;
	Sprite* UpButton;
	Sprite* DownButton;
	Sprite* LeftButton;
	Sprite* RightButton;
	Sprite* MenuShowButton;
	MenuOptionLayer* menulayer;
	std::vector<Role*>* AliveRole;//活跃的角色
	std::vector<Item*>* AliveItem;//活跃的物品
	bool IsAttack;
	Point Moveable_Begin;
	Point Moveable_End;
	int CurrentState;
	int CZOrder;//¿Ø¼þ²ã´Î	
	int GameModel;
	int Enemy_Count;
	EventListenerTouchOneByOne* listener;
	void update(float dt) override;
	void ClearAliveRole();
	void DetecCover();
	void QuickSort(std::vector<Role*>* vData,int Left,int Right);
	void DetectCollision();
	bool CheckCollision(Rect& RectA,Rect& RectB);
	void GenerateEnemy();
	void DetectAttack();
	void CheckAttack(Role& Attacker,Role& Victim);
	void DetectDead();
	void GameOver(bool Result);
	void GenerateFood(Vec2& Position);
	void Restart(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void MainMenu(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void NextChapter(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void UpdateHeroPosition();
	void ShowMenu();
};

#endif // __HELLOWORLD_SCENE_H__
