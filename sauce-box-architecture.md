# Sauce Box Architecture Strategy

> Internal engineering document.
>
> This document describes how we build the Sauce Box plugin ecosystem, not
> how customers experience it.

---

# Goal

Deliver a family of standalone plugins while maintaining one shared codebase.

Customers should feel like they are buying individual products.

Developers should feel like they are maintaining one product platform.

---

# Current Codebase Baseline

The repo currently builds one JUCE plugin target:

- CMake target: `SauceBox`
- Product name: `Hot Packet`
- Bundle ID: `com.saucebox.plugin`
- Manufacturer code: `SaBx`
- Plugin code: `SBox`
- Formats: AU, VST3, Standalone

The current implementation is a good V1 baseline, but it is still product-specific
in code:

- `CMakeLists.txt` hardcodes the plugin identity and product name.
- `Source/PluginProcessor.*` owns the DSP, parameter layout, preset data, state,
  and compatibility IDs.
- `Source/PluginEditor.*` hardcodes Hot Packet branding, colors, copy, layout,
  locked Pro controls, and the track review CTA.

That is fine for shipping Hot Packet V1. It is not the final shape for a product
family.

The next architecture step is to keep the existing behavior but move product
identity, module selection, presets, themes, and licensing rules out of the core
processor/editor code.

---

# Product Strategy

Customers see individual plugins:

- Hot Packet
- Smoky Packet
- Sweet Packet
- Drip Packet
- Chop Packet
- Crunch Packet

Each packet has:

- Its own plugin binary
- Its own installer
- Its own plugin IDs
- Its own presets
- Its own branding
- Its own license SKU

Premium product:

## Sauce Box

Sauce Box contains every current packet in one premium plugin.

Users can either:

- Buy individual packets at a low price
- Buy Sauce Box as the full premium product

The customer never needs to know that the products share internal code.

---

# Engineering Strategy

Use one shared platform with multiple product definitions.

Do not fork the plugin code for every product.

Every product should be built from:

1. Shared DSP modules
2. Shared UI framework
3. Shared preset engine
4. Shared licensing system
5. Product-specific manifest

The product manifest decides what the customer sees. The shared code decides how
the plugin works.

---

# Target Repo Shape

The current repo can migrate toward this shape:

```text
Source/
  Core/
    SauceProcessorBase.h
    SauceProcessorBase.cpp
    SauceEditorBase.h
    SauceEditorBase.cpp
    ProductManifest.h
    ProductRegistry.h
    PresetBank.h
    LicenseState.h

  DSP/
    SaturationModule.h
    SaturationModule.cpp
    TextureModule.h
    TextureModule.cpp
    WowModule.h
    WowModule.cpp
    ToneModule.h
    ToneModule.cpp
    MixOutputModule.h
    MixOutputModule.cpp

  UI/
    PacketLookAndFeel.h
    PacketLookAndFeel.cpp
    PacketTheme.h
    PacketControls.h
    PresetBrowser.h
    LockedControlPanel.h
    TrackReviewCta.h

  Products/
    HotPacket/
      HotPacketManifest.h
      HotPacketPresets.h
      HotPacketTheme.h

    SmokyPacket/
      SmokyPacketManifest.h
      SmokyPacketPresets.h
      SmokyPacketTheme.h

    SweetPacket/
      SweetPacketManifest.h
      SweetPacketPresets.h
      SweetPacketTheme.h

    SauceBox/
      SauceBoxManifest.h
      SauceBoxPresets.h
      SauceBoxTheme.h

CMakeLists.txt
```

This does not need to happen all at once. The first practical extraction should
be Hot Packet only:

1. Move Hot Packet product constants into a manifest.
2. Move Hot Packet presets into a preset bank.
3. Move Hot Packet colors/copy into a theme.
4. Keep the same plugin sound and UI behavior.

---

# Product Manifest

Every product should have one manifest that defines product identity and feature
availability.

Example shape:

```cpp
struct ProductManifest
{
    const char* productId;
    const char* productName;
    const char* shortName;
    const char* companyName;
    const char* bundleId;
    const char* licenseSku;

    uint32_t manufacturerCode;
    uint32_t pluginCode;

    bool exposesFreeMode;
    bool exposesProMode;
    bool exposesTrackReviewCta;

    std::vector<ModuleId> modules;
    std::vector<ParameterId> visibleFreeParameters;
    std::vector<ParameterId> visibleProParameters;
};
```

Hot Packet V1 would map to:

