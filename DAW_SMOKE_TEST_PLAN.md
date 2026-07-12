# Sauce Box DAW Smoke Test Plan (V1)

## Goal

Quickly verify stability, recall behavior, and basic audio safety in real DAW workflows before wider release.

## Test Matrix

- Logic Pro (AU)
- Ableton Live (VST3)
- Reaper (VST3)

If only one DAW is available, run full suite there and record limitations.

### Single-DAW Fallback (FL Studio Only)

If FL Studio is the only available DAW, use this release gate instead:

1. Run all 6 smoke cases in FL Studio.
2. Repeat Case 1, Case 2, and Case 3 in a second FL project with different source material.
3. Run a 20-minute continuous playback stress test with active parameter moves.
4. Run a standalone app sanity pass for startup, playback, and control movement.
5. Mark second-DAW validation as deferred and track as a post-launch risk item.

## Pass Criteria

1. No crashes during insert/load/play/close.
2. No extreme output spikes when changing controls.
3. Session save and reopen restores exact settings.
4. Plugin responds smoothly during playback.

## Test Session Setup

1. Use a short test project with:
- Vocal stem
- Drum loop
- 808 or bass stem
- Full mix print
2. Keep project at 44.1 kHz first, then repeat key tests at 48 kHz.
3. Set DAW buffer to 128 samples, then repeat key tests at 512.

## Smoke Test Cases

### Case 1 - Insert and Basic Audio

Steps:
1. Insert Sauce Box on a vocal track.
2. Start playback.
3. Move Drive, Texture, Tone, Mix, Output.
4. Toggle bypass on/off repeatedly.

Expected:
1. No crash.
2. No hard clipping bursts.
3. Controls respond in real time.

### Case 2 - Preset Cycling

Steps:
1. Load each launch preset.
2. Switch presets during playback.
3. Observe output meter and audible transitions.

Expected:
1. No crash.
2. No severe clicks/pops.
3. Preset loudness remains manageable.

### Case 3 - Save/Recall

Steps:
1. Create a custom setting.
2. Save DAW project.
3. Close DAW fully.
4. Reopen project.

Expected:
1. All parameter values restored.
2. Sound matches pre-save state.

### Case 4 - Insert vs Bus

Steps:
1. Use Sauce Box as track insert.
2. Move same instance settings to a bus/aux workflow.
3. Compare behavior and output control.

Expected:
1. Stable in both routing styles.
2. No gain runaway on bus.

### Case 5 - Mono/Stereo

Steps:
1. Insert on mono source.
2. Insert on stereo source.
3. Compare level and tone behavior.

Expected:
1. No channel dropouts.
2. No mono-specific crash or distortion artifacts.

### Case 6 - Sample Rate and Buffer Change

Steps:
1. Run at 44.1 kHz / 128.
2. Run at 48 kHz / 512.
3. Change buffer during a session if DAW allows.

Expected:
1. No crash or freeze.
2. No broken audio state after reconfiguration.

## Issue Severity

- Critical: crash, freeze, project fails to reopen.
- High: loud spikes, broken recall, severe artifacts.
- Medium: occasional zipper noise or minor glitch.
- Low: UI alignment/cosmetic issues.

## Result Log Template

Use this format per DAW:

- DAW:
- Plugin Format:
- OS Build:
- Test Cases Passed: X/6
- Critical Issues:
- High Issues:
- Medium Issues:
- Low Issues:
- Notes:

## Exit Gate

Ready for wider release when:

1. Zero critical issues.
2. No unresolved high-severity audio safety issue.
3. Save/recall confirmed in at least 2 DAWs.

If only FL Studio is available, this alternate gate is acceptable for early launch:

1. Zero critical issues in FL smoke suite.
2. Save/recall passes in FL across two separate projects.
3. Standalone sanity pass is clean.
4. Multi-DAW validation is scheduled as a post-launch checkpoint.
