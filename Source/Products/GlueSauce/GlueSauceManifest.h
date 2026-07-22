#pragma once

#include <array>

namespace glue_sauce
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
inline constexpr auto sauce = "glue.sauce";
inline constexpr auto compression = "glue.compression";
inline constexpr auto drive = "glue.drive";
inline constexpr auto transient = "glue.transient";
inline constexpr auto tone = "glue.tone";
inline constexpr auto pump = "glue.pump";
inline constexpr auto mix = "glue.mix";
inline constexpr auto output = "glue.output";
}

inline constexpr ProductManifest manifest {
    "glue-sauce",
    "Glue Sauce",
    "GLUE SAUCE",
    "808Bytes",
    "com.808bytes.gluesauce",
    "EByt",
    "GlSc",
    "glue-sauce-pro",
    "https://saucebox.audio/review",
    "Fast drum bus and mix bus glue with musical level control.",
    true,
    true,
    true
};

inline constexpr std::array<const char*, 4> demoControlParameterIds {{
    parameters::sauce,
    parameters::compression,
    parameters::mix,
    parameters::output
}};

inline constexpr std::array<const char*, 7> proControlParameterIds {{
    parameters::compression,
    parameters::drive,
    parameters::transient,
    parameters::tone,
    parameters::pump,
    parameters::mix,
    parameters::output
}};
}
