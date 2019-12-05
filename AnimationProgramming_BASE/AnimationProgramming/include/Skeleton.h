#pragma once
#include <Bone.h>
#include <unordered_map>
#include <AnimationData.h>

namespace Animation
{
    class Skeleton
    {
    public:
        void Init();
        void SetBones();
        void CalculateBoneWorld();

        void AddAnimation(const char* p_name);
        void Animate(const char* p_animation, float p_deltaTime);

        void DrawSkeleton();
        void DrawRestingSkeleton();

    private:
        std::vector<Bone> m_bones;
        std::unordered_map<std::string, AnimationData> m_animData;
    };
}
