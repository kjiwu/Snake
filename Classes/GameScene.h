#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "TouchLayer.h"
#include "PlayerLayer.h"
#include "MenuLayer.h"
#include "BeanLayer.h"

USING_NS_CC;

#define GAMESCENE_TAG 2


#define MAPLAYER_TAG 0
#define PLAYERLAYER_TAG 1
#define BEANLAYER_TAG 3
#define MENULAYER_TAG 8
#define TOUCHLAYER_TAG 10


class GameScene : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);

	static CCScene* scene();

private:
	CCTMXTiledMap* m_map;
	TouchLayer* m_touchLayer;
	PlayerLayer* m_player;
	MenuLayer* m_menuLayer;
	BeanLayer* m_beanLayer;

};

#endif __GAMESCENE_H__