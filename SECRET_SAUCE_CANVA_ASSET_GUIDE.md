# Secret Sauce Canva Asset Guide

## Goal

Create one polished packet-style visual system that can be reused across the
whole sauce plugin line. Each flavor can share the same packet layout and change
colors, label details, and small accents.

## Canva Setup

Create a custom Canva design:

```text
1440 x 1120 px
```

This is 2x the current plugin UI size of `720 x 560`, so exported images should
look sharp inside the JUCE plugin.

## Core Assets

Start with these two:

1. `secret_sauce_packet_bg.png`
   - Full packet background.
   - Include texture, crimped edges, color, label art, shadows, highlights, and
     printed details.
   - Do not include interactive controls like knobs, sliders, buttons, or menu
     text.
   - Avoid baking in text that may need to change later.

2. `secret_sauce_logo.png`
   - Transparent logo or wordmark.
   - Can include `808Bytes` and `Secret Sauce`.
   - Export with transparent background.

Optional reusable assets:

3. `sauce_badge.png`
   - Small sticker, stamp, label badge, or `PRO` accent.
   - Export with transparent background.

4. `button_texture.png`
   - Subtle reusable texture for performance buttons.
   - Export with transparent background if it is just an overlay.

## Export Settings

For packet backgrounds:

- File type: `PNG`
- Transparent background: off
- Size: `2x` if available

For logos, badges, and overlays:

- File type: `PNG`
- Transparent background: on
- Size: `2x` if available

## Canva Search Terms

Useful terms to search inside Canva:

- `foil packet texture`
- `sauce packet`
- `condiment packet`
- `plastic wrapper texture`
- `sticker label`
- `hot sauce label`
- `retro food label`
- `halftone texture`
- `grain texture`
- `printed ink texture`
- `crimped edge`

## Suggested Flavor Color System

Use one packet template and swap colors per sauce:

| Product | Suggested Colors |
|---|---|
| Secret Sauce | red, plum, gold |
| Sweet Sauce | pink, cream, gold |
| Thick Sauce | black, deep red, yellow |
| Glue Sauce | blue, steel, yellow |
| Drip Sauce | teal, purple, silver |
| Extra Sauce | neon green, red, black |
| Light Sauce | white, mint, sky |
| Hot Packet | red, orange, yellow |

## Design Notes

- Keep the center area clean enough for the main `Sauce` knob.
- Leave room for a `Flavor` selector near the main control.
- Leave a horizontal strip for six performance buttons:
  `Freeze`, `Reverse`, `Repeat`, `Dropout`, `Tape Stop`, `Throw`.
- Leave a lower area for smaller pro controls.
- Keep important artwork away from the edges so it does not fight the UI.
- Make the packet texture subtle. It should feel polished, not noisy.

## First Pass Deliverables

For the first UI skin pass, only these are required:

1. `secret_sauce_packet_bg.png`
2. `secret_sauce_logo.png`

Once those exist, the plugin can keep knobs, buttons, and menus drawn in JUCE so
the controls stay crisp and interactive.
