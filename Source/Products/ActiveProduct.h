#pragma once

#include "HotPacket/HotPacketManifest.h"
#include "HotPacket/HotPacketPresets.h"
#include "HotPacket/HotPacketTheme.h"
#include "SecretSauce/SecretSauceManifest.h"
#include "SecretSauce/SecretSaucePresets.h"
#include "SecretSauce/SecretSauceTheme.h"

namespace active_product
{
#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
inline constexpr auto& manifest = secret_sauce::manifest;

namespace theme
{
inline const auto& packetRed = secret_sauce::theme::sauceRed;
inline const auto& packetOrange = secret_sauce::theme::saucePlum;
inline const auto& packetYellow = secret_sauce::theme::sauceGold;
inline const auto& packetCream = secret_sauce::theme::sauceCream;
inline const auto& packetInk = secret_sauce::theme::sauceBlack;
inline const auto& packetPurple = secret_sauce::theme::sauceMint;

inline constexpr auto byline = secret_sauce::theme::byline;
inline constexpr auto packetFlavor = secret_sauce::theme::bottleFlavor;
inline constexpr auto packetBackgroundWord = secret_sauce::theme::backgroundWord;
inline constexpr auto packetNote = secret_sauce::theme::note;
inline constexpr auto presetLabel = secret_sauce::theme::presetLabel;
inline constexpr auto ctaLabel = secret_sauce::theme::ctaLabel;
inline constexpr auto ctaButtonText = secret_sauce::theme::ctaButtonText;
inline constexpr auto unlockBadgeText = secret_sauce::theme::unlockBadgeText;
}

inline constexpr std::array<hot_packet::PresetDefinition, secret_sauce::factoryRecipes.size()> factoryPresets {{
    { "Self Sample Sauce", 0.32f, 0.38f, 0.08f, 0.05f, 0.64f, 0.62f, -1.0f, 50.0f },
    { "Vocal Chop",       0.68f, 0.62f, 0.62f, 0.22f, 0.66f, 0.58f, -1.8f, 66.0f },
    { "Reverse Pull",     0.26f, 0.66f, 0.08f, 0.04f, 0.42f, 0.66f, -2.0f, 64.0f },
    { "Stutter Step",     0.80f, 0.70f, 0.24f, 0.82f, 0.58f, 0.54f, -2.4f, 74.0f },
    { "Tape Wobble",      0.20f, 0.72f, 0.02f, 0.00f, 0.34f, 0.68f, -1.8f, 58.0f },
    { "Dirty Dream",      0.44f, 0.78f, 0.26f, 0.22f, 0.32f, 0.70f, -2.8f, 78.0f },
    { "Drip Throw",       0.36f, 0.54f, 0.04f, 0.10f, 0.76f, 0.56f, -1.6f, 64.0f },
    { "Half-Time Melt",   0.16f, 0.72f, 0.06f, 0.08f, 0.38f, 0.64f, -2.2f, 70.0f },
    { "Formant Ghost",    0.46f, 0.64f, 0.16f, 0.18f, 0.50f, 0.60f, -2.0f, 68.0f },
    { "Hook Maker",       0.34f, 0.44f, 0.06f, 0.04f, 0.72f, 0.54f, -1.2f, 56.0f },
    { "Dark R&B",         0.28f, 0.68f, 0.14f, 0.08f, 0.26f, 0.68f, -2.4f, 72.0f },
    { "Trap Motion",      0.84f, 0.64f, 0.50f, 0.66f, 0.60f, 0.58f, -2.6f, 76.0f }
}};

inline constexpr auto placeholderEngineNote =
    "";
#else
inline constexpr auto& manifest = hot_packet::manifest;
inline constexpr auto& factoryPresets = hot_packet::factoryPresets;

namespace theme
{
inline const auto& packetRed = hot_packet::theme::packetRed;
inline const auto& packetOrange = hot_packet::theme::packetOrange;
inline const auto& packetYellow = hot_packet::theme::packetYellow;
inline const auto& packetCream = hot_packet::theme::packetCream;
inline const auto& packetInk = hot_packet::theme::packetInk;
inline const auto& packetPurple = hot_packet::theme::packetPurple;

inline constexpr auto byline = hot_packet::theme::byline;
inline constexpr auto packetFlavor = hot_packet::theme::packetFlavor;
inline constexpr auto packetBackgroundWord = hot_packet::theme::packetBackgroundWord;
inline constexpr auto packetNote = hot_packet::theme::packetNote;
inline constexpr auto presetLabel = hot_packet::theme::presetLabel;
inline constexpr auto ctaLabel = hot_packet::theme::ctaLabel;
inline constexpr auto ctaButtonText = hot_packet::theme::ctaButtonText;
inline constexpr auto unlockBadgeText = hot_packet::theme::unlockBadgeText;
}

inline constexpr auto placeholderEngineNote = "";
#endif
}
