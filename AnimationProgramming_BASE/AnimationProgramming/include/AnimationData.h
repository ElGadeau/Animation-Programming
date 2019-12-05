#pragma once
#include <GPM/GPM.h>
// #include <vector>
#include <unordered_map>

namespace Animation
{
    struct AnimationData
    {
    private:
        void LoadAnimation(std::string& p_animation);

    public:
        AnimationData() = default;
        AnimationData(const char* p_name);

        std::string m_name;
        std::vector<std::vector<std::pair<Vector3F, Quaternion>>> m_data;
    };
}
