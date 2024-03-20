let
  pkgs = import <nixpkgs> {};
  qmk-shell = import ./qmk_firmware/shell.nix {};

in qmk-shell.overrideAttrs (oldAttrs: {
  name = "keyboard-layout";
  buildInputs = oldAttrs.buildInputs ++ (with pkgs; [ python3 python3Packages.pyyaml xorg.xkbcomp jq ]);
})
