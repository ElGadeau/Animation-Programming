#include <InputHandler.h>
#include <iostream>

InputHandler::InputHandler()
{
    m_inputManager = new InputManager;
}

InputHandler::~InputHandler()
{
    delete m_inputManager;
}

void InputHandler::ProcessInputs(Animation::Skeleton& p_skeleton) const
{
    if (m_inputManager->GetKeyDown('1'))
    {
        std::cout << "Playing waling animation\n\n";
        p_skeleton.m_animState = 0;
    }
    if (m_inputManager->GetKeyDown('2'))
    {
        std::cout << "Playing running animation\n\n";
        p_skeleton.m_animState = 1;
    }

    if (m_inputManager->GetKeyDown(0x26))
    {
        p_skeleton.m_speed += 5;
        std::cout << "Increase speed by 5 units\n";
        std::cout << "New speed : " << p_skeleton.m_speed << "\n\n";
    }
    if (m_inputManager->GetKeyDown(0x28))
    {
        p_skeleton.m_speed -= 5;
        if (p_skeleton.m_speed < 0)
            p_skeleton.m_speed = 0;
        std::cout << "Decrease speed by 5 units\n";
        std::cout << "New speed : " << p_skeleton.m_speed << "\n\n";
    }
}
