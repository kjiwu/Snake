#ifndef __TOUCHLAYER_H__
#define __TOUCHLAYER_H__

#include "cocos2d.h";

USING_NS_CC;

class TouchLayer : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(TouchLayer);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCPoint m_prePos, m_currentPos;
	double m_moveDistance;
};

#endif __TOUCHLAYER_H__