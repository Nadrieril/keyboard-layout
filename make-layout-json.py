#!/usr/bin/env python
# Use with http://www.keyboard-layout-editor.com

import sys, re, json

FINGER_MAP_FILE = "fingers-wide.json"
LAYOUT_NAME = "Colemak (wide mod, DH mod, angle mod, custom modifications)"
XKB_TEMPLATE = """
xkb_keymap {
    xkb_keycodes  { include "evdev+aliases(azerty)" };
    xkb_types     { include "complete" };
    xkb_compat    { include "complete" };
    xkb_symbols   {
        include "pc+fr+inet(evdev)+group(shifts_toggle)+ctrl(nocaps)+compose(paus)"
        name[Group2]= "%s";
%s
        include "level3(ralt_switch)"
    };
    xkb_geometry  { include "pc(pc105)" };
};
"""
finger_colors = {
     0: "#474747",
     1: "#7d1b22",
     2: "#2d7370",
    -2: "#365c70",
     3: "#1e5422",
    -3: "#1e5422",
     4: "#6e0964",
    -4: "#6e0964",
     5: "#705800",
    -5: "#705800",
}

def pretty(x):
    if x in symbol_dict:
        return symbol_dict[x]
    elif len(x) == 1:
        return x
    else:
        # print(x, file=sys.stderr)
        return "" #"•" # "ⁿ̸ₐ"

with open("symbols.json") as f:
    symbol_dict = json.loads(f.read())


with open("layout-order.json") as f:
    layout_order = json.loads(f.read())

with open("layout-map.json") as f:
    layout_map = json.loads(f.read())

key_map = {}
for (x, y) in zip(layout_order, layout_map):
    for (k, v) in zip(x, y):
        key_map[k] = v


with open("custom.xkb", "w") as f:
    key_defs = "\n".join(
        "        key %s { [], [ %s ] };" % (k, v)
        for (k, v) in key_map.items()
    )
    f.write(XKB_TEMPLATE % (LAYOUT_NAME, key_defs))


with open("layout-template.json") as f:
    layout_template = f.read()

with open(FINGER_MAP_FILE) as f:
    fingers = json.loads(f.read())
    for key, f in fingers.items():
        layout_template = layout_template.replace("\"%s\"" % (key,), "{\"c\":\"%s\"},\"%s\"" %
                (finger_colors[f], key))

for (key, symbs) in key_map.items():
    symbs = [ pretty(x.strip()) for x in symbs.split(",") ]
    if symbs[1] == symbs[0].upper():
        symbs[0] = symbs[1]
        symbs[1] = ""
    symb_str = "%s\\n\\n\\n%s\\n\\n\\n\\n\\n\\n%s" % (symbs[1], symbs[2], symbs[0])
    layout_template = layout_template.replace(key, symb_str)


print(layout_template)

