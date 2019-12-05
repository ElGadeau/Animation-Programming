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

            // Matrix4F localTrs = Matrix4F::CreateTransformation(Vector3F{ X, Y, Z }, Quaternion{ qX, qY, qZ, qW }, Vector3F::one);
            // data.make_pair(Vector3F{ X, Y, Z }, Quaternion{ qX, qY, qZ, qW });
            // auto p1 = std::make_pair(Vector3F{ X, Y, Z }, Quaternion{ qX, qY, qZ, qW });

            data.first = Vector3F{ X, Y, Z };
            data.second = Quaternion{ qX, qY, qZ, qW };
            vecData.push_back(data);
        }
        m_data.push_back(vecData);
    }
}
