#!/usr/bin/env bash

./make-layout-json.py | jq -c '.[]' | sed 's/$/,/' | xclip -in -selection clipboard
./make-layout-json.py | jq -c '.[]'
