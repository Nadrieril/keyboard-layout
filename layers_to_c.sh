#!/usr/bin/env bash
set -e

DIR="layout"
KEYBOARD="$1"

LAYOUT_SIZE=76
case $KEYBOARD in
    voyager)
        LAYOUT_SIZE=52
        ;;
esac

cat $DIR/${KEYBOARD}_keymap.json \
    | jq -r \
        '.layout as $layout
        | .layers
        | to_entries[]
        | if .value | length == 0 then .value = [range('"$LAYOUT_SIZE"') | "KC_NO"] else . end
        | .value |= join(",")
        | "  [\(.key)] = \($layout)(\(.value)),"' \
    > $DIR/.contents
cat $DIR/${KEYBOARD}_keymap.template.c \
    | sed -e "/__KEYMAP_GOES_HERE__/r $DIR/.contents" \
          -e '/__KEYMAP_GOES_HERE__/d' \
    > $DIR/${KEYBOARD}_keymap.c
rm $DIR/.contents
