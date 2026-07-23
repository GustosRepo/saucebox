#pragma once

#include <array>

namespace drip_sauce
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
inline constexpr auto sauce = "drip.sauce";
inline constexpr auto delayTime = "drip.delayTime";
inline constexpr auto feedback = "drip.feedback";
inline constexpr auto filter = "drip.filter";
inline constexpr auto space = "drip.space";
inline constexpr auto width = "drip.width";
inline constexpr auto throwLevel = "drip.throwLevel";
inline constexpr auto mix = "drip.mix";
inline constexpr auto output = "drip.output";
}

inline constexpr ProductManifest manifest {
    "drip-sauce",
    "Drip Sauce",
    "DRIP SAUCE",
    "808Bytes",
    "com.808bytes.dripsauce",
    "EByt",
    "DrSc",
    "drip-sauce-pro",
    "https://808bytes.com",
    "Delays, throws, space, and ambience built for fast ear candy.",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 4> demoControlParameterIds {{
    parameters::sauce,
    parameters::delayTime,
    parameters::mix,
    parameters::output
}};

inline constexpr std::array<const char*, 8> proControlParameterIds {{
    parameters::delayTime,
    parameters::feedback,
    parameters::filter,
    parameters::space,
    parameters::width,
    parameters::throwLevel,
    parameters::mix,
    parameters::output
}};
}
