#!/usr/bin/env bash
set -e

DIR=voyager
cat $DIR/layers.json \
    | jq -r \
        '.layout as $layout
        | .layers
        | to_entries[]
        | if .value | length == 0 then .value = [range(76) | "KC_NO"] else . end
        | .value |= join(",")
        | "  [\(.key)] = \($layout)(\(.value)),"' \
    > $DIR/.contents
cat $DIR/keymap.template.c \
    | sed -e "/__KEYMAP_GOES_HERE__/r $DIR/.contents" \
          -e '/__KEYMAP_GOES_HERE__/d' \
    > $DIR/keymap.c
rm $DIR/.contents
