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
	����
	ÿ�ֶ��ﶼ��һ���ļ�������
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
	int m_score; //ÿ�ֶ������Լ��ķ���
	float m_speed; //ÿ�ֶ����ƶ����ٶ�
	int m_canMoveDirection; //ÿ�ֶ�������ƶ��ķ���ͨ������������
	int m_moveCell; //ÿ�ֶ���һ���ƶ��ľ���
	Animal_Direction m_direction; //���ﵱǰ���ƶ�����
	int m_escapeRate; //����ÿ�ֶ���ʱ���������һ����������������ʱ������
};


#endif __ANIMAL_H__