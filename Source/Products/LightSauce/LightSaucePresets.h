#pragma once

#include <array>

namespace light_sauce
{
struct PresetRecipe
{
    const char* name = "";
    float sauce = 35.0f;
    float clarity = 0.42f;
    float lift = 0.34f;
    float smooth = 0.46f;
    float width = 0.36f;
    float glue = 0.24f;
    float mix = 0.50f;
    float output = -0.5f;
};

inline constexpr std::array<PresetRecipe, 8> factoryRecipes {{
    { "Clean Lift", 36.0f, 0.48f, 0.42f, 0.44f, 0.34f, 0.20f, 0.48f, -0.4f },
    { "Vocal Touch", 40.0f, 0.44f, 0.38f, 0.58f, 0.30f, 0.22f, 0.52f, -0.5f },
    { "Mix Fresh", 30.0f, 0.36f, 0.32f, 0.42f, 0.28f, 0.20f, 0.38f, -0.3f },
    { "Keys Open", 42.0f, 0.46f, 0.44f, 0.40f, 0.52f, 0.18f, 0.50f, -0.6f },
    { "Drum Polish", 34.0f, 0.34f, 0.28f, 0.36f, 0.24f, 0.36f, 0.44f, -0.5f },
    { "Soft Bright", 38.0f, 0.54f, 0.46f, 0.62f, 0.32f, 0.18f, 0.46f, -0.4f },
    { "Wide Clean", 44.0f, 0.40f, 0.36f, 0.42f, 0.68f, 0.16f, 0.48f, -0.6f },
    { "Barely Sauce", 20.0f, 0.24f, 0.18f, 0.32f, 0.18f, 0.12f, 0.26f, -0.2f }
}};
}
