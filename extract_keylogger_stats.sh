#!/usr/bin/env bash
cat ~/.dotfiles/keys.log \
    | grep KeyPress \
    | ~/.dotfiles/shell/bin/f 4 3 \
    | sed -e 's/Num_Lock//' \
    | sed -e 's/ISO_Level3_Shift/Alt_Gr/' \
    | sed -e 's/\[,/[/' -e 's/,\]/]/' -e 's/,,/,/' \
    | sed -e 's/,/ + /g' -e 's/\[\] //' -e 's/\] \[/ + /' -e 's/\[//g' -e 's/\]//g' \
    | sort \
    | uniq -c \
    | sort -h
