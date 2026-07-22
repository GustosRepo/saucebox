# Sauce Box by 808Bytes

Sauce Box is the shared JUCE codebase for the 808Bytes plugin ecosystem.

Current build targets:

- Hot Packet: free/entry texture plugin built around Instant Sauce.
- Secret Sauce: flagship movement/effects plugin target. Engine v0 includes
  Sauce macro control, movement depth/rate, chop, stutter-style sample hold,
  moving filter, width, mix, output, and safety limiting.

Flagship paid product direction:

- Secret Sauce: creative movement/effects plugin for self-sampled vocals, loops,
  chops, pitch movement, stutters, reverse pulls, throws, and ear candy.

Marketing line: Instant sauce for dull sounds.

Free mode should feel immediate:

- Instant Sauce (one-knob macro)
- Mix (dry/wet blend)
- Output (level match)

Pro unlocks the full box:

- Drive (soft saturation)
- Texture (bit depth + downsample texture)
- Wow Depth + Wow Rate (subtle delay modulation)
- Tone (post low-pass shaping)
- Mix and Output

The 808Bytes product ecosystem grows around the Sauce family:

- Sauce Box: the parent ecosystem and future bundle
- Secret Sauce: the flagship creative movement and effects plugin
- Hot Packet: the entry texture plugin and free lead magnet
- Sauce Packs: preset expansion packs
- Instant Sauce: the Free one-knob mode
- Sweet Sauce: vocal polish and shine
- Thick Sauce: 808, bass, and body enhancement
- Glue Sauce: drum bus and mix bus glue
- Drip Sauce: delay, space, throws, and ambience
- Extra Sauce: aggressive distortion, crush, and chaos
- Light Sauce: subtle clean polish

See `SECRET_SAUCE_PRODUCT_STRATEGY.md` for the Secret Sauce product plan.
See `PRODUCT_LINEUP.md` for all singles, suite packaging, SKUs, and planned plugin IDs.

## Build (macOS)

### 1) Configure

```bash
cmake -S . -B build -G Xcode
```

### 2) Build

```bash
cmake --build build --config Release
```

### 3) Locate plugin binaries

After build, look under `build` products for:

- `Hot Packet.vst3`
- `Hot Packet.component` (AU)
- `Hot Packet.app` (Standalone)
- `Secret Sauce.vst3`
- `Secret Sauce.component` (AU)
- `Secret Sauce.app` (Standalone)

## Notes

- This is intentionally simple and musical, not a strict analog model.
- Next iterations can add tape hiss, stereo width, transient emphasis, and modulation randomness.
