#pragma once

#include <array>

namespace sauce_box_suite
{
struct SuitePresetCollection
{
    const char* name = "";
    const char* description = "";
};

inline constexpr std::array<SuitePresetCollection, 8> collections {{
    { "Starter Sauce Box", "Balanced first-use presets across every sauce." },
    { "Self Sample Suite", "Secret Sauce, Drip Sauce, and Sweet Sauce chains for self-recorded ideas." },
    { "Vocal Suite", "Sweet Sauce, Secret Sauce, Light Sauce, and Drip Sauce workflows." },
    { "808 Suite", "Thick Sauce, Hot Packet, and Extra Sauce workflows." },
    { "Drum Bus Suite", "Glue Sauce, Hot Packet, and Extra Sauce workflows." },
    { "Hook Suite", "Secret Sauce, Sweet Sauce, and Drip Sauce workflows." },
    { "Mix Finish Suite", "Light Sauce, Glue Sauce, and Sweet Sauce workflows." },
    { "Chaos Suite", "Extra Sauce, Secret Sauce, and Drip Sauce workflows." }
}};
}
