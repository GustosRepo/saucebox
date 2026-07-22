#pragma once

#include <array>

namespace extra_sauce
{
struct ProductManifest
{
    const char* productId;
    const char* productName;
    const char* displayTitle;
    const char* companyName;
    const char* bundleId;
    const char* manufacturerCode;
    const char* pluginCode;
    const char* licenseSku;
    const char* trackReviewUrl;
    const char* oneLinePromise;
    bool exposesDemoMode;
    bool exposesProMode;
    bool exposesTrackReviewCta;
};

namespace parameters
{
inline constexpr auto sauce = "extra.sauce";
inline constexpr auto drive = "extra.drive";
inline constexpr auto crush = "extra.crush";
inline constexpr auto chaos = "extra.chaos";
inline constexpr auto movement = "extra.movement";
inline constexpr auto clip = "extra.clip";
inline constexpr auto tone = "extra.tone";
inline constexpr auto mix = "extra.mix";
inline constexpr auto output = "extra.output";
}

inline constexpr ProductManifest manifest {
    "extra-sauce",
    "Extra Sauce",
    "EXTRA SAUCE",
    "808Bytes",
    "com.808bytes.extrasauce",
    "EByt",
    "ExSc",
    "extra-sauce-pro",
    "https://saucebox.audio/review",
    "Aggressive distortion, crush, chaos, and hard movement.",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 4> demoControlParameterIds {{
    parameters::sauce,
    parameters::drive,
    parameters::mix,
    parameters::output
}};

inline constexpr std::array<const char*, 8> proControlParameterIds {{
    parameters::drive,
    parameters::crush,
    parameters::chaos,
    parameters::movement,
    parameters::clip,
    parameters::tone,
    parameters::mix,
    parameters::output
}};
}
