# Sauce Box Execution Checklist (Based on PRODUCT_REQUIREMENTS)

## How to use this

- Work top to bottom.
- Do not start a new phase until the current phase is mostly complete.
- Treat each checkbox as a shipping gate.

## Phase 0 - Scope Lock (Half day)

- [ ] Confirm Free version controls: Drive, Texture, Tone, Mix, Output.
- [ ] Confirm Pro-only features list and lock points.
- [ ] Confirm price target for Pro (single low-friction number).
- [ ] Confirm client CTA target URL (track review page).
- [ ] Freeze V1 scope: no new features until launch.

Definition of done:

- One-page scope is locked and shared.
- Team agrees what is in V1 and out of V1.

## Phase 1 - Free Version Foundation (Week 1)

### DSP and stability

- [ ] Ensure stable startup and no crash on open/close.
- [ ] Add output safety limiter.
- [ ] Add gain-match behavior to reduce loudness jump.
- [ ] Verify no clicks/pops on parameter changes.
- [ ] Verify low CPU on common session sizes.

### UX and controls

- [ ] Keep control count minimal and clear.
- [ ] Add starter default preset (Instant Sauce).
- [ ] Add concise hints for first use.
- [ ] Ensure readable UI at common plugin sizes.

### Presets

- [ ] Create 12 launch presets.
- [ ] Cover use cases: vocals, 808, drum bus, keys, full mix.
- [ ] Loudness-match presets for fair A/B.

Definition of done:

- Free sounds good in under 30 seconds.
- No critical crashes in smoke tests.
- Presets are musical and consistent.

## Phase 2 - Pro Value Layer (Week 2)

### Feature locks and differentiation

- [ ] Add Pro-only tags in UI for advanced features.
- [ ] Keep Free fully usable (no crippleware behavior).
- [ ] Add clear Pro value messaging tied to outcomes.

### Pro feature set

- [ ] Add advanced shaping (transient/stereo/multiband texture as scoped).
- [ ] Add oversampling options (2x/4x).
- [ ] Add A/B compare.
- [ ] Add preset favorites and expanded preset bank.

Definition of done:

- Pro feels meaningfully faster/deeper than Free.
- Free still feels complete and trustworthy.

## Phase 3 - Conversion and Client Funnel (Week 2)

### In-plugin conversion touchpoints

- [ ] Add subtle footer CTA: free track review.
- [ ] Add first-run message with outcome-focused copy.
- [ ] Add Pro unlock prompt only at intent moments.

### Funnel plumbing

- [ ] Launch simple track review page/form.
- [ ] Capture Name, Email, Song Link, Problem statement.
- [ ] Add auto-response and follow-up template.
- [ ] Define turnaround SLA for track feedback.

Definition of done:

- Plugin users can request help in under 60 seconds.
- You can reliably follow up and convert warm leads.

## Phase 4 - QA and Launch Readiness (Week 3-4)

### QA matrix

- [ ] Test in major DAWs on macOS.
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

- [ ] Rule 1: No new features unless they improve first-use sound or conversion.
- [ ] Rule 2: Stability beats novelty every sprint.
- [ ] Rule 3: Preset quality beats feature quantity.
- [ ] Rule 4: Every build must preserve trust (no surprises, no spikes).

## Immediate Next 5 Tasks

- [x] Lock final Free and Pro feature list.
- [x] Implement output limiter + gain match.
- [x] Build and tune 12 Free presets. (Implemented as built-in program bank; final ear-tuning ongoing)
- [x] Add in-plugin CTA and create track review landing page. (Spec in TRACK_REVIEW_LANDING_SPEC.md)
- [ ] Run DAW smoke tests and fix blockers. (FL-only fallback path defined in DAW_SMOKE_TEST_PLAN.md; initial pass logged in SMOKE_TEST_RESULTS.md)
