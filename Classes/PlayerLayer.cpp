#include "PlayerLayer.h"
#include "GameScene.h"
#include "BeanLayer.h"
#include "MenuLayer.h"

PlayerLayer::PlayerLayer()
{
	m_bodies = CCArray::create();
	m_bodies->retain();
}

PlayerLayer::~PlayerLayer()
{
	m_bodies->release();
	m_bodies = NULL;
}

bool PlayerLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCLayer::init());

		m_spriteBatchNode = CCSpriteBatchNode::create("body.png");
		addChild(m_spriteBatchNode);

		bRet = true;
	} while (0);

	return bRet;
}

void PlayerLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();

	do
	{
		GameScene* gameScene = dynamic_cast<GameScene*>(this->getParent());
		CC_BREAK_IF(!gameScene);

		m_map = dynamic_cast<CCTMXTiledMap*>(gameScene->getChildByTag(MAPLAYER_TAG));
		CC_BREAK_IF(!m_map);

		m_backgroundLayer = m_map->layerNamed("Background");
		start();

	} while (0);
}

void PlayerLayer::start()
{
	m_direction = dLeft;

	CCSize map_size = m_map->getMapSize();
	m_bodies->removeAllObjects();
	m_spriteBatchNode->removeAllChildren();

	for (int i = 4; i > 1; i--)
	{
		addBody(ccp(i, map_size.height / 2));
	}

	schedule(schedule_selector(PlayerLayer::updateSnakePosCallback), 0.5f);
}

void PlayerLayer::addBody(const CCPoint& position)
{
	SnakeBody* body = SnakeBody::create();
	body->setMapPosition(position);
	body->setPosition(m_backgroundLayer->positionAt(position));
	m_spriteBatchNode->addChild(body);
	m_bodies->addObject(body);
}

void PlayerLayer::move()
{
	for (int i = m_bodies->count() - 1; i > 0; i--)
	{
		SnakeBody* pre_body = dynamic_cast<SnakeBody*>(m_bodies->objectAtIndex(i - 1));
		SnakeBody* curr_body = dynamic_cast<SnakeBody*>(m_bodies->objectAtIndex(i));
		updateBodyPosition(curr_body, pre_body->getMapPosition());
	}

	SnakeBody* header = dynamic_cast<SnakeBody*>(m_bodies->objectAtIndex(0));
	CCPoint header_pos = header->getMapPosition();
	switch (m_direction)
	{
	case dLeft:
	{
		header_pos.x += 1;
		break;
	}
	case dRight:
	{
		header_pos.x -= 1;
		break;
	}
	case dUp:
	{
		header_pos.y -= 1;
		break;
	}
	case dDown:
	{
		header_pos.y += 1;
		break;
	}
	}
	updateBodyPosition(header, header_pos);

	died();
	eat();
}

void PlayerLayer::updateBodyPosition(SnakeBody* body, const CCPoint position)
{
	body->setMapPosition(position);
	body->setPosition(m_backgroundLayer->positionAt(position));
}

void PlayerLayer::updateSnakePosCallback(float dt)
{
	move();
}

void PlayerLayer::died()
{
	SnakeBody* header = dynamic_cast<SnakeBody*>(m_bodies->objectAtIndex(0));
	CCPoint mapPos = header->getMapPosition();
	if ((1 == mapPos.x || mapPos.x == m_map->getMapSize().height) ||
		(1 == mapPos.y || mapPos.y == m_map->getMapSize().width))
	{
		MenuLayer* menuLayer = dynamic_cast<MenuLayer*>(getParent()->getChildByTag(MENULAYER_TAG));
		menuLayer->showGameOverMenu();

		BeanLayer* beanLayer = dynamic_cast<BeanLayer*>(getParent()->getChildByTag(BEANLAYER_TAG));
		beanLayer->stop();

		CCLOG("death");
		unschedule(schedule_selector(PlayerLayer::updateSnakePosCallback));
		return;
	}

	if (m_bodies->count() >= 5)
	{
		for (int i = 4; i < m_bodies->count(); i++)
		{
			SnakeBody* body = dynamic_cast<SnakeBody*>(m_bodies->objectAtIndex(i));
			if (body->boundingBox().intersectsRect(header->boundingBox()))
			{
				MenuLayer* menuLayer = dynamic_cast<MenuLayer*>(getParent()->getChildByTag(MENULAYER_TAG));
				menuLayer->showGameOverMenu();

				BeanLayer* beanLayer = dynamic_cast<BeanLayer*>(getParent()->getChildByTag(BEANLAYER_TAG));
				beanLayer->stop();

				CCLOG("death");
				unschedule(schedule_selector(PlayerLayer::updateSnakePosCallback));
				break;
			}
		}
	}
}

void PlayerLayer::eat()
{
	do
	{
		GameScene* gameScene = dynamic_cast<GameScene*>(this->getParent());
		CC_BREAK_IF(!gameScene);

		BeanLayer* beanLayer = dynamic_cast<BeanLayer*>(gameScene->getChildByTag(BEANLAYER_TAG));
		CC_BREAK_IF(!beanLayer);

		MenuLayer* menuLayer = dynamic_cast<MenuLayer*>(gameScene->getChildByTag(MENULAYER_TAG));
		CC_BREAK_IF(!menuLayer);

		CCRect rect = beanLayer->getBeanPos();
		SnakeBody* header = dynamic_cast<SnakeBody*>(m_bodies->objectAtIndex(0));
		if (header->boundingBox().intersectsRect(rect))
		{
			beanLayer->start();
			menuLayer->addScore(SCORE_VALUE);

			SnakeBody* tail = dynamic_cast<SnakeBody*>(m_bodies->objectAtIndex(m_bodies->count() - 1));
			CCPoint position = tail->getMapPosition();
			position.x -= 1;
			addBody(position);
		}

	} while (0);
}