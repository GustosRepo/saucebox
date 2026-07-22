#pragma once

#include <array>

namespace drip_sauce
{
struct PresetRecipe
{
    const char* name = "";
    float sauce = 50.0f;
    float delayTime = 0.50f;
    float feedback = 0.35f;
    float filter = 0.55f;
    float space = 0.40f;
    float width = 0.60f;
    float throwLevel = 0.45f;
    float mix = 0.35f;
    float output = -1.0f;
};

inline constexpr std::array<PresetRecipe, 8> factoryRecipes {{
    { "Slap Drip", 42.0f, 0.18f, 0.24f, 0.62f, 0.22f, 0.46f, 0.34f, 0.28f, -0.8f },
    { "Hook Throw", 62.0f, 0.50f, 0.48f, 0.58f, 0.46f, 0.72f, 0.68f, 0.38f, -1.4f },
    { "Dark Delay", 58.0f, 0.38f, 0.56f, 0.34f, 0.36f, 0.58f, 0.52f, 0.34f, -1.2f },
    { "Wide Wash", 66.0f, 0.62f, 0.44f, 0.64f, 0.76f, 0.88f, 0.48f, 0.42f, -1.8f },
    { "Adlib Space", 54.0f, 0.28f, 0.34f, 0.68f, 0.54f, 0.78f, 0.44f, 0.36f, -1.0f },
    { "Quarter Sauce", 48.0f, 0.42f, 0.38f, 0.56f, 0.34f, 0.62f, 0.36f, 0.30f, -0.8f },
    { "Transition Tail", 72.0f, 0.74f, 0.66f, 0.48f, 0.64f, 0.84f, 0.74f, 0.46f, -2.0f },
    { "Clean Room", 34.0f, 0.24f, 0.18f, 0.70f, 0.38f, 0.50f, 0.24f, 0.24f, -0.5f }
}};
}
