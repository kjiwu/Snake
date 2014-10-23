#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Animal.h"
#include "cocos2d.h"

USING_NS_CC;

class Mouse : public Animal, public CCSprite
{
public:
	virtual bool init();
	CREATE_FUNC(Mouse);

	virtual void move();
	virtual void escape();
	virtual void kill(bool is_escape = false);

	virtual void update(float dt);
};

#endif __MOUSE_H__