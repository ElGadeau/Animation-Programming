#include <Bone.h>

Animation::Bone::Bone(int p_index, int p_parentIndex, const char* p_name) : m_index(p_index), m_parentIndex(p_parentIndex), m_name(p_name)
{
    m_parent = nullptr;
}

Animation::Bone::Bone(Bone& p_bone)
{
    m_index = p_bone.m_index;
    m_parentIndex = p_bone.m_parentIndex;
    m_name = p_bone.m_name;
    m_worldMatrix = p_bone.m_worldMatrix;
    m_TPoseLocalMatrix = p_bone.m_TPoseLocalMatrix;
    m_TPoseWorldMatrix = p_bone.m_TPoseWorldMatrix;
    m_parent = p_bone.m_parent;
}

Animation::Bone::Bone(Bone&& p_bone)
{
    m_index = p_bone.m_index;
    m_parentIndex = p_bone.m_parentIndex;
    m_name = p_bone.m_name;
    m_worldMatrix = p_bone.m_worldMatrix;
    m_TPoseLocalMatrix = p_bone.m_TPoseLocalMatrix;
    m_TPoseWorldMatrix = p_bone.m_TPoseWorldMatrix;
    m_parent = p_bone.m_parent;
}

Vector3F Animation::Bone::GetWorldPosition() const
{
    const float x = m_worldMatrix[3];
    const float y = m_worldMatrix[7];
    const float z = m_worldMatrix[11];

    return { x, y, z };
}

void Animation::Bone::DrawBone(std::vector<Bone>& p_bones)
{
    for (int i = 0; i < p_bones.size(); ++i)
    {
        if (p_bones[i].m_parentIndex == -1)
            continue;
        DrawLine(p_bones[p_bones[i].m_parentIndex].GetWorldPosition().x, p_bones[p_bones[i].m_parentIndex].GetWorldPosition().y, p_bones[p_bones[i].m_parentIndex].GetWorldPosition().z,
            p_bones[i].GetWorldPosition().x, p_bones[i].GetWorldPosition().y, p_bones[i].GetWorldPosition().z, 0, 0, 0);
    }
}

void Animation::Bone::DrawTPose(std::vector<Bone>& p_bones)
{
    for (int i = 0; i < p_bones.size(); ++i)
    {
        if (p_bones[i].m_parentIndex == -1)
            continue;

        DrawLine(p_bones[p_bones[i].m_parentIndex].m_TPoseWorldMatrix[3], p_bones[p_bones[i].m_parentIndex].m_TPoseWorldMatrix[7], p_bones[p_bones[i].m_parentIndex].m_TPoseWorldMatrix[11],
            p_bones[i].m_TPoseWorldMatrix[3], p_bones[i].m_TPoseWorldMatrix[7], p_bones[i].m_TPoseWorldMatrix[11], 0, 0, 0);
    }
}
