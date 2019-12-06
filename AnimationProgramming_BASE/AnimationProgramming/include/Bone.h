#pragma once
#include <string>
#include <GPM/GPM.h>
#include "Engine.h"

namespace Animation
{
    struct Bone
    {
    public:
        Bone() = default;
        Bone(int p_index, int p_parentIndex, const char* p_name);
        Bone(Bone& p_bone);
        Bone(Bone&& p_bone) noexcept;

        Vector3F GetWorldPosition() const;

        static void DrawBone(std::vector<Bone>& p_bones);
        static void DrawTPose(std::vector<Bone>& p_bones);

        int m_index;
        int m_parentIndex;
        std::string m_name;


        Bone* m_parent;
        Matrix4F m_worldMatrix;
        Matrix4F m_TPoseLocalMatrix;
        Matrix4F m_TPoseWorldMatrix;
    };
}
