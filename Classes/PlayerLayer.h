#ifndef __PLAYERLAYER_H__
#define __PLAYERLAYER_H__

#include "cocos2d.h";
#include "SnakeBody.h"
#include "AppConfig.h"

USING_NS_CC;


class PlayerLayer : public CCLayer
{
public:
	PlayerLayer();
	~PlayerLayer();

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	CREATE_FUNC(PlayerLayer);

	void setDirection(const Direction direction){ m_direction = direction; }
	Direction getDirection() const { return m_direction; }

	void start();
private:
	CCSpriteBatchNode* m_spriteBatchNode;
	CCArray* m_bodies;
	CCTMXTiledMap* m_map;
	Direction m_direction;
	CCTMXLayer* m_backgroundLayer;

private:
	void addBody(const CCPoint& position);
	void updateSnakePosCallback(float dt);
	void move();
	void updateBodyPosition(SnakeBody* body, const CCPoint position);
	void died();
	void eat();
	CCPoint getEatBeanPosition();
};


#endif __PLAYERLAYER_H__