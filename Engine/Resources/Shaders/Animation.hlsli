#ifdef ANIMATION_T_SLOT
StructuredBuffer<float4x4> ANIMATION_TRANSFORMS : register(ANIMATION_T_SLOT);
float4x4 calculateAnimationMatrix(Vertex vertex)
{
    float4x4 animationMatrix;

    for (int i = 0; i < 4; i++)
    {
        animationMatrix += mul(ANIMATION_TRANSFORMS[vertex.jointIds[i]], vertex.jointWeights[i]);
    }

    return animationMatrix;
}
#else
#error "ANIMATION_T_SLOT not defined, nowhere to bind ANIMATION_TRANSFORMS"
#endif