```text
Product ID: hot-packet
Product Name: Hot Packet
License SKU: hot-packet-pro
Modules: saturation, texture, wow, tone, mix-output
Free controls: Instant Sauce, Mix, Output
Pro controls: Drive, Texture, Wow Depth, Wow Rate, Tone, Mix, Output
CTA: Track Review
```

Sauce Box would map to:

```text
Product ID: sauce-box
Product Name: Sauce Box
License SKU: sauce-box
Modules: all current packet modules
Free controls: none, unless a demo mode is desired
Pro controls: all available modules
CTA: optional
```

---

# Build Outputs

The build system should produce separate plugin binaries from the same source.

Customer-facing outputs:

```text
Hot Packet.vst3
Hot Packet.component
Hot Packet.app

Smoky Packet.vst3
Smoky Packet.component
Smoky Packet.app

Sweet Packet.vst3
Sweet Packet.component
Sweet Packet.app

Sauce Box.vst3
Sauce Box.component
Sauce Box.app
```

Implementation options:

## Near-Term

Keep one CMake target for Hot Packet while the product platform is extracted.

This is the lowest-risk path because the current product can keep shipping while
the internals improve.

## Mid-Term

Use one CMake helper function that creates a JUCE plugin target from a product
manifest:

```cmake
add_sauce_product(
  TARGET HotPacket
  PRODUCT_NAME "Hot Packet"
  BUNDLE_ID "com.808bytes.hotpacket"
  PLUGIN_CODE HoPk
  MANIFEST HOT_PACKET
)
```

The helper should create one plugin target per customer product, all linking the
same shared source modules.

---

# Plugin Identity Rules

Plugin identity must be stable once a product ships.

Each product needs:

- Unique AU bundle ID
- Unique VST3 processor/controller IDs
- Unique JUCE plugin code
- Stable product name
- Stable state/preset compatibility story

Do not reuse Hot Packet IDs for Sauce Box.

Do not let Sauce Box replace packet installs in a DAW session.

If a product is renamed after release, keep compatibility IDs the way the current
code already does for the legacy Sauce Box to Hot Packet rename.

---

# Shared DSP Modules

The current Hot Packet DSP should be split into small modules without changing
the sound:

- Saturation: drive gain and soft clipping
- Texture: bit reduction and downsample hold
- Wow: LFO movement
- Tone: post low-pass shaping
- Mix/Output: dry/wet blend, gain compensation, final limiter

Each module should own:

- Parameter definitions
- Runtime state
- Prepare/reset behavior
- Audio processing
- Value formatting where relevant

The processor should assemble modules from the product manifest.

Hot Packet uses the existing module chain:

```text
Input
  -> Saturation
  -> Texture
  -> Wow
  -> Tone
  -> Mix/Output
Output
```

Sauce Box can later become either:

1. A rack where users combine packet modules, or
2. A premium all-in-one plugin with curated macro pages.

That decision should be made before Sauce Box UI work starts because it affects
state format, CPU behavior, preset format, and automation.

---

# Parameters and Automation

Parameter IDs are part of the public plugin contract. Once released, avoid
renaming them.

Current Hot Packet parameters:

- `instantSauce`
- `drive`
- `crush`
- `wowDepth`
- `wowRate`
- `tone`
- `mix`
- `output`

The existing IDs can stay for Hot Packet compatibility.

Future products should use clear module-scoped IDs when there is any risk of
collision:

```text
hot.drive
hot.texture
hot.wowDepth
hot.wowRate
hot.tone
global.mix
global.output
```

If Sauce Box contains multiple packet modules, scoped IDs become mandatory.

---

# Preset System

Presets should move out of `PluginProcessor.cpp`.

A preset should store:

- Preset ID
- Display name
- Product ID
- Required modules
- Parameter values
- Macro value, when applicable
- Minimum engine version, if needed

Example:

```cpp
struct PresetDefinition
{
    const char* presetId;
    const char* displayName;
    const char* productId;
    std::vector<ModuleId> requiredModules;
    std::vector<ParameterValue> values;
};
```

Rules:

- Hot Packet presets should load in Hot Packet.
- Sauce Box may load packet presets if it contains the required modules.
- A preset must fail gracefully if the current product does not include its
  required modules.
- Preset matching should be based on parameter values, not program count.

The current 12 Hot Packet presets can become `HotPacketPresets.h` first. No
external preset file format is required for V1.

---

# Licensing and Feature Gating

Licensing should unlock SKUs, not code forks.

The product manifest declares what is possible. The license state declares what
is unlocked.

Hot Packet V1:

- Free mode is always available.
- Pro controls are visible but locked when the user does not own `hot-packet-pro`.
- Track review CTA is available in Free and Pro.

