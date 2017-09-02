#include "MenuOptionLayer.h"
#include "Header.h"
MenuOptionLayer::MenuOptionLayer(){}
MenuOptionLayer::~MenuOptionLayer(){}
bool MenuOptionLayer::init(){
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	this->setVisible(false);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto colorlayer=LayerColor::create(Color4B(Color4B(250,250,250,255)));
	this->addChild(colorlayer);

	auto MenuButton = ui::Button::create();
	MenuButton->setTitleText("MainMenu");
	MenuButton->setTitleFontName("fonts/Marker Felt.ttf");
	MenuButton->setTitleColor(Color3B::BLACK);
	MenuButton->setTitleFontSize(30);
	MenuButton->setZoomScale(0.3f);
	MenuButton->addTouchEventListener(CC_CALLBACK_2(MenuOptionLayer::MainMenu,this));
	MenuButton->setPressedActionEnabled(true);
	MenuButton->setPosition(Vec2(origin.x+visibleSize.width/2-200,origin.y+visibleSize.height*0.2));
	colorlayer->addChild(MenuButton);

	auto BackButton = ui::Button::create();
	BackButton->setTitleText("BACK");
	BackButton->setTitleFontName("fonts/Marker Felt.ttf");
	BackButton->setTitleColor(Color3B::BLACK);
	BackButton->setTitleFontSize(30);
	BackButton->setZoomScale(0.3f);
	BackButton->addTouchEventListener(CC_CALLBACK_2(MenuOptionLayer::StepOff,this));
	BackButton->setPressedActionEnabled(true);
	BackButton->setPosition(Vec2(origin.x+visibleSize.width/2+200,origin.y+visibleSize.height*0.2));
	colorlayer->addChild(BackButton);

	return true;
}
void MenuOptionLayer::StepOff(Ref *pSender, cocos2d::ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		this->setVisible(false);
		Director::getInstance()->resume();
	}
}
void MenuOptionLayer::MainMenu(Ref *pSender, ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MainMenu::createScene());
	}
}