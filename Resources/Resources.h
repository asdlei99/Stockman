#pragma once
#include <map>
namespace Resources
{
    namespace Fonts
    {
        enum Files
        {
            KG14,
            KG18,
            KG26
        };
        const std::map<Files, const char *> Paths =
        {
            {KG14, R"(..\Resources\Fonts\KG14.spritefont)"},
            {KG18, R"(..\Resources\Fonts\KG18.spritefont)"},
            {KG26, R"(..\Resources\Fonts\KG26.spritefont)"}
        };
    }
    namespace Models
    {
        enum Files
        {
            Cube,
            SkySphere,
            Staff,
            Tablet1,
            UnitCube
        };
        const std::map<Files, const char *> Paths =
        {
            {Cube, R"(..\Resources\Models\Cube.hyb)"},
            {SkySphere, R"(..\Resources\Models\SkySphere.hyb)"},
            {Staff, R"(..\Resources\Models\Staff.hyb)"},
            {Tablet1, R"(..\Resources\Models\Tablet1.hyb)"},
            {UnitCube, R"(..\Resources\Models\UnitCube.hyb)"}
        };
    }
    namespace Shaders
    {
        enum Files
        {
            AnimationTest,
            ForwardPlus,
            SimpleForward,
            SkyShader,
            SpriteShader
        };
        const std::map<Files, const char *> Paths =
        {
            {AnimationTest, R"(..\Resources\Shaders\AnimationTest.hlsl)"},
            {ForwardPlus, R"(..\Resources\Shaders\ForwardPlus.hlsl)"},
            {SimpleForward, R"(..\Resources\Shaders\SimpleForward.hlsl)"},
            {SkyShader, R"(..\Resources\Shaders\SkyShader.hlsl)"},
            {SpriteShader, R"(..\Resources\Shaders\SpriteShader.hlsl)"}
        };
    }
    namespace Textures
    {
        enum Files
        {
            Backbutton,
            Color_pick_icons,
            crosshair,
            gameOverMenuButtons,
            gameOverTexture,
            Gamesheet,
            HPBars,
            HUDIcons,
            mainMenuButton,
            mainmenupicture,
            MissingTexture,
            SettingsMenuButtons,
            Spellsheet,
            weaponsheet
        };
        const std::map<Files, const char *> Paths =
        {
            {Backbutton, R"(..\Resources\Textures\Backbutton.dds)"},
            {Color_pick_icons, R"(..\Resources\Textures\Color_pick_icons.dds)"},
            {crosshair, R"(..\Resources\Textures\crosshair.png)"},
            {gameOverMenuButtons, R"(..\Resources\Textures\gameOverMenuButtons.png)"},
            {gameOverTexture, R"(..\Resources\Textures\gameOverTexture.png)"},
            {Gamesheet, R"(..\Resources\Textures\Gamesheet.dds)"},
            {HPBars, R"(..\Resources\Textures\HPBars.dds)"},
            {HUDIcons, R"(..\Resources\Textures\HUDIcons.dds)"},
            {mainMenuButton, R"(..\Resources\Textures\mainMenuButton.png)"},
            {mainmenupicture, R"(..\Resources\Textures\mainmenupicture.dds)"},
            {MissingTexture, R"(..\Resources\Textures\MissingTexture.png)"},
            {SettingsMenuButtons, R"(..\Resources\Textures\SettingsMenuButtons.png)"},
            {Spellsheet, R"(..\Resources\Textures\Spellsheet.dds)"},
            {weaponsheet, R"(..\Resources\Textures\weaponsheet.dds)"}
        };
    }
}
