#pragma once

#include <array>

namespace thick_sauce
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
    const char* websiteUrl;
    const char* oneLinePromise;
    bool exposesDemoMode;
    bool exposesProMode;
    bool exposesWebsiteCta;
};

namespace parameters
{
inline constexpr auto sauce = "thick.sauce";
inline constexpr auto weight = "thick.weight";
inline constexpr auto harmonics = "thick.harmonics";
inline constexpr auto subFocus = "thick.subFocus";
inline constexpr auto punch = "thick.punch";
inline constexpr auto mono = "thick.mono";
inline constexpr auto saturation = "thick.saturation";
inline constexpr auto mix = "thick.mix";
inline constexpr auto output = "thick.output";
}

inline constexpr ProductManifest manifest {
    "thick-sauce",
    "Thick Sauce",
    "THICK SAUCE",
    "808Bytes",
    "com.808bytes.thicksauce",
    "EByt",
    "ThSc",
    "thick-sauce-pro",
    "https://808bytes.com",
    "808, bass, low-end weight, and body that stays controlled.",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 4> demoControlParameterIds {{
    parameters::sauce,
    parameters::weight,
    parameters::mix,
    parameters::output
}};

inline constexpr std::array<const char*, 8> proControlParameterIds {{
    parameters::weight,
    parameters::harmonics,
    parameters::subFocus,
    parameters::punch,
    parameters::mono,
    parameters::saturation,
    parameters::mix,
    parameters::output
}};
}
