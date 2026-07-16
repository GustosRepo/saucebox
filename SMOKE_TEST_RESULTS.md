# Hot Packet Smoke Test Results

## 2026-07-16 - Command-Line AU/Build Validation (macOS)

Status: PASS

### Covered checks

1. Release build completed after product-data extraction.
2. AU registered as `aufx SBox SaBx - 808Bytes: Hot Packet`.
3. `auval -v aufx SBox SaBx` succeeded.
4. AU render tests passed at 512, 64, 137, and 4096 frame buffers.
5. AU render tests passed at 11025, 22050, 44100, 48000, 96000, and 192000 Hz.
6. AU mono and stereo render checks passed.
7. AU parameter set, scheduled parameter, and ramped parameter checks passed.
8. AU, VST3, and Standalone build artifacts passed `codesign --verify --deep --strict`.
9. VST3 `moduleinfo.json` reports `Hot Packet`, vendor `808Bytes`, version `0.1.0`, and legacy Sauce Box compatibility IDs.

### Notes

- `pluginval` is not installed on this machine, so VST3 host-style validation still needs a DAW or pluginval pass.
- Stale `Sauce Box` bundles from an older build were removed from `build/SauceBox_artefacts/Release` after validation.
- Because `COPY_PLUGIN_AFTER_BUILD` is enabled, the Release build overwrote the user-installed AU and VST3 Hot Packet plugins.

### Remaining validation

1. DAW save/recall verification.
2. Preset switching during real playback.
3. Real-material listening pass for vocals, 808, drums, keys, and mix bus.
4. Explicit click/pop and loudness check while changing controls.
5. Second DAW confirmation, recommended Logic or Reaper.

## 2026-07-11 - FL Studio (macOS)

Status: PASS (initial smoke pass)

### Covered checks

1. Plugin loads and runs in session.
2. Real-time control movement is stable.
3. No immediate crash during practical use.

### Notes

- User-reported result: "works" in FL Studio.
- This confirms core viability for first DAW target.

### Remaining validation

1. Save/recall verification (explicit pass/fail log).
2. Buffer/sample-rate transition checks.
3. Bus/send workflow verification.
4. Second DAW confirmation (recommended: Logic or Reaper).
