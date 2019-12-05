#pragma once
#include <unordered_map>

enum KeyState
{
    Null = -1,
    KeyDown = 1,
    KeyUp = 2,
    Key = 3,
    Completed = 4
};

class InputManager
{
public:
    InputManager();

    bool GetKey(char p_key);
    bool GetKeyDown(char p_key);
    bool GetKeyUp(char p_key);

private:
    std::unordered_map<char, KeyState> keys;
};