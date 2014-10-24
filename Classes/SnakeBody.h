#ifndef __SNAKEBODY_H__
#define __SNAKEBODY_H__

#include "cocos2d.h";
USING_NS_CC;

class SnakeBody : public CCSprite
{
public:
	virtual bool init();
	CREATE_FUNC(SnakeBody);

	void setMapPosition(const CCPoint& position);
	CCPoint getMapPosition() const;
private:
	CCPoint m_mapPos;
};

#endif __SNAKEBODY_H__