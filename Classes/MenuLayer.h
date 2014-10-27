#ifndef __MENULAYER_H__
#define __MENULAYER_H__

#include "cocos2d.h";
USING_NS_CC;

class MenuLayer : public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);


	void addScore(int value);
	void showGameOverMenu();
private:
	CCLabelTTF* m_labelValue;
	int m_score;

	void initScoreMenu();
	void initGameOverMenu();

	void hideGameOverMenu();
	void gameRestartCallback(CCObject* pSender);
};


#endif __MENULAYER_H__