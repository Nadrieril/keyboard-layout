#!/usr/bin/env zsh
cat corpus/**/*(.) \
    | sed \
        -e 's,ä,∘"a,g' \
        -e 's,ü,∘"u,g' \
        -e 's,ö,∘"o,g' \
        -e 's,ï,∘"i,g' \
        -e 's,ë,∘"e,g' \
        -e 's,œ,∘oe,g' \
        -e 's,♫,∘#oo,g' \
        -e 's,♪,∘#o/,g' \
        -e 's,✓,∘@/,g' \
        -e 's,✔,∘@@/,g' \
        -e 's/😄/∘:D/g' \
        -e 's/😊/∘^^/g' \
        -e 's/♥/∘<3/g' \
        -e 's/™/∘tm/g' \
        -e 's/©/∘oc/g' \
        -e 's/²/∘^2/g' \
        -e "s/’/'/g" \
        -e 's/“/"/g' \
        -e 's/”/"/g' \
        -e 's,https\?://[^ ]\+,,g' \
    | python -c 'import sys, collections, json; print(json.dumps(collections.Counter(sys.stdin.read().lower())))' \
    | jq -c 'to_entries | sort_by(.value) | .[] | [.value, .key]'

