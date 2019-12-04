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
        Bone(int p_index, int p_parentIndex, const char* p_name) : m_index(p_index), m_parentIndex(p_parentIndex), m_name(p_name) {}
        Bone(Bone& p_bone);
        Bone(Bone&& p_bone);

        Vector3F GetWorldPosition();

        static void DrawBone(std::vector<Bone>& p_bones);
        static void DrawTPose(std::vector<Bone>& p_bones);

        int m_index;
        int m_parentIndex;
        std::string m_name;

        Matrix4F m_worldMatrix;
        Matrix4F m_TPoseLocalMatrix;
        Matrix4F m_TPoseWorldMatrix;
    };
}
