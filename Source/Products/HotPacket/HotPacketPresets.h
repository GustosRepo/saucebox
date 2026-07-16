#pragma once

#include <array>

namespace hot_packet
{
struct PresetDefinition
{
    const char* name = "";
    float drive = 10.0f;
    float texture = 0.22f;
    float wowDepth = 0.20f;
    float wowRate = 1.10f;
    float tone = 0.58f;
    float mix = 0.62f;
    float output = -1.5f;
    float instantSauce = 50.0f;
};

inline constexpr std::array<PresetDefinition, 12> factoryPresets {{
    { "Instant Sauce",      10.0f, 0.22f, 0.20f, 1.10f, 0.58f, 0.62f, -1.5f, 50.0f },
    { "Velvet Vocal",        8.0f, 0.12f, 0.08f, 0.75f, 0.68f, 0.48f, -1.0f, 34.0f },
    { "Crisp Vocal Edge",   14.0f, 0.18f, 0.06f, 1.30f, 0.74f, 0.44f, -2.0f, 44.0f },
    { "808 Glue Heat",      16.0f, 0.30f, 0.04f, 0.55f, 0.46f, 0.56f, -2.5f, 56.0f },
    { "Drum Bus Dirt",      12.0f, 0.36f, 0.10f, 1.80f, 0.52f, 0.50f, -2.0f, 62.0f },
    { "Drum Bus Crunch",    18.0f, 0.45f, 0.12f, 2.20f, 0.57f, 0.46f, -3.0f, 72.0f },
    { "Keys Warm Dust",      9.0f, 0.24f, 0.18f, 0.95f, 0.50f, 0.60f, -1.5f, 48.0f },
    { "Guitar Soft Bite",   13.0f, 0.20f, 0.14f, 1.60f, 0.63f, 0.54f, -1.8f, 52.0f },
    { "Lo-Fi Wash",         11.0f, 0.52f, 0.36f, 0.85f, 0.37f, 0.72f, -2.8f, 78.0f },
    { "Chorus Lift",         7.0f, 0.10f, 0.16f, 1.25f, 0.70f, 0.42f, -0.8f, 32.0f },
    { "Mix Bus Glue Lite",   6.0f, 0.08f, 0.05f, 0.65f, 0.64f, 0.36f, -0.5f, 26.0f },
    { "Night Tape Mood",    10.0f, 0.34f, 0.28f, 0.70f, 0.42f, 0.66f, -2.2f, 64.0f }
}};
}
