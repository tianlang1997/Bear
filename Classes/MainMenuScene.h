#ifndef _MAIN_MENU_SCENE_
#define _MAIN_MENU_SCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class MainMenu:public Layer
{
public:
	static cocos2d::Scene* createScene();
	MainMenu();
	~MainMenu();
	virtual bool init();
	CREATE_FUNC(MainMenu);
private:
	void StepOff(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);//ºóÍË
	void selectedItemEvent(Ref *pSender, ui::ListView::EventType type);
	void ExitGame(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif