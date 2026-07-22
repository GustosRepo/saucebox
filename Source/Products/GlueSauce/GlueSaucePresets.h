#pragma once

#include <array>

namespace glue_sauce
{
struct PresetRecipe
{
    const char* name = "";
    float sauce = 50.0f;
    float compression = 0.45f;
    float drive = 0.30f;
    float transient = 0.50f;
    float tone = 0.55f;
    float pump = 0.18f;
    float mix = 0.70f;
    float output = -1.0f;
};

inline constexpr std::array<PresetRecipe, 8> factoryRecipes {{
    { "Drum Bus Glue", 56.0f, 0.56f, 0.34f, 0.52f, 0.54f, 0.18f, 0.72f, -1.4f },
    { "Mix Glue Lite", 34.0f, 0.30f, 0.16f, 0.48f, 0.58f, 0.08f, 0.46f, -0.5f },
    { "Punch Hold", 52.0f, 0.44f, 0.24f, 0.68f, 0.56f, 0.10f, 0.66f, -1.0f },
    { "Warm Bus", 48.0f, 0.40f, 0.46f, 0.42f, 0.48f, 0.12f, 0.68f, -1.2f },
    { "Knock Control", 60.0f, 0.62f, 0.28f, 0.58f, 0.50f, 0.20f, 0.70f, -1.8f },
    { "Parallel Squeeze", 72.0f, 0.78f, 0.38f, 0.44f, 0.52f, 0.24f, 0.50f, -2.2f },
    { "Vocal Bus Lock", 44.0f, 0.42f, 0.18f, 0.50f, 0.62f, 0.10f, 0.58f, -0.8f },
    { "Two Track Touch", 28.0f, 0.24f, 0.12f, 0.46f, 0.56f, 0.06f, 0.38f, -0.4f }
}};
}
