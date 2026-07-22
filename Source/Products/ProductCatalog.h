#pragma once

#include <array>

#include "HotPacket/HotPacketManifest.h"
#include "HotPacket/HotPacketPresets.h"
#include "HotPacket/HotPacketTheme.h"
#include "DripSauce/DripSauceManifest.h"
#include "DripSauce/DripSaucePresets.h"
#include "DripSauce/DripSauceTheme.h"
#include "ExtraSauce/ExtraSauceManifest.h"
#include "ExtraSauce/ExtraSaucePresets.h"
#include "ExtraSauce/ExtraSauceTheme.h"
#include "GlueSauce/GlueSauceManifest.h"
#include "GlueSauce/GlueSaucePresets.h"
#include "GlueSauce/GlueSauceTheme.h"
#include "LightSauce/LightSauceManifest.h"
#include "LightSauce/LightSaucePresets.h"
#include "LightSauce/LightSauceTheme.h"
#include "SauceBox/SauceBoxManifest.h"
#include "SauceBox/SauceBoxPresets.h"
#include "SauceBox/SauceBoxTheme.h"
#include "SecretSauce/SecretSauceManifest.h"
#include "SecretSauce/SecretSaucePresets.h"
#include "SecretSauce/SecretSauceTheme.h"
#include "SweetSauce/SweetSauceManifest.h"
#include "SweetSauce/SweetSaucePresets.h"
#include "SweetSauce/SweetSauceTheme.h"
#include "ThickSauce/ThickSauceManifest.h"
#include "ThickSauce/ThickSaucePresets.h"
#include "ThickSauce/ThickSauceTheme.h"

namespace sauce_products
{
struct ProductSummary
{
    const char* productId;
    const char* productName;
    const char* role;
    const char* bundleId;
    const char* manufacturerCode;
    const char* pluginCode;
    const char* licenseSku;
    bool isFlagship;
    bool isSuite;
};

inline constexpr std::array<ProductSummary, 9> catalog {{
    {
        hot_packet::manifest.productId,
        hot_packet::manifest.productName,
        "Entry texture plugin and free lead magnet",
        hot_packet::manifest.bundleId,
        hot_packet::manifest.manufacturerCode,
        hot_packet::manifest.pluginCode,
        hot_packet::manifest.licenseSku,
        false,
        false
    },
    {
        secret_sauce::manifest.productId,
        secret_sauce::manifest.productName,
        "Flagship creative movement and effects plugin",
        secret_sauce::manifest.bundleId,
        secret_sauce::manifest.manufacturerCode,
        secret_sauce::manifest.pluginCode,
        secret_sauce::manifest.licenseSku,
        true,
        false
    },
    {
        sweet_sauce::manifest.productId,
        sweet_sauce::manifest.productName,
        "Vocal polish, air, compression, and presence",
        sweet_sauce::manifest.bundleId,
        sweet_sauce::manifest.manufacturerCode,
        sweet_sauce::manifest.pluginCode,
        sweet_sauce::manifest.licenseSku,
        false,
        false
    },
    {
        thick_sauce::manifest.productId,
        thick_sauce::manifest.productName,
        "808, bass, low-end weight, and body enhancement",
        thick_sauce::manifest.bundleId,
        thick_sauce::manifest.manufacturerCode,
        thick_sauce::manifest.pluginCode,
        thick_sauce::manifest.licenseSku,
        false,
        false
    },
    {
        glue_sauce::manifest.productId,
        glue_sauce::manifest.productName,
        "Drum bus and mix bus glue",
        glue_sauce::manifest.bundleId,
        glue_sauce::manifest.manufacturerCode,
        glue_sauce::manifest.pluginCode,
        glue_sauce::manifest.licenseSku,
        false,
        false
    },
    {
        drip_sauce::manifest.productId,
        drip_sauce::manifest.productName,
        "Delays, throws, space, and ambience",
        drip_sauce::manifest.bundleId,
        drip_sauce::manifest.manufacturerCode,
        drip_sauce::manifest.pluginCode,
        drip_sauce::manifest.licenseSku,
        false,
        false
    },
    {
        extra_sauce::manifest.productId,
        extra_sauce::manifest.productName,
        "Aggressive distortion, crush, chaos, and hard movement",
        extra_sauce::manifest.bundleId,
        extra_sauce::manifest.manufacturerCode,
        extra_sauce::manifest.pluginCode,
        extra_sauce::manifest.licenseSku,
        false,
        false
    },
    {
        light_sauce::manifest.productId,
        light_sauce::manifest.productName,
        "Subtle clean polish, lift, and clarity",
        light_sauce::manifest.bundleId,
        light_sauce::manifest.manufacturerCode,
        light_sauce::manifest.pluginCode,
        light_sauce::manifest.licenseSku,
        false,
        false
    },
    {
        sauce_box_suite::manifest.productId,
        sauce_box_suite::manifest.productName,
        "Full suite bundle with every sauce plugin",
        sauce_box_suite::manifest.bundleId,
        sauce_box_suite::manifest.manufacturerCode,
        sauce_box_suite::manifest.pluginCode,
        sauce_box_suite::manifest.licenseSku,
        false,
        true
    }
}};

inline constexpr const ProductSummary& flagshipProduct = catalog[1];
inline constexpr const ProductSummary& suiteProduct = catalog[8];
}
