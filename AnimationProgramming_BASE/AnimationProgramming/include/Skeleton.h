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
        void SetParents();
        void CalculateBoneWorld();

        void AddAnimation(const char* p_name);
        void Animate(const char* p_animation, float p_deltaTime);
        void Animate(float p_deltaTime);

        Matrix4F CalculateNewLocal(const char* p_animation, float& deltaTime, int id);

        void DrawSkeleton();
        void DrawRestingSkeleton();

        unsigned int m_animState;
        float m_speed;
    private:
        std::vector<Bone> m_bones;
        std::unordered_map<std::string, AnimationData> m_animData;
    };
}
