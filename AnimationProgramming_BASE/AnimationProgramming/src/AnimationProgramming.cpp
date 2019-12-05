// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Engine.h>
#include <Simulation.h>
#include <Skeleton.h>
#include <Windows.h>
#include <InputManager.h>

class CSimulation : public ISimulation
{
    Animation::Skeleton MySkeleton;
    InputManager inMan;

	virtual void Init() override
	{
        MySkeleton.Init();
        MySkeleton.AddAnimation("ThirdPersonWalk.anim");
        MySkeleton.AddAnimation("ThirdPersonRun.anim");
	}

	virtual void Update(float frameTime) override
	{

        static int state = 0;
        static float m_time = 0;
        static float speed = 5;
        m_time += frameTime * speed;

        if (inMan.GetKey('Q'))
        {
            std::cout << "Q hold\n";
        }

        if (inMan.GetKeyDown('E'))
        {
            std::cout << "E pressed\n";
        }

        if (inMan.GetKeyUp('R'))
        {
            std::cout << "R released\n";
        }

        switch(state)
        {
        case 0:
            MySkeleton.Animate("ThirdPersonWalk.anim", m_time);
            break;
        case 1:
            MySkeleton.Animate("ThirdPersonRun.anim", m_time);
            break;
        default:
            break;
        }

            MySkeleton.Animate("ThirdPersonWalk.anim", m_time);
        // std::cout << "time : " << m_time << '\n';
        // MySkeleton.DrawSkeleton();

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