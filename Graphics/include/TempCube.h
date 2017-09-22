#pragma once
#include <d3d11.h>
#include "Datatypes.h"
struct  TempCube
{
    ID3D11Buffer * vertexBuffer;
    TempCube(ID3D11Device * device)
    {
        Vertex vertices[] =
        {
            // FRONT
            { { -1, -1, -1 * -1 },{ 0,  0, -1 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },
            { { -1,  1, -1 * -1 },{ 0,  0, -1 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { 1, -1, -1 * -1 },{ 0,  0, -1 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },

            { { 1, -1, -1 * -1 },{ 0,  0, -1 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },
            { { -1,  1, -1 * -1 },{ 0,  0, -1 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { 1,  1, -1 * -1 },{ 0,  0, -1 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } },

            // TOP		
            { { -1,  1, -1 * -1 },{ 0,  1,  0 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },
            { { -1,  1,  1 * -1 },{ 0,  1,  0 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { 1,  1, -1 * -1 },{ 0,  1,  0 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },

            { { 1,  1, -1 * -1 },{ 0,  1,  0 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },
            { { -1,  1,  1 * -1 },{ 0,  1,  0 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { 1,  1,  1 * -1 },{ 0,  1,  0 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } },

            // LEFT		
            { { -1, -1,  1 * -1 },{ -1,  0,  0 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { -1,  1,  1 * -1 },{ -1,  0,  0 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } },
            { { -1, -1, -1 * -1 },{ -1,  0,  0 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },

            { { -1, -1, -1 * -1 },{ -1,  0,  0 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },
            { { -1,  1,  1 * -1 },{ -1,  0,  0 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } },
            { { -1,  1, -1 * -1 },{ -1,  0,  0 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },

            // RIGHT	
            { { 1,  1,  1 * -1 },{ 1,  0,  0 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } },
            { { 1, -1,  1 * -1 },{ 1,  0,  0 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { 1, -1, -1 * -1 },{ 1,  0,  0 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },

            { { 1,  1,  1 * -1 },{ 1,  0,  0 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } },
            { { 1, -1, -1 * -1 },{ 1,  0,  0 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },
            { { 1,  1, -1 * -1 },{ 1,  0,  0 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },

            // BACK		
            { { -1,  1,  1 * -1 },{ 0,  0,  1 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { -1, -1,  1 * -1 },{ 0,  0,  1 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },
            { { 1, -1,  1 * -1 },{ 0,  0,  1 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },

            { { -1,  1,  1 * -1 },{ 0,  0,  1 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { 1, -1,  1 * -1 },{ 0,  0,  1 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },
            { { 1,  1,  1 * -1 },{ 0,  0,  1 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } },

            // BOTTOM	
            { { -1, -1,  1 * -1 },{ 0, -1,  0 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { -1, -1, -1 * -1 },{ 0, -1,  0 * -1 },{ 0, 0 },{ 0,0 },{ 0,0 } },
            { { 1, -1, -1 * -1 },{ 0, -1,  0 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },

            { { -1, -1,  1 * -1 },{ 0, -1,  0 * -1 },{ 0, 1 },{ 0,0 },{ 0,0 } },
            { { 1, -1, -1 * -1 },{ 0, -1,  0 * -1 },{ 1, 0 },{ 0,0 },{ 0,0 } },
            { { 1, -1,  1 * -1 },{ 0, -1,  0 * -1 },{ 1, 1 },{ 0,0 },{ 0,0 } }
        };

        D3D11_SUBRESOURCE_DATA subData = {};
        subData.pSysMem = vertices;

        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(vertices);
        desc.Usage = D3D11_USAGE_IMMUTABLE;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        device->CreateBuffer(&desc, &subData, &vertexBuffer);
    }

    ~TempCube()
    {
        vertexBuffer->Release();
    }
};