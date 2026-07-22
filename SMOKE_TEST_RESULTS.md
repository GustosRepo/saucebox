# Hot Packet Smoke Test Results

## 2026-07-22 - Secret Sauce Product Scaffold Build Check

Status: PASS

### Covered checks

1. Added Secret Sauce product manifest, theme, preset recipes, and shared product catalog.
2. Included the new product catalog in the existing Hot Packet processor build path.
3. Release build completed successfully with the current Hot Packet AU, VST3, and Standalone targets.
4. Expanded product catalog to preserve the business model: individual sauce plugins plus Sauce Box as the suite.
5. Added scaffold manifests, themes, and preset banks for Sweet Sauce, Thick Sauce, Glue Sauce, Drip Sauce, Extra Sauce, Light Sauce, and Sauce Box.
6. Added planned bundle IDs, manufacturer codes, plugin codes, and license SKUs for every single and the suite.
7. Added reusable CMake helper and built both Hot Packet and Secret Sauce targets.
8. Confirmed Secret Sauce AU metadata: bundle `com.808bytes.secretsauce`, manufacturer `EByt`, subtype `SeSc`.
9. Confirmed Secret Sauce VST3 `moduleinfo.json` reports name `Secret Sauce`, vendor `808Bytes`, version `0.1.0`.
10. Codesign verification passed for Secret Sauce AU, VST3, and Standalone artifacts.
11. Replaced Secret Sauce placeholder Hot Packet DSP with engine v0: Sauce macro, movement rate/depth, chop gate, stutter-style sample hold, moving filter, width, mix, output safety.
12. Release build completed successfully after the engine v0 change.
13. `auval -v aufx SeSc EByt` passed for Secret Sauce.
14. Secret Sauce AU published 10 parameters: Sauce, Flavor, Movement Rate, Movement Depth, Chop, Stutter, Filter, Width, Mix, Output.
15. Secret Sauce AU render tests passed at 512, 64, 137, and 4096 frame buffers and at 11025, 22050, 44100, 48000, 96000, and 192000 Hz.
16. Added first-pass Secret Sauce performance buttons: Freeze, Reverse, Repeat, Dropout, Tape Stop, and Throw.
17. Release build completed successfully after performance-button DSP/UI changes.
18. Codesign verification passed for Hot Packet and Secret Sauce AU, VST3, and Standalone artifacts.
19. `auval -v aufx SeSc EByt` passed for Secret Sauce after the performance-button pass.
20. Secret Sauce AU now publishes 16 parameters, including the six performance buttons.
21. `auval -v aufx SBox SaBx` passed for Hot Packet after the shared-code changes.
22. Added first-pass host tempo sync for Secret Sauce movement divisions, chops, repeats, dropouts, reverse windows, throws, and tape-stop curves.
23. Release build completed successfully after the tempo-sync pass.
24. Codesign verification passed again for Hot Packet and Secret Sauce AU, VST3, and Standalone artifacts.
25. `auval -v aufx SeSc EByt` and `auval -v aufx SBox SaBx` both passed after the tempo-sync pass.
26. Added first-pass Secret Sauce flavor intelligence. Each Flavor mode now biases timing, depth, chop, stutter, filter, width, gate depth, reverse amount, throw amount, saturation, dropout shape, and tape behavior.
27. Release build completed successfully after the flavor-intelligence pass.
28. Codesign verification passed again for Hot Packet and Secret Sauce AU, VST3, and Standalone artifacts.
29. `auval -v aufx SeSc EByt` and `auval -v aufx SBox SaBx` both passed after the flavor-intelligence pass.
30. Added first-pass Secret Sauce movement smoothing for chop gates, dropout gates, reverse blend, throw blend, tape amount, and tape dip.
31. Release build completed successfully after the smoothing pass.
32. Codesign verification passed again for Hot Packet and Secret Sauce AU, VST3, and Standalone artifacts.
33. `auval -v aufx SeSc EByt` and `auval -v aufx SBox SaBx` both passed after the smoothing pass.
34. Tuned the 12 Secret Sauce factory flavor preset defaults for the first real-material listening pass.
35. Added `SECRET_SAUCE_LISTENING_CHECKLIST.md` for vocals, loops, 808/bass, drums, and transition feedback.
36. Release build completed successfully after the preset/listening-prep pass.
37. Codesign verification passed again for Hot Packet and Secret Sauce AU, VST3, and Standalone artifacts.
38. `auval -v aufx SeSc EByt` and `auval -v aufx SBox SaBx` both passed after the preset/listening-prep pass.

### Notes

- This is a compile/build validation only.
- Secret Sauce has its own plugin target and identity.
- Secret Sauce engine v0 is intentionally simple. It now includes first-pass performance gestures, host-tempo-synced timing, flavor-specific DSP profiles, smoothed movement transitions, and tuned factory flavor presets, but pitch/formant, deeper reverse/grab, throw timing, and refined tape-stop behavior still need listening-driven iteration.
- The other single products now have metadata scaffolds, but do not have dedicated plugin targets or DSP engines yet.
- The build used the existing `COPY_PLUGIN_AFTER_BUILD` behavior and installed/overwrote Hot Packet and Secret Sauce AU/VST3 artifacts in the user plugin folders.

### Remaining validation

1. Validate Secret Sauce engine v0 in a DAW on real self-sampled vocals/loops.
2. Replace the packet-style Secret Sauce interface with a dedicated flagship visual system.
3. Add dedicated targets for Sweet Sauce, Thick Sauce, Glue Sauce, Drip Sauce, Extra Sauce, Light Sauce, and Sauce Box.
4. Run DAW testing after the Secret Sauce UI and engine exist.

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
