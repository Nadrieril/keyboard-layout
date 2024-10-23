#!/usr/bin/env bash
set -e

cat ergodox/layers.json \
    | jq -r \
        --argjson map "$(cat ergodox/azerty_map.yaml | yaml2json)" \
        '.layers
        | to_entries[]
        | if .value | length == 0 then .value = [range(76) | "KC_NO"] else . end
        # | .value |= map(if in($map) then $map[.] else . end)
        | .value |= join(",")
        | "  [\(.key)] = LAYOUT_ergodox(\(.value)),"' \
    > ergodox/.contents
cat ergodox/keymap.template.c \
    | sed -e '/__KEYMAP_GOES_HERE__/r ergodox/.contents' \
          -e '/__KEYMAP_GOES_HERE__/d' \
    > ergodox/keymap.c
rm ergodox/.contents
cd qmk_firmware
nix-shell --run "make ergodox_ez:nadrieril:teensy"
