#pragma once

#include <array>

namespace secret_sauce
{
enum class FlavorMode
{
    selfSample,
    vocalChop,
    reversePull,
    stutterStep,
    tapeWobble,
    dirtyDream,
    dripThrow,
    halfTimeMelt,
    formantGhost,
    hookMaker,
    darkRnb,
    trapMotion
};

struct PresetRecipe
{
    const char* name = "";
    FlavorMode flavor = FlavorMode::selfSample;
    float sauce = 50.0f;
    float movementRate = 0.50f;
    float movementDepth = 0.50f;
    float swing = 0.0f;
    float random = 0.0f;
    float pitch = 0.0f;
    float formant = 0.0f;
    float chop = 0.0f;
    float stutter = 0.0f;
    float reverse = 0.0f;
    float filter = 0.50f;
    float width = 0.50f;
    float mix = 0.65f;
    float output = -1.0f;
};

inline constexpr std::array<PresetRecipe, 12> factoryRecipes {{
    { "Self Sample Sauce", FlavorMode::selfSample,   50.0f, 0.32f, 0.38f, 0.08f, 0.10f,  0.0f,   0.0f, 0.08f, 0.05f, 0.00f, 0.64f, 0.62f, 0.62f, -1.0f },
    { "Vocal Chop",        FlavorMode::vocalChop,    66.0f, 0.68f, 0.62f, 0.18f, 0.10f,  0.0f,  0.05f, 0.62f, 0.22f, 0.00f, 0.66f, 0.52f, 0.58f, -1.8f },
    { "Reverse Pull",      FlavorMode::reversePull,  64.0f, 0.26f, 0.66f, 0.04f, 0.20f,  0.0f,   0.0f, 0.08f, 0.04f, 0.72f, 0.42f, 0.68f, 0.66f, -2.0f },
    { "Stutter Step",      FlavorMode::stutterStep,  74.0f, 0.80f, 0.70f, 0.22f, 0.14f,  0.0f,   0.0f, 0.24f, 0.82f, 0.02f, 0.58f, 0.44f, 0.54f, -2.4f },
    { "Tape Wobble",       FlavorMode::tapeWobble,   58.0f, 0.20f, 0.72f, 0.02f, 0.28f, -0.05f,  0.0f, 0.02f, 0.00f, 0.02f, 0.34f, 0.54f, 0.68f, -1.8f },
    { "Dirty Dream",       FlavorMode::dirtyDream,   78.0f, 0.44f, 0.78f, 0.12f, 0.36f, -0.02f, -0.08f, 0.26f, 0.22f, 0.10f, 0.32f, 0.72f, 0.70f, -2.8f },
    { "Drip Throw",        FlavorMode::dripThrow,    64.0f, 0.36f, 0.54f, 0.10f, 0.18f,  0.0f,  0.04f, 0.04f, 0.10f, 0.24f, 0.76f, 0.78f, 0.56f, -1.6f },
    { "Half-Time Melt",    FlavorMode::halfTimeMelt, 70.0f, 0.16f, 0.72f, 0.06f, 0.24f, -0.12f, -0.04f, 0.06f, 0.08f, 0.08f, 0.38f, 0.66f, 0.64f, -2.2f },
    { "Formant Ghost",     FlavorMode::formantGhost, 68.0f, 0.46f, 0.64f, 0.12f, 0.30f,  0.02f, -0.30f, 0.16f, 0.18f, 0.08f, 0.50f, 0.74f, 0.60f, -2.0f },
    { "Hook Maker",        FlavorMode::hookMaker,    56.0f, 0.34f, 0.44f, 0.08f, 0.10f,  0.0f,  0.02f, 0.06f, 0.04f, 0.02f, 0.72f, 0.84f, 0.54f, -1.2f },
    { "Dark R&B",          FlavorMode::darkRnb,      72.0f, 0.28f, 0.68f, 0.10f, 0.22f, -0.04f, -0.10f, 0.14f, 0.08f, 0.08f, 0.26f, 0.76f, 0.68f, -2.4f },
    { "Trap Motion",       FlavorMode::trapMotion,   76.0f, 0.84f, 0.64f, 0.26f, 0.16f,  0.0f,   0.0f, 0.50f, 0.66f, 0.02f, 0.60f, 0.54f, 0.58f, -2.6f }
}};
}
