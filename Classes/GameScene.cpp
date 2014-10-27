#include "GameScene.h"

bool GameScene::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_map = CCTMXTiledMap::create("map/map.tmx");
		addChild(m_map, MAPLAYER_TAG, MAPLAYER_TAG);

		m_touchLayer = TouchLayer::create();
		addChild(m_touchLayer, TOUCHLAYER_TAG, TOUCHLAYER_TAG);

		m_player = PlayerLayer::create();
		addChild(m_player, PLAYERLAYER_TAG, PLAYERLAYER_TAG);

		m_menuLayer = MenuLayer::create();
		addChild(m_menuLayer, MENULAYER_TAG, MENULAYER_TAG);

		m_beanLayer = BeanLayer::create();
		addChild(m_beanLayer, BEANLAYER_TAG, BEANLAYER_TAG);

		bRet = true;
	} while (0);

	return bRet;
}

CCScene* GameScene::scene()
{
	CCScene* s = CCScene::create();
	s->addChild(GameScene::create());
	s->setTag(GAMESCENE_TAG);
	return s;
}