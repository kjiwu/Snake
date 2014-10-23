#include "Mouse.h"

bool Mouse::init()
{
	bool bRet = false;

	do
	{
		CC_BREAK_IF(!CCSprite::init());
		srand(time(0));

		Animal::init_animal(1, 10, dLeft | dRight, 1, CCRANDOM_0_1() * 100, dLeft);
		this->initWithFile("mouse.png");

		bRet = true;
	} while (0);

	return bRet;
}

void Mouse::move()
{
	CCPoint currentPos = getPosition();

	switch (m_direction)
	{
	case dLeft:
		
		break;
	case dRight:

		break;
	}
}

void Mouse::escape()
{
	int rate = CCRANDOM_0_1() * 100;
	if (rate == m_escapeRate)
	{
		kill(true);
	}
}

void Mouse::kill(bool is_escape)
{
	if (is_escape)
	{

	}
	else
	{
		
	}
}