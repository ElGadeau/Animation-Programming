#include <Skeleton.h>
#include <Engine.h>

void Animation::Skeleton::Init()
{
    SetBones();
    CalculateBoneWorld();
}

void Animation::Skeleton::SetBones()
{
    //setting base data for bones
    for (int i = 0; i < GetSkeletonBoneCount() - 7; ++i)
    {
        const char* name = GetSkeletonBoneName(i);
        int index = i;
        int pIndex = GetSkeletonBoneParentIndex(i);

        m_bones.emplace_back(index, pIndex, name);

        float X, Y, Z, qW, qX, qY, qZ;
        GetSkeletonBoneLocalBindTransform(i, X, Y, Z, qW, qX, qY, qZ);
        const Matrix4F localTrs = Matrix4F::CreateTransformation(Vector3F{ X, Y, Z }, Quaternion{ qX, qY, qZ, qW }, Vector3F::one);

        m_bones[i].m_TPoseLocalMatrix = localTrs;
    }
}

void Animation::Skeleton::CalculateBoneWorld()
{
    //setting world matrix for bones
    for (auto& m_bone : m_bones)
    {
        if (m_bone.m_parentIndex == -1)
        {
            m_bone.m_TPoseWorldMatrix = m_bone.m_TPoseLocalMatrix;
        }
        else
        {
            const Matrix4F worldTrs = m_bones[m_bone.m_parentIndex].m_TPoseWorldMatrix * m_bone.m_TPoseLocalMatrix;
            m_bone.m_TPoseWorldMatrix = worldTrs;
        }
    }
}

void Animation::Skeleton::Animate(const char* p_animation, int p_frame)
{
    float matrixData[976];

    for (int i = 0; i < m_bones.size(); ++i)
    {
        float X, Y, Z, qW, qX, qY, qZ;
        GetAnimLocalBoneTransform(p_animation, i, p_frame, X, Y, Z, qW, qX, qY, qZ);

        Vector3F pos{ X, Y, Z };
        Quaternion rot{ qX, qY, qZ, qW };

        Matrix4F localAnim = Matrix4F::CreateTransformation(pos, rot, Vector3F::one);

        if (m_bones[i].m_parentIndex >= 0)
            m_bones[i].m_worldMatrix = (m_bones[m_bones[i].m_parentIndex].m_worldMatrix * m_bones[i].m_TPoseLocalMatrix * localAnim);
        else
            m_bones[i].m_worldMatrix = (m_bones[i].m_TPoseLocalMatrix * localAnim);

        Matrix4F inverseWorld = m_bones[i].m_worldMatrix * Matrix4F::Inverse(m_bones[i].m_TPoseWorldMatrix);

        for (int j = 0; j < 16; ++j)
        {
            matrixData[(i * 16) + j] = inverseWorld[j];
        }
    }

    SetSkinningPose(matrixData, m_bones.size());
}

void Animation::Skeleton::DrawSkeleton()
{
    Bone::DrawBone(m_bones);
}

void Animation::Skeleton::DrawRestingSkeleton()
{
    Bone::DrawTPose(m_bones);
}
