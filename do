#!/usr/bin/env bash
set -e
tmp_file=$(mktemp)

./make-layout.py "$@" > $tmp_file
data="$(cat $tmp_file | jq -rf urlon.jq)"
xdg-open "http://www.keyboard-layout-editor.com/##$data"

# cat $tmp_file | jq -c '.[]'
# setxkbmap fr,custom
rm $tmp_file
