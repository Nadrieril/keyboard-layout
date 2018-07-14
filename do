#!/usr/bin/env bash
set -e
tmp_file=$(mktemp)

./make-layout.py "$@" > $tmp_file
cat $tmp_file | jq -c '.[]' | sed 's/$/,/' | xclip -in -selection clipboard
cat $tmp_file | jq -c '.[]'
setxkbmap fr,custom
rm $tmp_file
