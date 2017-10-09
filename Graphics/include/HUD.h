#pragma once
#include "Resources\Shader.h"
#include <Engine\Constants.h>
#include "Utility\ShaderResource.h"
#include <CommonStates.h>
#include "Structs.h"
#include <SpriteFont.h>
#include <SpriteBatch.h>
#include <vector>

namespace Graphics
{
    class HUD
    {
    public:
        HUD(ID3D11Device * device, ID3D11DeviceContext * context);
        ~HUD();
        void drawHUD(ID3D11DeviceContext * context, ID3D11RenderTargetView * backBuffer, ID3D11BlendState * blendState);
        void queueText(Graphics::TextString * text);
        void fillHUDInfo(HUDInfo * info);

    private:
        void createHUDVBS(ID3D11Device * device);
        void createHUDTextures(ID3D11Device * device, ID3D11DeviceContext * context);
        void renderText(ID3D11BlendState * blendState);
        void setHUDTextRenderPos();
        void renderHUDText();
        void updateHUDConstantBuffer(ID3D11DeviceContext * context);
        void createHUDCBs(ID3D11Device * device);

        Shader shader;
        
        
        ID3D11ShaderResourceView *hudTextures[5];
        ID3D11Buffer * vertexBuffer;
        ID3D11Buffer * HUDCBuffer;

        std::unique_ptr<DirectX::SpriteFont> sFont[5];
        std::unique_ptr<DirectX::SpriteBatch> sBatch;

        std::vector<TextString> textQueue;
        HUDInfo * currentInfo;

        DirectX::SimpleMath::Vector2 ammoPos1;
        DirectX::SimpleMath::Vector2 ammoPos2;

        DirectX::SimpleMath::Vector2 scorePos;
        DirectX::SimpleMath::Vector2 wavePos;
        DirectX::SimpleMath::Vector2 timePos;
        DirectX::SimpleMath::Vector2 cdPos;

        bool changed;
        bool firstTime;
        int prevHP;
        float prevCooldown;
    };

}

