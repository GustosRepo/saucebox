#pragma once

#include <array>

namespace extra_sauce
{
struct PresetRecipe
{
    const char* name = "";
    float sauce = 65.0f;
    float drive = 0.68f;
    float crush = 0.48f;
    float chaos = 0.30f;
    float movement = 0.42f;
    float clip = 0.55f;
    float tone = 0.44f;
    float mix = 0.65f;
    float output = -2.0f;
};

inline constexpr std::array<PresetRecipe, 8> factoryRecipes {{
    { "Hard Sauce", 68.0f, 0.72f, 0.42f, 0.24f, 0.34f, 0.60f, 0.46f, 0.66f, -2.0f },
    { "Crushed Hook", 74.0f, 0.64f, 0.72f, 0.28f, 0.42f, 0.48f, 0.50f, 0.58f, -2.4f },
    { "Chaos Bus", 82.0f, 0.76f, 0.54f, 0.66f, 0.58f, 0.64f, 0.38f, 0.50f, -3.0f },
    { "808 Rip", 70.0f, 0.82f, 0.34f, 0.18f, 0.24f, 0.72f, 0.42f, 0.62f, -2.6f },
    { "Dirty Drop", 78.0f, 0.70f, 0.60f, 0.52f, 0.66f, 0.58f, 0.36f, 0.56f, -2.8f },
    { "Static Bite", 64.0f, 0.58f, 0.68f, 0.34f, 0.30f, 0.42f, 0.52f, 0.54f, -2.0f },
    { "Clip Knock", 60.0f, 0.66f, 0.28f, 0.16f, 0.24f, 0.80f, 0.54f, 0.58f, -2.2f },
    { "Controlled Extra", 48.0f, 0.44f, 0.30f, 0.12f, 0.22f, 0.42f, 0.58f, 0.50f, -1.2f }
}};
}
