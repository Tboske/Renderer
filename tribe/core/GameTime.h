#pragma once
#include "pch.h"


class GameTime
{
public:
	GameTime() = default;
	~GameTime() = default;

	double GetDeltaTime() const { return m_Delta; }
	double GetTotalTime() const { return m_Time; }
	int GetFps() const { return m_Fps; }
	void SetTargetFps(int fps) { m_FpsTarget = fps; }

private:
	double m_Time;
    double m_Delta;
	int m_Fps;
	int m_FpsTarget = 240;

	friend class Tribe;
	double GetSleepTime() const;
	void Update();
};