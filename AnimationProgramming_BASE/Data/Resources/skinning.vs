
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	vec4 pos = vec4(inputPosition, 1.0f);

    int i0 = int(boneIndices[0]);
    int i1 = int(boneIndices[1]);
    int i2 = int(boneIndices[2]);
    int i3 = int(boneIndices[3]);

	vec4 LocalPos = vec4((boneWeights[0] * (pos * skin.mat[i0]))
                  + (boneWeights[1] * (pos * skin.mat[i1]))
                  + (boneWeights[2] * (pos * skin.mat[i2]))
	              + (boneWeights[3] * (pos * skin.mat[i3])));

	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(LocalPos.xyz, 1.0f));
	outNormal = mat3(modelViewMatrix) * normal;

	outNormal = normalize(outNormal);
}
