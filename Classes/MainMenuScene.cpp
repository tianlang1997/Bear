#include "MainMenuScene.h"
#include "Header.h"
#include "define.h"
MainMenu::MainMenu(){}
MainMenu::~MainMenu(){}
Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto colorlayer=LayerColor::create(Color4B(230,230,230,255));
	this->addChild(colorlayer);
	colorlayer->setContentSize(visibleSize);
	auto label = Label::createWithTTF("Choose The Chapter", "fonts/Marker Felt.ttf", 50);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,	origin.y + visibleSize.height-label->getContentSize().height*0.8));
	label->setColor(Color3B::BLACK);
	colorlayer->addChild(label);

	UserDefault::getInstance()->setIntegerForKey("ChapterNo",1);
	UserDefault::getInstance()->flush();
	auto ChapterNo=UserDefault::getInstance()->getIntegerForKey("ChapterNo",0);//读取指定key的数据,如不存在该数据则返回指定的默认值"default value"

	std::vector<std::string> ChapterPicName;
	for (int i = 0; i < CHAPTER_COUNT; ++i)
	{
		std::string ccstr = StringUtils::format("bear/Chapter/Chapter_%d.png", i);
		ChapterPicName.push_back(ccstr);
	}

	// Create the list view ex
	auto listView = ui::ListView::create();
	// set list view ex direction
	listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	listView->setTouchEnabled(true);
	listView->setBounceEnabled(true);
	listView->setAnchorPoint(Vec2(0.5,0.5));
	listView->setBackGroundImage("bear/Chapter/Chapter_BackGround.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(listView->getBackGroundImageTextureSize());
	listView->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MainMenu::selectedItemEvent, this));
	colorlayer->addChild(listView);

	// add custom item
	for (int i = 0; i < CHAPTER_COUNT; i++)
	{
		
		auto NormalPic=ChapterPicName[i];
		auto SelectPic=ChapterPicName[i];
		if (ChapterNo<i)
		{
			SelectPic="bear/Chapter/Lock.png";
		}
		auto custom_button = ui::Button::create(NormalPic, SelectPic);
		custom_button->setTag(i);
		custom_button->setScale9Enabled(true);
		//custom_button->setContentSize(custom_button->getContentSize());

		auto custom_item = ui::Layout::create();
		custom_item->setContentSize(custom_button->getContentSize());
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		custom_item->addChild(custom_button);
		if (ChapterNo<i)
		{
			//custom_button->setEnabled(false);
		}

		listView->pushBackCustomItem(custom_item);
	}

	// set all items layout gravity
	listView->setGravity(ui::ListView::Gravity::CENTER_VERTICAL);

	// set items margin
	listView->setItemsMargin(2);


	auto ExitButton = ui::Button::create();
	ExitButton->setTitleText("Exit");
	ExitButton->setTitleFontName("fonts/Marker Felt.ttf");
	ExitButton->setTitleColor(Color3B::BLACK);
	ExitButton->setTitleFontSize(30);
	ExitButton->setZoomScale(0.3f);
	ExitButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::ExitGame,this));
	ExitButton->setPressedActionEnabled(true);
	ExitButton->setPosition(Vec2(origin.x+visibleSize.width*0.9,origin.y+visibleSize.height*0.1));
	colorlayer->addChild(ExitButton);
	return true;
}

void MainMenu::StepOff(Ref *pSender, cocos2d::ui::Widget::TouchEventType type){
	if (type==ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->replaceScene(Welcome::createScene());
	}
}
void MainMenu::ExitGame(Ref *pSender, cocos2d::ui::Widget::TouchEventType type){
	Director::getInstance()->end();
}

void MainMenu::selectedItemEvent(Ref *pSender, ui::ListView::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CC_UNUSED_PARAM(listView);
			//CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
			
			break;
		}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ui::ListView* listView = static_cast<ui::ListView*>(pSender);
			CC_UNUSED_PARAM(listView);
			//CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
			auto CharpterNo=listView->getCurSelectedIndex();
			switch (CharpterNo)
			{
				case Charpter::FORETFIGHT:
					Director::getInstance()->replaceScene(ForestFight::createScene());
				break;
				case Charpter::LAKEFIGHT:
					Director::getInstance()->replaceScene(LakeFight::createScene());
					break;
			default:
				break;
			}
			break;
		}
	default:
		break;
	}
}