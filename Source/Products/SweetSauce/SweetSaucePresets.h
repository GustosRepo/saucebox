#pragma once

#include <array>

namespace sweet_sauce
{
struct PresetRecipe
{
    const char* name = "";
    float sauce = 50.0f;
    float air = 0.45f;
    float presence = 0.45f;
    float smooth = 0.50f;
    float deEss = 0.35f;
    float compression = 0.35f;
    float width = 0.45f;
    float mix = 0.70f;
    float output = -1.0f;
};

inline constexpr std::array<PresetRecipe, 8> factoryRecipes {{
    { "Vocal Shine", 50.0f, 0.58f, 0.50f, 0.52f, 0.38f, 0.34f, 0.44f, 0.70f, -1.0f },
    { "Hook Air", 62.0f, 0.74f, 0.56f, 0.48f, 0.44f, 0.30f, 0.58f, 0.66f, -1.4f },
    { "Smooth Lead", 46.0f, 0.42f, 0.46f, 0.70f, 0.56f, 0.42f, 0.36f, 0.74f, -1.0f },
    { "Adlib Candy", 68.0f, 0.70f, 0.62f, 0.44f, 0.34f, 0.38f, 0.72f, 0.62f, -1.8f },
    { "Rap Clear", 54.0f, 0.48f, 0.64f, 0.50f, 0.46f, 0.48f, 0.32f, 0.70f, -1.2f },
    { "R&B Silk", 58.0f, 0.54f, 0.44f, 0.74f, 0.50f, 0.36f, 0.62f, 0.76f, -1.4f },
    { "Stack Polish", 44.0f, 0.50f, 0.42f, 0.58f, 0.42f, 0.28f, 0.70f, 0.60f, -0.8f },
    { "Mix Top Lift", 36.0f, 0.36f, 0.34f, 0.50f, 0.22f, 0.24f, 0.30f, 0.42f, -0.5f }
}};
}
