#pragma once

#include <array>

namespace hot_packet
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
    bool exposesFreeMode;
    bool exposesProMode;
    bool exposesTrackReviewCta;
};

namespace parameters
{
inline constexpr auto drive = "drive";
inline constexpr auto texture = "crush";
inline constexpr auto wowDepth = "wowDepth";
inline constexpr auto wowRate = "wowRate";
inline constexpr auto tone = "tone";
inline constexpr auto mix = "mix";
inline constexpr auto output = "output";
inline constexpr auto instantSauce = "instantSauce";
}

namespace state
{
inline constexpr auto programIndex = "programIndex";
}

inline constexpr ProductManifest manifest {
    "hot-packet",
    "Hot Packet",
    "HOT PACKET",
    "808Bytes",
    "com.saucebox.plugin",
    "SaBx",
    "SBox",
    "hot-packet-pro",
    "https://saucebox.audio/review",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 5> proControlParameterIds {{
    parameters::drive,
    parameters::texture,
    parameters::wowDepth,
    parameters::wowRate,
    parameters::tone
}};

inline constexpr std::array<const char*, 3> freeControlParameterIds {{
    parameters::instantSauce,
    parameters::mix,
    parameters::output
}};
}
