#pragma once

#include <array>

namespace thick_sauce
{
struct PresetRecipe
{
    const char* name = "";
    float sauce = 50.0f;
    float weight = 0.55f;
    float harmonics = 0.40f;
    float subFocus = 0.50f;
    float punch = 0.35f;
    float mono = 0.70f;
    float saturation = 0.35f;
    float mix = 0.70f;
    float output = -1.5f;
};

inline constexpr std::array<PresetRecipe, 8> factoryRecipes {{
    { "808 Weight", 58.0f, 0.70f, 0.46f, 0.68f, 0.38f, 0.86f, 0.34f, 0.72f, -1.8f },
    { "Bass Fill", 48.0f, 0.56f, 0.54f, 0.50f, 0.34f, 0.72f, 0.42f, 0.68f, -1.2f },
    { "Sub Lock", 42.0f, 0.50f, 0.28f, 0.80f, 0.24f, 0.96f, 0.22f, 0.62f, -1.0f },
    { "Punchy 808", 64.0f, 0.62f, 0.44f, 0.58f, 0.68f, 0.82f, 0.40f, 0.70f, -2.0f },
    { "Small Speaker Bass", 70.0f, 0.46f, 0.76f, 0.38f, 0.44f, 0.62f, 0.58f, 0.74f, -2.2f },
    { "Kick Body", 52.0f, 0.64f, 0.34f, 0.48f, 0.58f, 0.74f, 0.30f, 0.66f, -1.6f },
    { "Low Mid Meat", 46.0f, 0.58f, 0.36f, 0.34f, 0.30f, 0.52f, 0.28f, 0.64f, -1.0f },
    { "Clean Weight", 36.0f, 0.44f, 0.22f, 0.62f, 0.28f, 0.86f, 0.18f, 0.56f, -0.8f }
}};
}
