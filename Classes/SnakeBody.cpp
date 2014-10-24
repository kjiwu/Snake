#include "SnakeBody.h"

bool SnakeBody::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCSprite::init());
		initWithFile("body.png");
		bRet = true;
	} while (0);

	return bRet;
}

void SnakeBody::setMapPosition(const CCPoint& position)
{
	m_mapPos = position;
}

CCPoint SnakeBody::getMapPosition() const
{
	return m_mapPos;
}