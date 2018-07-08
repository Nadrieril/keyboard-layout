This repo contains a definition of my colemak-based custom keyboard layout, and
scripts to transform a xkb definition into data suitable to be used with
http://www.keyboard-layout-editor.com

The `make-layout-json.py` script reads the layout definition in `custom.xkb`,
the finger map in `fingers.json` or `fingers-wide.json`, the map to display xkb
symbol names in `symbols.json`, and the layout template in
`layout-template.json`. It then combines them and outputs a json suitable for
use with the editor linked above.

The `do` script simply runs the python script and copies the output to the clipboard.
The included `layout-template.json` matches the keyboard of my ASUS Zenbook.

Sample output:
![Sample layout output](/sample-layout.png?raw=true)

TODO:

- [ ] Clean up the scripts to take the various relevant files as parameters
- [ ] Construct a permalink to the editor instead of having to copy/paste the json
- [ ] Parse xkb files better, in particular understand `include`s
- [ ] Allow reading directly from system xkb files
- [ ] Read geometry from xkb files ?
