#include "StartScene.h"
#include "GameScene.h"
#include "AppConfig.h"

bool StartScene::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCLabelTTF* title_label = CCLabelTTF::create("Snake", "fonts/aa.ttf", 60);
		title_label->setColor(LABEL_COLOR);
		title_label->setPosition(ccp(size.width / 2, size.height * 0.7));
		addChild(title_label);
		

		CCLabelTTF* start_label = CCLabelTTF::create("Tap to start", "fonts/aa.ttf", 45);
		start_label->setColor(LABEL_COLOR);

		CCBlink* blink = CCBlink::create(2, 1);
		CCActionInterval* action = CCSequence::create(blink, NULL);
		start_label->runAction(CCRepeatForever::create(action));

		CCMenuItemLabel* start_menu = CCMenuItemLabel::create(start_label, this, menu_selector(StartScene::menuStartCallback));
		start_menu->setPosition(ccp(size.width / 2, size.height * 0.4));

		CCMenu* menu = CCMenu::create(start_menu, NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);
		bRet = true;
	} while (0);

	return bRet;
}

CCScene* StartScene::scene()
{
	CCScene* s = CCScene::create();
	s->addChild(StartScene::create());
	s->setTag(STARTSCENE_TAG);
	return s;
}

void StartScene::menuStartCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, GameScene::scene()));
}