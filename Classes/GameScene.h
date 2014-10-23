#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);

	static CCScene* scene();

private:
	CCTMXTiledMap* m_map;
};

#endif __GAMESCENE_H__