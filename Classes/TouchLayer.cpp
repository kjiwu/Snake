#include "TouchLayer.h"
#include "GameScene.h"
#include "PlayerLayer.h"

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
	do
	{
		GameScene* gameScene = dynamic_cast<GameScene*>(getParent());
		CC_BREAK_IF(!gameScene);

		PlayerLayer* playerLayer = dynamic_cast<PlayerLayer*>(gameScene->getChildByTag(PLAYERLAYER_TAG));
		CC_BREAK_IF(!playerLayer);

		Direction direction = playerLayer->getDirection();

		CCPoint subPos = ccpSub(m_currentPos, m_prePos);
		if (fabs(subPos.x) > fabs(subPos.y))
		{
			if (subPos.x >= m_moveDistance)
			{
				if (direction == dLeft || direction == dRight)
					return;
				playerLayer->setDirection(dLeft);
			}

			if (subPos.x <= -m_moveDistance)
			{
				if (direction == dLeft || direction == dRight)
					return;

				playerLayer->setDirection(dRight);
			}
		}
		else
		{
			if (subPos.y >= m_moveDistance)
			{
				if (direction == dUp || direction == dDown)
					return;

				playerLayer->setDirection(dUp);
			}

			if (subPos.y <= -m_moveDistance)
			{
				if (direction == dUp || direction == dDown)
					return;

				playerLayer->setDirection(dDown);
			}
		}
	} while (0);
}