#ifndef __ANIMAL_H__
#define __ANIMAL_H__

enum Animal_Direction
{
	dLeft = 1,
	dRight = 2,
	dUp = 4,
	dDown = 8
};

class Animal
{
public:
	virtual void move() = 0;

	/*
	逃跑
	每种动物都有一定的几率逃跑
	*/
	virtual void escape() = 0;

	virtual void kill(bool is_escape) = 0;

	void init_animal(int score, float speed, int canMoveDirection, int moveCell, int escapeRate, Animal_Direction direction)
	{
		m_score = score;
		m_speed = speed;
		m_canMoveDirection = canMoveDirection;
		m_moveCell = moveCell;
		m_escapeRate = escapeRate;
		m_direction = direction;
	}
protected:
	int m_score; //每种动物有自己的分数
	float m_speed; //每种动物移动的速度
	int m_canMoveDirection; //每种动物可以移动的方向，通过与操作来检测
	int m_moveCell; //每种动物一次移动的距离
	Animal_Direction m_direction; //动物当前的移动方向
	int m_escapeRate; //创建每种动物时，随机生成一个数，当满足条件时，逃跑
};


#endif __ANIMAL_H__