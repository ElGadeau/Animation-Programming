#include <Skeleton.h>
#include <Engine.h>

void Animation::Skeleton::Init()
{
    m_animState = 0;
    SetBones();
    SetParents();
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

void Animation::Skeleton::SetParents()
{
    for (int i = 0; i < GetSkeletonBoneCount() - 7; ++i)
    {
        m_bones[i].parent = &m_bones[m_bones[i].m_parentIndex];
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
            const Matrix4F worldTrs = m_bone.parent->m_TPoseWorldMatrix * m_bone.m_TPoseLocalMatrix;
            m_bone.m_TPoseWorldMatrix = worldTrs;
        }
    }
}

void Animation::Skeleton::AddAnimation(const char* p_name)
{
    AnimationData tmpAnim(p_name);
    m_animData.try_emplace(p_name, tmpAnim);
}

void Animation::Skeleton::Animate(const char* p_animation, float p_deltaTime)
{
    float matrixData[976];

    for (int i = 0; i < m_bones.size(); ++i)
    {
        Matrix4F localAnim = CalculateNewLocal(p_animation, p_deltaTime, i);

        if (m_bones[i].m_parentIndex >= 0)
            m_bones[i].m_worldMatrix = (m_bones[i].parent->m_worldMatrix * m_bones[i].m_TPoseLocalMatrix * localAnim);
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

void Animation::Skeleton::Animate(float p_deltaTime)
{
    std::string animation;
    switch (m_animState)
    {
    case 0:
        animation = "ThirdPersonWalk.anim";
        break;
    case 1:
        animation = "ThirdPersonRun.anim";
        break;
    default:
        break;
    }

    Animate(animation.c_str(), p_deltaTime * m_speed);
}

Matrix4F Animation::Skeleton::CalculateNewLocal(const char* p_animation, float& deltaTime, int id)
{
    const float frameScale = Tools::Utils::GetDecimalPart(deltaTime);
    std::vector<std::vector<std::pair<Vector3F, Quaternion>>> tmpdata = m_animData[p_animation].m_data;
    const int frame = static_cast<int>(deltaTime);

    const int size = tmpdata.size() - 1;

    Vector3F currPos = tmpdata[frame % size][id].first;
    Vector3F nextPos = tmpdata[(frame + 1) % size][id].first;

    const Quaternion currRot = tmpdata[frame % size][id].second;
    const Quaternion nextRot = tmpdata[(frame + 1) % size][id].second;

    const Vector3F thisPos{ Vector3F::Lerp(currPos, nextPos, frameScale) };
    const Quaternion thisRot{ Quaternion::SlerpShortestPath(currRot, nextRot, frameScale) };

    return { Matrix4F::CreateTransformation(thisPos, thisRot, Vector3F::one) };
}

void Animation::Skeleton::DrawSkeleton()
{
    Bone::DrawBone(m_bones);
}

void Animation::Skeleton::DrawRestingSkeleton()
{
    Bone::DrawTPose(m_bones);
}