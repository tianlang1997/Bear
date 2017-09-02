#ifndef _WELCOME_SCENE_
#define _WELCOME_SCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class Welcome:public Layer
{
public:
	static cocos2d::Scene* createScene();
	Welcome();
	~Welcome();
	bool init();
	CREATE_FUNC(Welcome);
	void ShowGameModel();
private:
	void SimpleModel(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void NormalModel(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void HardModel(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void ShowMainMenu();
};


#endif