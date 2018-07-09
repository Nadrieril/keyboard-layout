#!/usr/bin/env bash

./make-layout.py | jq -c '.[]' | sed 's/$/,/' | xclip -in -selection clipboard
./make-layout.py | jq -c '.[]'
