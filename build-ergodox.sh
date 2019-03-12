#!/usr/bin/env nix-shell
#!nix-shell -i bash /home/nadrieril/wip/forks/qmk_firmware/shell.nix
set -e

cd $HOME/wip/forks/qmk_firmware
make ergodox_ez:nadrieril:teensy
