#include <InputManager.h>
#include <iostream>
#include <Windows.h>

InputManager::InputManager()
{
    //init numbers
    for (char i = '0'; i <= '9'; ++i)
    {
        keys.try_emplace(i, Null);
    }

    //init letters
    for (char i = 'A'; i <= 'Z'; ++i)
    {
        keys.try_emplace(i, Null);
    }

    keys.try_emplace(VK_LEFT, Null);
    keys.try_emplace(VK_UP, Null);
    keys.try_emplace(VK_RIGHT, Null);
    keys.try_emplace(VK_DOWN, Null);
}

bool InputManager::GetKey(char p_key)
{
    char key;
    if (!(key = keys.find(p_key)->first))
    {
        std::cout << "COULD NOT FIND KEY\N";
        return false;
    }

    if (GetKeyState(key) < 0)
    {
        return true;
    }
    return false;
}

bool InputManager::GetKeyDown(char p_key)
{
    char key;
    if (!(key = keys.find(p_key)->first))
    {
        std::cout << "COULD NOT FIND KEY\N";
        return false;
    }

    if (GetKeyState(key) < 0 && keys.find(key)->second != Completed)
    {
        keys.find(key)->second = KeyDown;
    }
    if ((keys.find(key)->second) == KeyDown)
    {
        keys.find(key)->second = Completed;
        return true;
    }
    if (GetKeyState(key) >= 0)
    {
        keys.find(key)->second = Null;
    }
    return false;
}

bool InputManager::GetKeyUp(char p_key)
{
    char key;
    if (!(key = keys.find(p_key)->first))
    {
        std::cout << "COULD NOT FIND KEY\N";
        return false;
    }

    if (GetKeyState(key) < 0 && keys.find(key)->second != Completed)
    {
        keys.find(key)->second = KeyDown;
    }
    if ((keys.find(key)->second) == KeyDown)
    {
        keys.find(key)->second = KeyUp;
    }
    if (GetKeyState(key) >= 0 && keys.find(key)->second == KeyUp)
    {
        keys.find(key)->second = Null;
        return true;
    }
    return false;
}