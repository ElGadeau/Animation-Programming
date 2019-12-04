// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"
#include <GPM/GPM.h>
#include <Skeleton.h>

class CSimulation : public ISimulation
{
    Animation::Skeleton MySkeleton;

	virtual void Init() override
	{
        MySkeleton.Init();
	}

	virtual void Update(float frameTime) override
	{
        static float m_time = 0;
        m_time += frameTime * 30;
        // MySkeleton.Animate("ThirdPersonWalk.anim", static_cast<int>(m_time) % GetAnimKeyCount("ThirdPersonWalk.anim"));
        MySkeleton.Animate("ThirdPersonRun.anim", static_cast<int>(m_time) % GetAnimKeyCount("ThirdPersonRun.anim"));
        MySkeleton.DrawSkeleton();

        DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);
        DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);
        DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);


    return 0;
}