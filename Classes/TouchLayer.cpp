#include "TouchLayer.h"

#define MOVE_MIN_DISTANCE 25;

bool TouchLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCLayer::init());
		m_moveDistance = MOVE_MIN_DISTANCE;
		bRet = true;
	} while (0);

	return bRet;
}

void TouchLayer::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void TouchLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_prePos = pTouch->getLocation();
	return true;
}

void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	m_currentPos = pTouch->getLocation();
}

void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint subPos = ccpSub(m_currentPos, m_prePos);
	if (fabs(subPos.x) > fabs(subPos.y))
	{
		if (subPos.x >= m_moveDistance)
		{
			CCLOG("Right");
		}

		if (subPos.x <= -m_moveDistance)
		{
			CCLOG("Left");
		}
	}
	else
	{
		if (subPos.y >= m_moveDistance)
		{
			CCLOG("Up");
		}

		if (subPos.y <= -m_moveDistance)
		{
			CCLOG("Down");
		}
	}
}