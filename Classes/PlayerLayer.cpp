#include "PlayerLayer.h"
#include "GameScene.h"

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
		m_direction = dLeft;

		m_spriteBatchNode = CCSpriteBatchNode::create("body.png");
		addChild(m_spriteBatchNode);

		bRet = true;
	} while (0);

	return bRet;
}

void PlayerLayer::onEnter()
{
	CCLayer::onEnter();

	do
	{
		GameScene* gameScene = dynamic_cast<GameScene*>(this->getParent());
		CC_BREAK_IF(!gameScene);

		m_map = dynamic_cast<CCTMXTiledMap*>(gameScene->getChildByTag(MAPLAYER_TAG));
		CC_BREAK_IF(!m_map);

		CCSize map_size = m_map->getMapSize();
		for (int i = 3; i > 0; i--)
		{
			addBody(ccp(i, map_size.height / 2));
		}

		schedule(schedule_selector(PlayerLayer::updateSnakePosCallback), 1.0f);
	} while (0);
}

void PlayerLayer::addBody(const CCPoint& position)
{
	SnakeBody* body = SnakeBody::create();
	body->setMapPosition(position);
	CCTMXLayer* backgroundLayer = m_map->layerNamed("Background");
	body->setPosition(backgroundLayer->positionAt(position));
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
}

void PlayerLayer::updateBodyPosition(SnakeBody* body, const CCPoint position)
{
	body->setMapPosition(position);
	CCTMXLayer* backgroundLayer = m_map->layerNamed("Background");
	body->setPosition(backgroundLayer->positionAt(position));
}

void PlayerLayer::updateSnakePosCallback(float dt)
{
	move();
}