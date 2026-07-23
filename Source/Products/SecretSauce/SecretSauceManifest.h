#pragma once

#include <array>

namespace secret_sauce
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
inline constexpr auto sauce = "secret.sauce";
inline constexpr auto flavor = "secret.flavor";
inline constexpr auto movementRate = "secret.movementRate";
inline constexpr auto movementDepth = "secret.movementDepth";
inline constexpr auto swing = "secret.swing";
inline constexpr auto random = "secret.random";
inline constexpr auto pitch = "secret.pitch";
inline constexpr auto formant = "secret.formant";
inline constexpr auto chop = "secret.chop";
inline constexpr auto stutter = "secret.stutter";
inline constexpr auto reverse = "secret.reverse";
inline constexpr auto filter = "secret.filter";
inline constexpr auto width = "secret.width";
inline constexpr auto mix = "secret.mix";
inline constexpr auto output = "secret.output";
}

namespace performance
{
inline constexpr auto freeze = "secret.freeze";
inline constexpr auto reverse = "secret.reverseMomentary";
inline constexpr auto repeat = "secret.repeat";
inline constexpr auto dropout = "secret.dropout";
inline constexpr auto tapeStop = "secret.tapeStop";
inline constexpr auto throwFx = "secret.throw";
}

inline constexpr ProductManifest manifest {
    "secret-sauce",
    "Secret Sauce",
    "SECRET SAUCE",
    "808Bytes",
    "com.808bytes.secretsauce",
    "EByt",
    "SeSc",
    "secret-sauce-pro",
    "https://808bytes.com",
    "Movement, chops, pitch, repeats, and ear candy for self-sampled ideas.",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 4> demoControlParameterIds {{
    parameters::sauce,
    parameters::flavor,
    parameters::mix,
    parameters::output
}};

inline constexpr std::array<const char*, 13> proControlParameterIds {{
    parameters::movementRate,
    parameters::movementDepth,
    parameters::swing,
    parameters::random,
    parameters::pitch,
    parameters::formant,
    parameters::chop,
    parameters::stutter,
    parameters::reverse,
    parameters::filter,
    parameters::width,
    parameters::mix,
    parameters::output
}};

inline constexpr std::array<const char*, 6> performanceButtonIds {{
    performance::freeze,
    performance::reverse,
    performance::repeat,
    performance::dropout,
    performance::tapeStop,
    performance::throwFx
}};
}