Sauce Box:

- Owns a separate `sauce-box` SKU.
- Unlocks all included packet modules inside Sauce Box.
- Does not automatically need to unlock separate packet plugin binaries unless
  the business model explicitly says it does.

Keep this distinction clear:

```text
Buying Sauce Box unlocks Sauce Box.
Buying Hot Packet Pro unlocks Hot Packet Pro.
Cross-unlocks are a business decision, not an engineering assumption.
```

---

# UI Architecture

The current editor is product-specific and should be split into:

- Shared packet layout components
- Shared knob styling
- Shared preset dropdown
- Shared locked-control panel
- Shared CTA component
- Product theme data
- Product copy data

Hot Packet theme data should include:

- Product title: `HOT PACKET`
- Byline: `808BYTES ORIGINAL SAUCE`
- Main colors
- Packet art copy
- CTA label and URL
- Free/Pro control visibility

The editor should not need hardcoded `Hot Packet` strings once product manifests
exist.

---

# State Compatibility

State must stay loadable across updates.

Current state is stored through APVTS XML plus `programIndex`.

Near-term rules:

- Keep existing Hot Packet parameter IDs.
- Keep loading old APVTS state.
- Keep legacy compatible VST3 class IDs for already-shipped builds.
- Add new manifest fields without breaking old sessions.

Mid-term rules:

- Add `productId` to state.
- Add `engineVersion` to state.
- Keep unknown parameter values ignored, not fatal.
- Keep missing module values defaulted, not fatal.

---

# Testing and Release Rules

A shared DSP change can affect every product. That means the release process has
to test products, not just modules.

Minimum checks before shipping:

- Build every product target.
- Open every product in AU, VST3, and Standalone where supported.
- Confirm plugin names and IDs are correct.
- Confirm old Hot Packet sessions still load.
- Confirm presets load and recall values.
- Confirm locked controls do not change when locked.
- Confirm Free and Pro states render correctly.
- Confirm bypass, silence, mono, and stereo cases are clean.
- Confirm output does not jump dangerously across presets.

Preferred automated checks:

- Parameter layout snapshot per product
- Preset recall test per product
- Basic audio render smoke test
- State save/load round trip
- Plugin identity snapshot from generated build metadata

---

# Migration Plan

## Phase 1: Stabilize Hot Packet

Ship the current Hot Packet V1 with minimal churn.

Keep:

- Current DSP behavior
- Current preset behavior
- Current Free/Pro UI shape
- Current track review CTA

Only fix bugs and release blockers.

## Phase 2: Extract Product Data

Move hardcoded Hot Packet data into product-specific files:

- `HotPacketManifest.h`
- `HotPacketPresets.h`
- `HotPacketTheme.h`

No behavior change.

## Phase 3: Extract DSP Modules

Split the current processor chain into reusable modules:

- Saturation
- Texture
- Wow
- Tone
- Mix/Output

No sound change.

Use audio snapshot tests or rendered comparison files before and after the split.

## Phase 4: Add Product Build Helper

Replace the single hardcoded `juce_add_plugin` block with a helper that can
create one target per product.

Start with Hot Packet only.

Then add a second internal product target to prove the architecture before
building the whole ecosystem.

## Phase 5: Build the Next Packet

Build one new packet from the shared system.

Recommended next product: Smoky Packet or Sweet Packet.

Do not start Sauce Box until at least two packet products share the platform.
Sauce Box should prove aggregation, not be the first test of the architecture.

## Phase 6: Build Sauce Box

Decide whether Sauce Box is:

- A unified rack, or
- A premium macro interface over all modules

Then build its manifest, preset bank, theme, and module routing.

---

# Recommended Next Engineering Step

Do not create seven plugins yet.

Completed first extraction:

- `Source/Products/HotPacket/HotPacketManifest.h`
- `Source/Products/HotPacket/HotPacketPresets.h`
- `Source/Products/HotPacket/HotPacketTheme.h`

The processor and editor now read Hot Packet product data from those files while
keeping the same DSP behavior and build outputs.

The active next step is:

1. Validate and polish Hot Packet V1.
2. Tune preset names and values in `HotPacketPresets.h`.
3. Tune product copy and visual tone in `HotPacketTheme.h`.
4. Keep the current DSP path stable while product details are refined.
5. Run the smoke-test matrix before deeper DSP/module extraction.

That keeps us on the architecture plan without risking the launch product.

---

# Guiding Principle

Customers buy products.

Developers maintain architecture.

Never let internal engineering decisions dictate the product experience.
