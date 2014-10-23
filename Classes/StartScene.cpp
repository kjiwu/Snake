#include "StartScene.h"
#include "GameScene.h"

bool StartScene::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCMenuItemLabel* lable_menu = CCMenuItemLabel::create(CCLabelTTF::create("Start", "Consolas", 30), this, menu_selector(StartScene::menuStartCallback));
		lable_menu->setPosition(ccp(size.width / 2, size.height * 0.7));

		CCMenu* menu = CCMenu::create(lable_menu, NULL);
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
	return s;
}

void StartScene::menuStartCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, GameScene::scene()));
}