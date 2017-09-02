#ifndef _MENUOPTIONLAYER_
#define _MENUOPTIONLAYER_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class MenuOptionLayer:public Layer
{
public:
	static cocos2d::Scene* createScene();
	MenuOptionLayer();
	~MenuOptionLayer();
	virtual bool init();
	CREATE_FUNC(MenuOptionLayer);
private:
	void StepOff(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void MainMenu(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	
};
#endif 
