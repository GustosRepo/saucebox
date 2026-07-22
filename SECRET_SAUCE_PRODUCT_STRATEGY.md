# Secret Sauce Product Strategy (Flagship)

## Position

Secret Sauce is the main paid product in the Sauce Box ecosystem.

Hot Packet remains the entry point and free texture plugin, but Secret Sauce is
the product built for the way most users will actually create: recording or
sampling themselves, then adding movement, chops, pitch, repeats, and ear-candy
effects until the part feels alive.

## Core Promise

Turn self-recorded samples, vocal ideas, loops, and plain sounds into moving
production-ready sauce fast.

Secret Sauce should make a dry idea feel:

1. Less static.
2. More rhythmic.
3. More expensive.
4. Easier to flip into a hook, loop, intro, transition, or texture.

## Target User

1. Producers who sample their own voice, instruments, phone recordings, or loop
   ideas.
2. Artists who record rough vocal ideas and want motion without deep editing.
3. Beatmakers who need quick movement on melodies, chops, 808 accents, and
   transitions.
4. Engineers who want fast ear candy without building full automation chains.

## Product Family Role

Each sauce is sold as its own plugin. Sauce Box is the full-suite offer for
customers who want every flavor together.

| Product | Role |
|---|---|
| Secret Sauce | Flagship paid creative movement/effects plugin |
| Hot Packet | Free/entry texture and warmth plugin |
| Sweet Sauce | Vocal polish, air, compression, presence |
| Thick Sauce | 808, bass, and body enhancer |
| Glue Sauce | Drum bus and mix bus glue |
| Drip Sauce | Delays, throws, space, and ambience |
| Extra Sauce | Aggressive distortion, crush, chaos, hard movement |
| Light Sauce | Subtle clean polish and clarity |
| Sauce Box | Bundle/all-in-one premium ecosystem |

## Secret Sauce V1 Controls

Free/demo surface:

1. Sauce: one main movement intensity macro.
2. Flavor: preset-style mode selector.
3. Mix.
4. Output.

Pro controls:

1. Movement Rate.
2. Movement Depth.
3. Swing.
4. Random.
5. Pitch.
6. Formant.
7. Chop.
8. Stutter.
9. Reverse.
10. Filter.
11. Width.
12. Mix.
13. Output.

Performance buttons:

1. Freeze.
2. Reverse.
3. Repeat.
4. Dropout.
5. Tape Stop.
6. Throw.

## V1 Flavor Modes

1. Self Sample Sauce: clean movement for vocals and self-recorded ideas.
2. Vocal Chop: rhythmic chops and gated motion.
3. Reverse Pull: reverse swells and pickup effects.
4. Stutter Step: repeats, skips, and short rhythmic catches.
5. Tape Wobble: pitch drift, wow, flutter, and softened tone.
6. Dirty Dream: lo-fi texture with movement.
7. Drip Throw: delay-style throw and wet ear candy.
8. Half-Time Melt: slowed-feel movement without committing to destructive audio.
9. Formant Ghost: vocal-like pitch/formant movement.
10. Hook Maker: wide, polished movement for melodic hooks.
11. Dark R&B: moody filtering, width, and slow motion.
12. Trap Motion: faster chops, 808 accents, and rhythmic spice.

## Launch Packaging

The first commercial path should be:

1. Hot Packet Free gets producers into the ecosystem.
2. Secret Sauce Pro is the main upgrade offer.
3. Each flavor remains available as a single paid plugin.
4. Sauce Packs expand individual sauces with genre and workflow presets.
5. Sauce Box later bundles all flavors once two or more products share the
   platform cleanly.

## Preset Pack Ideas

1. Self Sample Sauce.
2. Vocal Sauce.
3. Dark R&B Sauce.
4. Trap Motion Sauce.
5. Afro Bounce Sauce.
6. Jersey Flip Sauce.
7. 808 Sauce.
8. Hook Sauce.
9. Transition Sauce.
10. Secret Sauce After Dark.

## Build Direction

Secret Sauce should not be a small variation of Hot Packet. It should share
platform pieces, but its engine needs movement-first modules:

1. Tempo-sync movement LFO.
2. Randomized modulation.
3. Pitch/formant shifting.
4. Beat-repeat/stutter buffer.
5. Reverse/grab buffer.
6. Filter motion.
7. Width and throw effects.
8. Output safety.

The first engineering step is product scaffolding:

1. Add Secret Sauce manifest, theme, and preset recipe files. Done.
2. Add a product catalog so Hot Packet and Secret Sauce can coexist in code. Done.
3. Add a dedicated Secret Sauce build target with unique AU/VST3 identity. Done.
4. Add engine v0: Sauce macro, movement, chop, stutter-style hold, filter
   motion, width, mix, output safety. Done.
5. Add first-pass performance buttons: Freeze, Reverse, Repeat, Dropout, Tape
   Stop, and Throw. Done.
6. Add first-pass host tempo sync for movement, chops, repeats, dropouts,
   reverse windows, throws, and tape-stop curves. Done.
7. Add first-pass flavor intelligence so the Flavor selector changes timing,
   gate depth, tone, width, saturation, reverse, throw, and tape behavior. Done.
8. Add movement/performance smoothing for chop gates, dropout gates, reverse,
   throw, and tape transitions. Done.
9. Tune the 12 factory flavor presets for a stronger first listening pass. Done.
10. Add a real-material listening checklist for feedback capture. Done.
11. Move shared DSP into reusable modules before deepening the advanced Secret
   Sauce movement engine.
