#include "MenuLayer.h"
#include "AppConfig.h"

#define SCORE_NODE_TAG 1

bool MenuLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCLayer::init());
		m_score = 0;

		initScoreMenu();

		bRet = true;
	} while (0);

	return bRet;
}

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

void MenuLayer::addScore(int value)
{
	m_score += value;
	CCString* str_score = CCString::createWithFormat("%d", m_score);
	m_labelValue->setString(str_score->getCString());
}