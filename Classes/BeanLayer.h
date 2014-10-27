#ifndef __BEAN_H__
#define __BEAN_H__

#include "cocos2d.h"

USING_NS_CC;

#define SCORE_VALUE 1

class BeanLayer : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(BeanLayer);

	void start();
	void onEnterTransitionDidFinish();
	CCRect getBeanPos() const { return m_bean->boundingBox(); }
	void stop();
private:
	CCTMXTiledMap* m_map;
	CCSprite* m_bean;
	CCTMXLayer* m_backgroundLayer;

	CCPoint getRandPos();

	void disappearCallback(float dt);
};

#endif __BEAN_H__