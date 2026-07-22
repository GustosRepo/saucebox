#pragma once

#include <array>

namespace sweet_sauce
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
inline constexpr auto sauce = "sweet.sauce";
inline constexpr auto air = "sweet.air";
inline constexpr auto presence = "sweet.presence";
inline constexpr auto smooth = "sweet.smooth";
inline constexpr auto deEss = "sweet.deEss";
inline constexpr auto compression = "sweet.compression";
inline constexpr auto width = "sweet.width";
inline constexpr auto mix = "sweet.mix";
inline constexpr auto output = "sweet.output";
}

inline constexpr ProductManifest manifest {
    "sweet-sauce",
    "Sweet Sauce",
    "SWEET SAUCE",
    "808Bytes",
    "com.808bytes.sweetsauce",
    "EByt",
    "SwSc",
    "sweet-sauce-pro",
    "https://saucebox.audio/review",
    "Vocal shine, air, presence, and smooth polish without harshness.",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 4> demoControlParameterIds {{
    parameters::sauce,
    parameters::mix,
    parameters::output,
    parameters::air
}};

inline constexpr std::array<const char*, 8> proControlParameterIds {{
    parameters::air,
    parameters::presence,
    parameters::smooth,
    parameters::deEss,
    parameters::compression,
    parameters::width,
    parameters::mix,
    parameters::output
}};
}
