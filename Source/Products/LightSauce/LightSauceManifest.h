#pragma once

#include <array>

namespace light_sauce
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
inline constexpr auto sauce = "light.sauce";
inline constexpr auto clarity = "light.clarity";
inline constexpr auto lift = "light.lift";
inline constexpr auto smooth = "light.smooth";
inline constexpr auto width = "light.width";
inline constexpr auto glue = "light.glue";
inline constexpr auto mix = "light.mix";
inline constexpr auto output = "light.output";
}

inline constexpr ProductManifest manifest {
    "light-sauce",
    "Light Sauce",
    "LIGHT SAUCE",
    "808Bytes",
    "com.808bytes.lightsauce",
    "EByt",
    "LiSc",
    "light-sauce-pro",
    "https://saucebox.audio/review",
    "Subtle clean polish, lift, and clarity when the track only needs a touch.",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 4> demoControlParameterIds {{
    parameters::sauce,
    parameters::clarity,
    parameters::mix,
    parameters::output
}};

inline constexpr std::array<const char*, 7> proControlParameterIds {{
    parameters::clarity,
    parameters::lift,
    parameters::smooth,
    parameters::width,
    parameters::glue,
    parameters::mix,
    parameters::output
}};
}
