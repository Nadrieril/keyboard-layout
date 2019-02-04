with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "keyboard-layout";
  buildInputs = [ python3 python3Packages.pyyaml xorg.xkbcomp jq ];
}
