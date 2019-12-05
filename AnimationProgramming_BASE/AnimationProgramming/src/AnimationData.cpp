#include <AnimationData.h>
#include <Engine.h>

Animation::AnimationData::AnimationData(const char* p_name) : m_name(p_name)
{
    LoadAnimation(m_name);
}

void Animation::AnimationData::LoadAnimation(std::string& p_animation)
{
    for (unsigned int frame = 0; frame < GetAnimKeyCount(p_animation.c_str()); ++frame)
    {
        std::vector< std::pair<Vector3F, Quaternion>> vecData;

        for (unsigned int id = 0; id < GetSkeletonBoneCount() - 7; ++id)
        {
            std::pair<Vector3F, Quaternion> data;
            float X, Y, Z, qW, qX, qY, qZ;
            GetAnimLocalBoneTransform(p_animation.c_str(), id, frame, X, Y, Z, qW, qX, qY, qZ);

            data.first = Vector3F{ X, Y, Z };
            data.second = Quaternion{ qX, qY, qZ, qW };
            vecData.push_back(data);
        }
        m_data.push_back(vecData);
    }
}
