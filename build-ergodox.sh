#!/usr/bin/env nix-shell
#!nix-shell -i bash /home/nadrieril/wip/forks/qmk_firmware/shell.nix
set -e

cat ergodox_layout/layers.json \
    | jq -r '.layers | to_entries[] | "  [\(.key)] = LAYOUT_ergodox(\(.value | join(","))),"' \
    > ergodox_layout/.contents
cat ergodox_layout/keymap.template.c \
    | sed -e '/__KEYMAP_GOES_HERE__/r ergodox_layout/.contents' \
          -e '/__KEYMAP_GOES_HERE__/d' \
    > ergodox_layout/keymap.c
rm ergodox_layout/.contents
cd $HOME/wip/forks/qmk_firmware
make ergodox_ez:nadrieril:teensy