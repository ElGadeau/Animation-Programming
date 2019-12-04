#pragma once
#include <Bone.h>

namespace Animation
{
    class Skeleton
    {
    public:
        void Init();
        void SetBones();
        void CalculateBoneWorld();

        void Animate(const char* p_animation, int p_frame);

        void DrawSkeleton();
        void DrawRestingSkeleton();

        private:
        std::vector<Bone> m_bones;
    };
}
