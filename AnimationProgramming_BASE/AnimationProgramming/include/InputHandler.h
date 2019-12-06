#pragma once
#include <InputManager.h>
#include <Skeleton.h>

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void ProcessInputs(Animation::Skeleton& p_skeleton);

private:
    InputManager* m_inputManager;
};
