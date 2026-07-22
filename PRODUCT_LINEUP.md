# Sauce Product Lineup

## Sales Model

Each sauce is sold as its own plugin. Sauce Box is the full-suite bundle.

Secret Sauce is the flagship and highest-priority paid product, but every flavor
has its own identity, installer, presets, license SKU, and plugin IDs.

## Singles

| Product | Role | Bundle ID | Plugin Code | SKU |
|---|---|---|---|---|
| Hot Packet | Free/entry texture and warmth | `com.saucebox.plugin` | `SBox` | `hot-packet-pro` |
| Secret Sauce | Flagship movement, chops, pitch, repeats, and ear candy | `com.808bytes.secretsauce` | `SeSc` | `secret-sauce-pro` |
| Sweet Sauce | Vocal polish, air, compression, and presence | `com.808bytes.sweetsauce` | `SwSc` | `sweet-sauce-pro` |
| Thick Sauce | 808, bass, low-end weight, and body | `com.808bytes.thicksauce` | `ThSc` | `thick-sauce-pro` |
| Glue Sauce | Drum bus and mix bus glue | `com.808bytes.gluesauce` | `GlSc` | `glue-sauce-pro` |
| Drip Sauce | Delays, throws, space, and ambience | `com.808bytes.dripsauce` | `DrSc` | `drip-sauce-pro` |
| Extra Sauce | Aggressive distortion, crush, chaos, and hard movement | `com.808bytes.extrasauce` | `ExSc` | `extra-sauce-pro` |
| Light Sauce | Subtle clean polish, lift, and clarity | `com.808bytes.lightsauce` | `LiSc` | `light-sauce-pro` |

## Suite

| Product | Role | Bundle ID | Plugin Code | SKU |
|---|---|---|---|---|
| Sauce Box | Full suite bundle with every sauce plugin | `com.808bytes.saucebox` | `SaBx` | `sauce-box-suite` |

## Engineering Notes

The current build still produces the Hot Packet AU/VST3/Standalone target while
the shared platform is being extracted. Hot Packet keeps the legacy
`com.saucebox.plugin` / `SBox` identity for compatibility with the existing
installed plugin.

Secret Sauce now has its own AU/VST3/Standalone target and product identity.
Engine v0 includes Sauce macro control, movement depth/rate, chop,
stutter-style sample hold, moving filter, width, mix, output, safety limiting,
and six performance buttons: Freeze, Reverse, Repeat, Dropout, Tape Stop, and
Throw.
