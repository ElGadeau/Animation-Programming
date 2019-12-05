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
    InputManager InputManager;

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
        static bool Gizmos = false;

        if (InputManager.GetKeyDown('1'))
        {
            std::cout << "Playing waling animation\n\n";
            state = 0;
        }
        if (InputManager.GetKeyDown('2'))
        {
            std::cout << "Playing running animation\n\n";
            state = 1;
        }

        if (InputManager.GetKeyDown('G'))
        {
            Gizmos = !Gizmos;
        }

        if (InputManager.GetKeyDown(VK_UP))
        {
            speed += 5;
            std::cout << "Increase speed by 5 units\n";
            std::cout << "New speed : " << speed << "\n\n";
        }
        if (InputManager.GetKeyDown(VK_DOWN))
        {
            speed -= 5;
            if (speed < 0)
                speed = 0;
            std::cout << "Decrease speed by 5 units\n";
            std::cout << "New speed : " << speed << "\n\n";
        }

        switch (state)
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

        if (Gizmos)
        {
            DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);
            DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);
            DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
        }
    }
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);


    return 0;
}