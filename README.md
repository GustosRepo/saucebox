# Hot Packet by 808Bytes - Simple Texturizer (VST3/AU)

Hot Packet is a JUCE texture plugin built around an Instant Sauce Free mode and a deeper Pro control set.

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

The larger 808Bytes product ecosystem can grow around the Sauce family:

- Sauce Box: the parent ecosystem and future bundle
- Hot Packet: the main texture plugin
- Sauce Packs: preset expansion packs
- Instant Sauce: the Free one-knob mode
- Secret Sauce: more aggressive or unusual presets
- Light Sauce / Extra Sauce: intensity-based preset banks

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

## Notes

- This is intentionally simple and musical, not a strict analog model.
- Next iterations can add tape hiss, stereo width, transient emphasis, and modulation randomness.
