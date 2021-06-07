#!/usr/bin/env bash
set -e

cat ergodox_layout/layers.json \
    | jq -r '
        .layers
        | to_entries[]
        | if .value | length == 0 then .value = [range(76) | "KC_NO"] else . end
        | .value |= join(",")
        | "  [\(.key)] = LAYOUT_ergodox(\(.value)),"' \
    > ergodox_layout/.contents
cat ergodox_layout/keymap.template.c \
    | sed -e '/__KEYMAP_GOES_HERE__/r ergodox_layout/.contents' \
          -e '/__KEYMAP_GOES_HERE__/d' \
    > ergodox_layout/keymap.c
# rm ergodox_layout/.contents
cd $HOME/wip/forks/qmk_firmware
make ergodox_ez:nadrieril:teensy
