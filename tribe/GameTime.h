#pragma once
#include "pch.h"


class GameTime
{
public:
	GameTime(){}
	~GameTime(){}

	void Update();

private:
	double m_Time;
    double m_Delta;
};