#include "BeanLayer.h"
#include "GameScene.h"

#define BEAN_EXIST_TIME 20

bool BeanLayer::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCLayer::init());
		bRet = true;
		srand(time(0));

		m_bean = CCSprite::create("bean.png");
		addChild(m_bean);

	} while (0);

	return bRet;
}

void BeanLayer::onEnterTransitionDidFinish()
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

CCPoint BeanLayer::getRandPos()
{
	CCSize map_size = m_map->getMapSize();
	int x = (rand() % ((int)map_size.width - 2) + 1);
	int y = (rand() % ((int)map_size.height - 2) + 1);

	return ccp(x, y);
}

void BeanLayer::start()
{
	m_bean->setPosition(m_backgroundLayer->positionAt(getRandPos()));
	schedule(schedule_selector(BeanLayer::disappearCallback), BEAN_EXIST_TIME, 1, 0);
}

void BeanLayer::disappearCallback(float dt)
{
	CCBlink* blink = CCBlink::create(2, 3);
	m_bean->runAction(CCSequence::create(blink, CCCallFunc::create(this, callfunc_selector(BeanLayer::start)), NULL));
}

void BeanLayer::stop()
{
	unschedule(schedule_selector(BeanLayer::disappearCallback));
}