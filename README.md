# Sauce Box by 808Bytes - Simple Texturizer (VST3/AU)

A starter JUCE plugin that adds character with a simple chain:

- Drive (soft saturation)
- Crush (bit depth + downsample texture)
- Wow Depth + Wow Rate (subtle delay modulation)
- Tone (post low-pass shaping)
- Mix (dry/wet)

The larger 808Bytes product ecosystem can grow around the Sauce family:

- Sauce Box: the main texture plugin
- Sauce Packs: preset expansion packs
- Instant Sauce: a preset category or one-knob mode
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

- `Sauce Box.vst3`
- `Sauce Box.component` (AU)
- `Sauce Box.app` (Standalone)

## Notes

- This is intentionally simple and musical, not a strict analog model.
- Next iterations can add tape hiss, stereo width, transient emphasis, and modulation randomness.
