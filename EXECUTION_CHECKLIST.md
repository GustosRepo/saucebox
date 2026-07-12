# Sauce Box Execution Checklist (Based on PRODUCT_REQUIREMENTS)

## How to use this

- Work top to bottom.
- Do not start a new phase until the current phase is mostly complete.
- Treat each checkbox as a shipping gate.

## Phase 0 - Scope Lock (Half day)

- [x] Confirm Free version controls: Instant Sauce, Mix, Output. (Locked in SCOPE_LOCK_V1.md)
- [x] Confirm Pro unlock controls: Drive, Texture, Wow Depth, Wow Rate, Tone, Mix, Output. (Locked in PRODUCT_REQUIREMENTS.md and SCOPE_LOCK_V1.md)
- [x] Confirm Pro-only features list and lock points. (Locked in PRODUCT_REQUIREMENTS.md and SCOPE_LOCK_V1.md)
- [ ] Confirm price target for Pro (single low-friction number). (Currently only defined as "low one-time price")
- [x] Confirm client CTA target URL (track review page). (https://saucebox.audio/review)
- [x] Freeze V1 scope: no new features until launch. (Locked in SCOPE_LOCK_V1.md)

Definition of done:

- One-page scope is locked and shared.
- Team agrees what is in V1 and out of V1.

## Phase 1 - Free Version Foundation (Week 1)

### DSP and stability

- [x] Ensure stable startup and no crash on open/close. (Initial FL Studio smoke pass logged; broader DAW pass still open)
- [x] Add output safety limiter.
- [x] Add gain-match behavior to reduce loudness jump.
- [ ] Verify no clicks/pops on parameter changes. (Needs explicit smoke-test pass)
- [ ] Verify low CPU on common session sizes. (Needs explicit smoke-test pass)

### UX and controls

- [ ] Implement Free Instant Sauce one-knob UI.
- [ ] Map Instant Sauce macro to Drive, Texture, Wow Depth, Wow Rate, Tone, Mix, and output compensation.
- [ ] Add Pro locked detailed-controls state.
- [x] Keep control count minimal and clear. (Current UI is clear; next revision simplifies Free further)
- [x] Add starter default preset (Instant Sauce).
- [ ] Add concise hints for first use.
- [x] Ensure readable UI at common plugin sizes. (Fixed-size 640x420 UI checked in current build)
- [x] Add "by 808Bytes" directly beneath Sauce Box title.

### Presets

- [x] Create 12 launch presets.
- [x] Cover use cases: vocals, 808, drum bus, keys, full mix.
- [ ] Loudness-match presets for fair A/B. (Implemented with gain compensation; final ear check still needed)

Definition of done:

- Free sounds good in under 30 seconds.
- No critical crashes in smoke tests.
- Presets are musical and consistent.

## Phase 2 - Pro Value Layer (Week 2)

### Feature locks and differentiation

- [ ] Add Pro-only locked state for full detailed controls.
- [ ] Keep Free fully usable (no crippleware behavior).
- [ ] Add clear Pro value messaging tied to outcomes.

### Pro feature set

- [ ] Unlock detailed controls: Drive, Texture, Wow Depth, Wow Rate, Tone, Mix, Output.
- [ ] Add advanced shaping (transient/stereo/multiband texture as scoped).
- [ ] Add oversampling options (2x/4x).
- [ ] Add A/B compare.
- [ ] Add preset favorites and expanded preset bank.

Definition of done:

- Pro feels meaningfully faster/deeper than Free.
- Free still feels complete and trustworthy.

## Phase 3 - Conversion and Client Funnel (Week 2)

### In-plugin conversion touchpoints

- [x] Add subtle footer CTA: free track review.
- [ ] Add first-run message with outcome-focused copy.
- [ ] Add Pro unlock prompt only at intent moments.

### Funnel plumbing

- [ ] Launch simple track review page/form. (Spec written; page not built/launched)
- [ ] Capture Name, Email, Song Link, Problem statement. (Specified in TRACK_REVIEW_LANDING_SPEC.md)
- [x] Add auto-response and follow-up template. (Drafted in TRACK_REVIEW_LANDING_SPEC.md)
- [x] Define turnaround SLA for track feedback. (24 to 48 hours in TRACK_REVIEW_LANDING_SPEC.md)

Definition of done:

- Plugin users can request help in under 60 seconds.
- You can reliably follow up and convert warm leads.

## Phase 4 - QA and Launch Readiness (Week 3-4)

### QA matrix

- [ ] Test in major DAWs on macOS. (Initial FL Studio pass only; Logic/Reaper/Ableton still deferred)
- [ ] Test insert and bus workflows.
- [ ] Test mono, stereo, and sample-rate changes.
- [ ] Test project save/recall.
- [ ] Test preset switching at playback.

### Release assets

- [ ] Finalize website copy and screenshots.
- [ ] Publish Free download page.
- [ ] Publish Pro upgrade page.
- [ ] Prepare short demo audio/video clips.

Definition of done:

- Release candidate passes QA matrix.
- Download, install, and first-use journey is smooth.

## Weekly KPI Tracker

- [ ] Free downloads.
- [ ] Active users (opened plugin 3+ sessions).
- [ ] CTA click-through rate.
- [ ] Track review submissions.
- [ ] Pro conversion rate.
- [ ] Service conversion rate from plugin users.

## Discipline Rules (Anti Scope Drift)

- [x] Rule 1: No new features unless they improve first-use sound or conversion.
- [x] Rule 2: Stability beats novelty every sprint.
- [x] Rule 3: Preset quality beats feature quantity.
- [x] Rule 4: Every build must preserve trust (no surprises, no spikes).

## Immediate Next 5 Tasks

- [x] Lock final Free and Pro feature list.
- [x] Implement output limiter + gain match.
- [x] Build and tune 12 Free presets. (Implemented as built-in program bank; final ear-tuning ongoing)
- [x] Add in-plugin CTA and create track review landing page. (Spec in TRACK_REVIEW_LANDING_SPEC.md)
- [ ] Prototype Instant Sauce Free UI and macro mapping.

## Current Open Blockers

- Pick the exact Sauce Box Pro launch price.
- Tune Instant Sauce macro by ear so Free feels useful, not crippled.
- Decide visual locked-state treatment for Pro controls.
- Run explicit save/recall, preset switching during playback, mono/stereo, sample-rate, and buffer smoke tests.
- Build and publish the actual track review landing page/form from TRACK_REVIEW_LANDING_SPEC.md.
- Decide whether first-run hints belong in Free V1 or should stay out to keep the interface clean.
