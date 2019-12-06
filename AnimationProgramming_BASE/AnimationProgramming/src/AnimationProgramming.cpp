// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Engine.h>
#include <Simulation.h>
#include <Skeleton.h>
#include <Windows.h>
#include <InputHandler.h>

class CSimulation : public ISimulation
{
    Animation::Skeleton MySkeleton;
    InputHandler inHand;

	virtual void Init() override
	{
        MySkeleton.Init();
        MySkeleton.AddAnimation("ThirdPersonWalk.anim");
        MySkeleton.AddAnimation("ThirdPersonRun.anim");
	}

    virtual void Update(float frameTime) override
    {
        static float m_time = 0;
        m_time += frameTime;
        inHand.ProcessInputs(MySkeleton);
        MySkeleton.Animate(m_time);
    }
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);


    return 0;
}