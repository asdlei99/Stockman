#pragma once

#include "../Utility/ConstantBuffer.h"

#include <SimpleMath.h>
#include <Engine\Constants.h>
namespace Graphics
{
	class Sun
	{
	public:
		struct ShaderMatrix
		{
			DirectX::SimpleMath::Matrix vp;
			//"padding" TODO: Should probably make a new shader instead
			DirectX::SimpleMath::Matrix mInvP;
			//End padding
			DirectX::SimpleMath::Matrix mV;
			DirectX::SimpleMath::Vector4 camPos;
		};

		struct LightValues
		{
			DirectX::SimpleMath::Vector4 pos;
			//Value from 0 to 1, when it is 1 the shadows are on
			float fade;
			char pad[12];
		};

		Sun(ID3D11Device* device, int width, int height);
		~Sun();

		void update(ID3D11DeviceContext* context, float rotationAmount, DirectX::SimpleMath::Vector3 offset = DirectX::SimpleMath::Vector3(0, 0, 0));

		ConstantBuffer<ShaderMatrix>* getMatrixBuffer() { return &matrixBuffer; };
		ConstantBuffer<LightValues>* getShaderBuffer() { return &shaderBuffer; };
		D3D11_VIEWPORT getViewPort() { return viewPort; };
		float getShadowFade() const;

	private:
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
		DirectX::SimpleMath::Vector4 pos;

		

		//Clamp a value between min and max
		float snap(float value, float min, float max);

		ShaderMatrix matrixData;
		LightValues shaderData;
		ConstantBuffer<ShaderMatrix> matrixBuffer;
		ConstantBuffer<LightValues> shaderBuffer;

		D3D11_VIEWPORT viewPort;

	};
}