#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define SHADOW_WIDTH
#define SHADOW_HEIGHT

#define SAFE_RELEASE(p) { if ( (p) && (p) != nullptr ) { (p)->Release(); (p) = 0; } }

#define _CRTDBG_MAP_ALLOC
#define newd new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define WINDOWED    true
#define WIREFRAME   false
#define VSYNC		1 //1 == ON, 0 = OFF
#define FPS_CAP		60

#define D3D_DEBUG_INFO

#define TEXTURE_PATH(path) L"Resources/Textures/" path
#define MODEL_PATH(path)   L"Resources/Models/" path
#define SHADER_PATH(path) L"Resources/Shaders/" path

