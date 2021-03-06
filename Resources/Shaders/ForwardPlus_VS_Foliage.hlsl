#include "include/Vertex.hlsli"
#include "include/StaticInstance.hlsli"
#include "include/Fragment.hlsli"
#include "include/Camera.hlsli"

#define USE_GRID_TEXTURE

cbuffer cb0 : register(b0) { Camera camera; };
cbuffer cb3 : register(b3) { float grassTime; };
cbuffer LightBuffer : register(b2) { float4x4 LightProjection; };

cbuffer cb10 : register(b10) { uint instanceOffset; };
StructuredBuffer<StaticInstance> instanceBuffer : register(t10);

Fragment VS(Vertex vertex, uint instanceId : SV_InstanceId) 
{
    StaticInstance   instance = instanceBuffer[instanceId + instanceOffset];
	Fragment fragment;

    float3 position = vertex.position;
    float sx = sin(position.x + vertex.uv.x * 5 + grassTime);
    float sy = cos(position.y + pow(vertex.uv.y, 2) * 5 + grassTime);
	position.x += 0.10 * sx*sy    * position.y * 2;
	position.z += 0.05 * sy*sx*sy * position.y * 2;

    fragment.position    = mul(instance.world, float4(position, 1));
    fragment.ndcPosition = mul(camera.viewProjection, fragment.position);
    fragment.lightPos    = mul(LightProjection, fragment.position);

    fragment.normal     = normalize(mul(instance.world, float4(vertex.normal,   0))).xyz;
    fragment.binormal   = normalize(mul(instance.world, float4(vertex.binormal, 0))).xyz;
    fragment.tangent    = normalize(mul(instance.world, float4(vertex.tangent,  0))).xyz;
    fragment.viewNormal = normalize(mul(camera.view,    float4(fragment.normal, 0)));

    fragment.uv         = vertex.uv;

#ifdef USE_GRID_TEXTURE
    float3   localPosition = mul(instance.world, float4(vertex.position, 0)).xyz;
    float3x3 tangentMatrix = float3x3(fragment.tangent, fragment.binormal, fragment.normal);
    float3   worldTangent  = mul(tangentMatrix, localPosition);
    fragment.gridUV = (worldTangent.xy + float2(1, 1)) / 8;
#endif

    fragment.color = instance.color;
    fragment.useGridTexture = instance.useGridTexture;

	return fragment;
}
