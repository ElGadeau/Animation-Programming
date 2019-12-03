// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"
#include <GPM/GPM.h>
#include <iostream>
#include <vector>

struct Bone
{
    Bone(const char* p_name, int p_index, const char* p_parentName, int p_parentIndex) : Name(p_name), Index(p_index), ParentName(p_parentName), ParentIndex(p_parentIndex)
    {}
    const char* Name;
    int Index;
    const char* ParentName;
    int ParentIndex;
    Vector3F LocalPosition;
    Matrix4F LocalMatrix;
    Matrix4F WorldMatrix;
    Quaternion Rotation;
    // Bone* parent = nullptr;
};

Quaternion ParentWorldPosition(Bone p_parent)
{
    if (p_parent.ParentName == nullptr)
        return p_parent.Rotation;

    return p_parent.Rotation;
}

void DrawBones(std::vector<Bone>& p_bone)
{
    for (int i = 0; i < GetSkeletonBoneCount() - 7; ++i)
    {
        if (p_bone[i].ParentIndex >= 0)
        {
            DrawLine(p_bone[p_bone[i].ParentIndex].WorldMatrix[3], p_bone[p_bone[i].ParentIndex].WorldMatrix[7], p_bone[p_bone[i].ParentIndex].WorldMatrix[11],
                p_bone[i].WorldMatrix[3], p_bone[i].WorldMatrix[7], p_bone[i].WorldMatrix[11], 0, 0, 0);
        }
    }
}

class CSimulation : public ISimulation
{
    std::vector<Bone> BoneArray;
	virtual void Init() override
	{
        for (unsigned int i = 0; i < GetSkeletonBoneCount(); ++i)
        {
            const char* name = GetSkeletonBoneName(i);
            int index = i;
            int pIndex = GetSkeletonBoneParentIndex(i);
            const char* pName = nullptr;
            if (pIndex >= 0)
                pName = GetSkeletonBoneName(pIndex);

            BoneArray.emplace_back(name, index, pName, pIndex);

            float X, Y, Z, qW, qX, qY, qZ;
            GetSkeletonBoneLocalBindTransform(i, X, Y, Z, qW, qX, qY, qZ);

            BoneArray[i].Rotation = { qX, qY, qZ, qW };
            BoneArray[i].LocalPosition = { X, Y, Z };

            Matrix3F rotMat = BoneArray[i].Rotation.ToMatrix3();

            BoneArray[i].LocalMatrix = Matrix4F::CreateTransformation(BoneArray[i].LocalPosition, BoneArray[i].Rotation, Vector3F::one);
        }
        
        for (int i = 0; i < GetSkeletonBoneCount() - 7; ++i)
        {
            std::cout << "Bone number[" << i << "] : " << BoneArray[i].Name << '\n';
            if (BoneArray[i].ParentIndex < 0)
            {
                std::cout << "NO PARENT\n";

                BoneArray[i].WorldMatrix = BoneArray[i].LocalMatrix;
            }
            else
            {
                std::cout << "Bone number[" << BoneArray[i].ParentIndex << "] : "  << GetSkeletonBoneName(BoneArray[i].ParentIndex) << " is parent\n";

                //world * local
                BoneArray[i].WorldMatrix = BoneArray[BoneArray[i].ParentIndex].WorldMatrix * BoneArray[i].LocalMatrix;
            }

            size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
            float X, Y, Z, qW, qX, qY, qZ;
            GetSkeletonBoneLocalBindTransform(i, X, Y, Z, qW, qX, qY, qZ);
            printf("Anim key : pos(%f,%f,%f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", X, Y, Z, qW, qX, qY, qZ);
            std::cout << "World Location: X= " << BoneArray[i].WorldMatrix[3] << " Y= " << BoneArray[i].WorldMatrix[7] << " Z= " << BoneArray[i].WorldMatrix[11] << '\n';

            std::cout << '\n';
        }
	}

	virtual void Update(float frameTime) override
	{
        DrawBones(BoneArray);
		// X axis
		// DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		// DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		// DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);


    return 0;
}