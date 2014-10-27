#include "MenuLayer.h"
#include "AppConfig.h"
#include "PlayerLayer.h"
#include "GameScene.h"
#include "BeanLayer.h"

#define SCORE_NODE_TAG 1
#define GAMEOVER_NODE_TAG 2

bool MenuLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCLayer::init());
		m_score = 0;

		initScoreMenu();
		initGameOverMenu();

		bRet = true;
	} while (0);

	return bRet;
}

/*
初始化分数菜单项
*/
void MenuLayer::initScoreMenu()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCNode* score_node = CCNode::create();
	CCLabelTTF* label_score = CCLabelTTF::create("Score:", "fonts/aa.ttf", 40);
	label_score->setPosition(ccp(label_score->getContentSize().width / 2 + 30,
		size.height - label_score->getContentSize().height / 2 - 30));
	score_node->addChild(label_score);

	m_labelValue = CCLabelTTF::create("0", "fonts/aa.ttf", 40);
	m_labelValue->setAnchorPoint(ccp(0, 0.5));
	m_labelValue->setPosition(ccp(label_score->getContentSize().width + 60,
		size.height - label_score->getContentSize().height / 2 - 30));
	score_node->addChild(m_labelValue);

	addChild(score_node, SCORE_NODE_TAG, SCORE_NODE_TAG);
}

/*
初始化游戏结束菜单项
*/
void MenuLayer::initGameOverMenu()
{
	do
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCNode* node = CCNode::create();
		node->setVisible(false);
		node->setPosition(ccp(node->getPositionX(), -node->getContentSize().height / 2));

		CCLabelTTF* title_label = CCLabelTTF::create("Game Over", "fonts/aa.ttf", 60);
		title_label->setPosition(ccp(size.width / 2, size.height * 0.6));
		node->addChild(title_label);


		CCMenuItemImage* restart_menu = CCMenuItemImage::create("restart.png", "restart.png", this, menu_selector(MenuLayer::gameRestartCallback));
		restart_menu->setPosition(ccp(size.width / 2, size.height * 0.4));

		CCMenu* menu = CCMenu::create(restart_menu, NULL);
		menu->setPosition(CCPointZero);
		node->addChild(menu);

		addChild(node, GAMEOVER_NODE_TAG, GAMEOVER_NODE_TAG);
	} while (0);
}

void MenuLayer::showGameOverMenu()
{
	do
	{
		CCNode* node = dynamic_cast<CCNode*>(getChildByTag(GAMEOVER_NODE_TAG));
		CC_BREAK_IF(!node);

		node->setVisible(true);
		/*CCActionInterval* moveTo = CCMoveTo::create(2, ccp(node->getPositionX(), 0));
		CCActionInterval* backInOut = CCEaseBackInOut::create(moveTo);
		runAction(backInOut);*/
	} while (0);
}

void MenuLayer::hideGameOverMenu()
{
	do
	{
		CCNode* node = dynamic_cast<CCNode*>(getChildByTag(GAMEOVER_NODE_TAG));
		CC_BREAK_IF(!node);

		node->setVisible(false);
		/*CCActionInterval* moveTo = CCMoveTo::create(2, ccp(node->getPositionX(), 0));
		CCActionInterval* backInOut = CCEaseBackInOut::create(moveTo);
		runAction(backInOut);*/
	} while (0);
}

void MenuLayer::addScore(int value)
{
	m_score += value;
	CCString* str_score = CCString::createWithFormat("%d", m_score);
	m_labelValue->setString(str_score->getCString());
}

void MenuLayer::gameRestartCallback(CCObject* pSender)
{
	hideGameOverMenu();
	m_score = 0;
	m_labelValue->setString("0");

	PlayerLayer* playerLayer = dynamic_cast<PlayerLayer*>(getParent()->getChildByTag(PLAYERLAYER_TAG));
	playerLayer->start();

	BeanLayer* beanLayer = dynamic_cast<BeanLayer*>(getParent()->getChildByTag(BEANLAYER_TAG));
	beanLayer->start();
}