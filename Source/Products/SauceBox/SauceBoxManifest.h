#pragma once

#include <array>

namespace sauce_box_suite
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
    bool isSuite;
};

inline constexpr ProductManifest manifest {
    "sauce-box",
    "Sauce Box",
    "SAUCE BOX",
    "808Bytes",
    "com.808bytes.saucebox",
    "EByt",
    "SaBx",
    "sauce-box-suite",
    "https://808bytes.com",
    "The full 808Bytes sauce suite in one bundle.",
    false,
    true,
    true,
    true
};

inline constexpr std::array<const char*, 8> includedProductIds {{
    "hot-packet",
    "secret-sauce",
    "sweet-sauce",
    "thick-sauce",
    "glue-sauce",
    "drip-sauce",
    "extra-sauce",
    "light-sauce"
}};
}
