#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#define STARTSCENE_TAG 1

class StartScene : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(StartScene);

	static CCScene* scene();

	void menuStartCallback(CCObject* pSender);
};

#endif __STARTSCENE_H__