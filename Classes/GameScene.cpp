#include "GameScene.h"

bool GameScene::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		m_map = CCTMXTiledMap::create("map/map.tmx");
		addChild(m_map);

		bRet = true;
	} while (0);

	return bRet;
}

CCScene* GameScene::scene()
{
	CCScene* s = CCScene::create();
	s->addChild(GameScene::create());
	return s;
}